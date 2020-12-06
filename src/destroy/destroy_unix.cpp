#include "destroy_unix.h"
#include "static_unit.h"
#include "tools.h"
#include "destroy_platform.h"
#ifndef WIN32
#include <csignal>
#endif


DestroyUnix::DestroyUnix() {
#ifndef WIN32
    struct sigaction sigIntHandler{};

    sigIntHandler.sa_handler = [](int s) {
        std::string event = "Caught Signal " + std::to_string(s);
        Tools::destroy_thread(event, destroy_platform::platform);
    };
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    //catch SIGINT(CTRL+C) SIGALRM(kill -14 pid)
    sigaction(SIGINT, &sigIntHandler, nullptr);
    sigaction(SIGALRM, &sigIntHandler, nullptr);
#endif
}
