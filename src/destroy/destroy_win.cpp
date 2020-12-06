#include "destroy_win.h"
#include "spdlog/spdlog.h"
#include "static_unit.h"
#include "tools.h"
#include "destroy_platform.h"
#ifdef WIN32
#include <Windows.h>

BOOL CtrlHandler(DWORD fdwCtrlType);
BOOL CtrlHandler(DWORD fdwCtrlType)
{
    std::string event;
    switch (fdwCtrlType)
    {
        /* handle the CTRL-C signal */
        case CTRL_C_EVENT:
            event = std::string("CTRL-C event");
            break;
            /* handle the CTRL-BREAK signal */
        case CTRL_BREAK_EVENT:
            event = std::string("CTRL-BREAK event");
            break;

            /* handle the CTRL-CLOSE signal */
        case CTRL_CLOSE_EVENT:
            event = std::string("CTRL_CLOSE_EVENT");
            break;

            /* handle the CTRL-LOGOFF signal */
        case CTRL_LOGOFF_EVENT:
            event = std::string("CTRL-LOGOFF event");
            break;

            /* handle the CTRL-SHUTDOWN signal */
        case CTRL_SHUTDOWN_EVENT:
            event = std::string("CTRL-SHUTDOWN event");
            break;

        default:
            return FALSE;
    }
    Tools::destroy_thread(event, destroy_platform::platform);

    //1 second to wait resource destroy when event is "CTRL_CLOSE_EVENT"
    if(fdwCtrlType == CTRL_CLOSE_EVENT) {
        Sleep(1*1000);
    }

    return TRUE;
}
#endif

DestroyWin::DestroyWin() {
#ifdef WIN32
    if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE))
    {
        spdlog::info("WINDOWS API-->SetConsoleCtrlHandler.");

    }
    else
    {
        spdlog::info("ERROR: could not set control handler.");
    }
#endif


}
