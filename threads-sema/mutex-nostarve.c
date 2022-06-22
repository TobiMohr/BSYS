#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h"

//
// Here, you have to write (almost) ALL the code. Oh no!
// How can you show that a thread does not starve
// when attempting to acquire this mutex you build?
//

typedef struct __ns_mutex_t {
    int room1;
    int room2;
    sem_t t1;
    sem_t t2;
    sem_t mutex;
} ns_mutex_t;

void ns_mutex_init(ns_mutex_t *m) {
    m->room1 = 0;
    m->room2 = 0;
    sem_init(&m->t1, 0, 1);
    sem_init(&m->t2, 0, 0);
    sem_init(&m->mutex, 0, 1);
}

void ns_mutex_acquire(ns_mutex_t *m) {
    sem_wait(&m->mutex);
    m->room1++;
    sem_post(&m->mutex);

    sem_wait(&m->t1);
    m->room2++;
    sem_wait(&m->mutex);
    m->room1--;

    if (m->room1 == 0) {
        sem_post(&m->mutex);
        sem_post(&m->t2);
    }
    else {
        sem_post(&m->mutex);
        sem_post(&m->t1);
    }

    sem_wait(&m->t2);
    m->room2--;
}

void ns_mutex_release(ns_mutex_t *m) {
    if (m->room2 == 0) {
        sem_post(&m->t1);
    }
    else {
        sem_post(&m->t2);
    }
}

int loops;
int value = 0;

ns_mutex_t mymutex;

void *worker(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        ns_mutex_acquire(&mymutex);
        value++;
        printf("value: %d\n", value);//critical section
        ns_mutex_release(&mymutex);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    assert(argc == 3);
    int num_workers = atoi(argv[1]);
    loops = atoi(argv[2]);

    pthread_t pw[num_workers];

    ns_mutex_init(&mymutex);
    printf("parent: begin\n");

    int i;
    for (i =0; i < num_workers; i++) {
        Pthread_create(&pw[i], NULL, worker, NULL);
    }

    for (i = 0; i < num_workers; i++) {
        Pthread_join(pw[i], NULL);
    }

    printf("parent: end\n");
    return 0;
}

