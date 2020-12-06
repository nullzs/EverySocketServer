#ifndef EVERYSOCKETSERVER_DESTROY_UNIX_H
#define EVERYSOCKETSERVER_DESTROY_UNIX_H

#include "destroy.h"

class DestroyUnix : public Destroy {
public:
    DestroyUnix();
    ~DestroyUnix() override = default;
};


#endif //EVERYSOCKETSERVER_DESTROY_UNIX_H
