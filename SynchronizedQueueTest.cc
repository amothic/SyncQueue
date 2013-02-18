#include <pthread.h>
#include "SynchronizedQueue.h"

typedef struct _thread_arg {
    SynchronizedQueue* q;
    int size;
} thread_arg_t;


static void
fail(const char *reason) {
    printf("SynchronizedQueueTest failed %s", reason);
}

static void
push_func(void *arg) {
    thread_arg_t* targ = (thread_arg_t *)arg;
    for(int i = 0; i < targ->size; i++) {
        printf("push %d\n",i);
        targ->q->push(i);
    }
    return;
}

static void
pop_func(void *arg) {
    thread_arg_t* targ = (thread_arg_t *)arg;
    for(int i = 0; i < targ->size; i++) {
        if (targ->q->pop() != i) {
            fail("pop data fail\n");
            break;
        }
        printf("\t pop %d\n",i);
    }
    return;
}

static void
tester(SynchronizedQueue* q, int size) {
    //送信者スレッド作成
    thread_arg_t starg;
    starg.q = q;
    starg.size = size;

    pthread_t send;
    pthread_create(&send, NULL, (void* (*)(void*))&push_func, (void*)&starg);

    //受信者スレッド作成
    thread_arg_t rtarg;
    rtarg.q = q;
    rtarg.size = size;

    pthread_t recv;
    pthread_create(&recv, NULL, (void* (*)(void*))&pop_func, (void*)&rtarg);

    //終了待ち
    pthread_join(send, NULL);
    pthread_join(recv, NULL);
}

static void
test() {
    SynchronizedQueue* q1= new SynchronizedQueue(2);
    tester(q1,16);
    tester(q1,32);
    SynchronizedQueue* q2 = new SynchronizedQueue(8);
    tester(q2,16);
    tester(q2,32);
    SynchronizedQueue* q3 = new SynchronizedQueue(16);
    tester(q3,16);
    tester(q3,32);
}

int
main() {
    test();
    printf("SynchronizedQueueTest succeed\n");
}
