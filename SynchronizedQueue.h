#ifndef INCLUDED_SYNC_QUEUE
#define INCLUDED_SYNC_QUEUE

#include <queue>
#include "Sem.h"

class SynchronizedQueue {
    public:
        SynchronizedQueue(unsigned int _qsize = 32);
        virtual ~SynchronizedQueue();

        // functions
        void push(int data);
        int  pop();

    private:
        queue<int> q;
        unsigned int qsize;
        SemPtr queue_remain;
        SemPtr queue_count;
};

#endif
