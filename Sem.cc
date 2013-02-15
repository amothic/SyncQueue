#include "Sem.h"
#include <pthread.h>

Sem::Sem(int value)
{
    sem = new sem_t;
    pthread_mutex_init(&sem->mutex, NULL);
    pthread_cond_init(&sem->cond, NULL);
    sem->value = value;
}

Sem::~Sem()
{
    pthread_mutex_destroy(&sem->mutex);
    pthread_cond_destroy(&sem->cond);

    delete sem;
}

//P命令
//資源を確保する
    void
Sem::sem_p()
{
    pthread_mutex_lock(&sem->mutex);

    //セマフォ変数が0の時、他のスレッドが資源を解放するのを待つ
    while(sem->value == 0) {
        pthread_cond_wait(&sem->cond, &sem->mutex);
    }

    sem->value--;	//資源の確保

    pthread_mutex_unlock(&sem->mutex);
}

//V命令
//資源を解放する
    void
Sem::sem_v()
{
    pthread_mutex_lock(&sem->mutex);
    sem->value++;	//資源の解放

    //資源の解放を知らせる
    pthread_cond_signal(&sem->cond);
    pthread_mutex_unlock(&sem->mutex);

}
