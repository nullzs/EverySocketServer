#include "static_unit.h"
#include "server_init.h"
#include "listener_threads.h"

int main(int argc, char** argv)
{
    ServerInit::get_instance().init();
    StaticUnit::log->daily->info("server start!");

    auto listeners = std::make_shared<ListenerThreads>();
    return 0;
}