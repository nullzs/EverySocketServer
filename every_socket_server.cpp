#include "static_unit.h"
#include "server_init.h"
#include "listener_threads.h"
#include "thread_pool.h"

int main(int argc, char** argv)
{
    ServerInit::get_instance().init();
    StaticUnit::log->daily->info("server start!");

    auto thread_pool = std::make_shared<ThreadPool>();

    auto listeners = std::make_shared<ListenerThreads>();

    return 0;
}