#include "static_unit.h"
#include "server_init.h"
#include "listener_threads.h"
#include "thread_pool.h"
#include "push_pool/push_pool.h"
#include "destroy_win.h"
#include "destroy_unix.h"

int main(int argc, char **argv) {
    ServerInit::get_instance().init();
    StaticUnit::log->daily->info("server start!");
    StaticUnit::log->daily->flush();
    auto push_pool = std::make_shared<PushPool>(1, PushTask::push_default);

    auto thread_pool = std::make_shared<ThreadPool>();

    auto listeners = std::make_shared<ListenerThreads>();
#ifdef WIN32
    auto destroy = std::make_shared<DestroyWin>();
#else
    auto destroy = std::make_shared<DestroyUnix>();
#endif

    return 0;
}