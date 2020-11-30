#include "static_unit.h"
#include "server_init.h"

int main(int argc, char** argv)
{
    ServerInit::get_instance().init();
    StaticUnit::log->daily->info("server start!");
    return 0;
}