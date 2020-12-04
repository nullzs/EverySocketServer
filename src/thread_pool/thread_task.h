#ifndef EVERYSOCKETSERVER_THREAD_TASK_H
#define EVERYSOCKETSERVER_THREAD_TASK_H


class ThreadTask {
public:
    ThreadTask() = delete;
    static void do_task(int thread_id);
};


#endif //EVERYSOCKETSERVER_THREAD_TASK_H
