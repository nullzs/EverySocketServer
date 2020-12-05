#ifndef EVERYSOCKETSERVER_PUSH_TASK_H
#define EVERYSOCKETSERVER_PUSH_TASK_H


class PushTask {
public:
    static void do_task(int type);

    enum {
        push_default = 0
    };
    PushTask() = delete;

};


#endif //EVERYSOCKETSERVER_PUSH_TASK_H
