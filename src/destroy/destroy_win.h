#ifndef EVERYSOCKETSERVER_DESTROY_WIN_H
#define EVERYSOCKETSERVER_DESTROY_WIN_H

#include "destroy.h"

class DestroyWin: public Destroy {
public:
    DestroyWin();
    ~DestroyWin() override = default;
};


#endif //EVERYSOCKETSERVER_DESTROY_WIN_H
