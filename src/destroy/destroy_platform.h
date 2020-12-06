#ifndef EVERYSOCKETSERVER_DESTROY_PLATFORM_H
#define EVERYSOCKETSERVER_DESTROY_PLATFORM_H
#include <string>

namespace destroy_platform {
#ifdef WIN32
    const std::string platform{"WIN"};
#else
    const std::string platform{"UNIX_LIKE"};
#endif
}

#endif //EVERYSOCKETSERVER_DESTROY_PLATFORM_H
