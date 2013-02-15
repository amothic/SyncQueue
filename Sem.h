#ifndef INCLUDED_SEM
#define INCLUDED_SEM

#include <pthread.h>

typedef struct sem_t {
    volatile int value;		//セマフォ変数
    pthread_mutex_t mutex;	//セマフォ操作用のロック
    pthread_cond_t cond;	//待ち合わせ用の条件変数
} sem_t, *sem_ptr;

class Sem {
    public:
        /* constructor */
        Sem(int value);
        ~Sem();
        void sem_p();
        void sem_v();
        /* variables */
    private:
        sem_t *sem;
};

typedef Sem *SemPtr;

#endif /* INCLUDED_SEM */
