#include "SynchronizedQueue.h"

SynchronizedQueue::SynchronizedQueue(unsigned int _qsize) {
    qsize = _qsize;

    //queue内に入る残りの数
    queue_remain  = new Sem(qsize-1);

    //queue内に現在入っている数
    queue_count	= new Sem(0);

}

SynchronizedQueue::~SynchronizedQueue() {
}


void
SynchronizedQueue::push(int data) {
    queue_remain->sem_p();	//資源-1
    q.push(data);
    queue_count->sem_v();	//資源+1
}

int
SynchronizedQueue::pop() {
    queue_count->sem_p();	//資源-1
    int data = 0;

    if (!q.empty()) {
        data = q.front();
        q.pop();
    }
    queue_remain->sem_v();	//資源+1

    return data;
}
