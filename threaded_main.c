/*-------------------------------------------------------------------
Author: Aaron Anthony Valoroso
Date: November 3rd, 2019
License: None
Email: Aaron.A.Valoroso@erdc.dren.mil

To Run (Type): make threads

--------------------------------------------------------------------*/

#include "queue.h"

queue * q = NULL;
queue * q2 = NULL;

void * worker_threads() {

    int number = 0;

    while(1) {
        if (queue_size(q) > 0) {
            number = pop(q);
            printf("Looking at number: %d\n", number);
        } else {
            break;
        }
    }

    return NULL;
}

void * worker_threads2() {

    int number = 0;

    while(1) {
        if (queue_size(q2) > 0) {
            number = pop(q2);
            printf("Looking at number2: %d\n", number);
        } else {
            break;
        }
    }

    return NULL;
}

int main() { 

    q = create_queue();
    q2 = create_queue();

    pthread_t tid[4];
    
    for(int i = 0; i < 5; ++i)
        push(q, i * 10);
    
    for(int i = 0; i < 5; ++i)
        push(q2, i * 20);

    pthread_create(&tid[0], NULL, worker_threads, NULL);
    pthread_create(&tid[1], NULL, worker_threads, NULL);
    pthread_create(&tid[2], NULL, worker_threads2, NULL);
    pthread_create(&tid[3], NULL, worker_threads2, NULL);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL); 
    pthread_join(tid[2], NULL);
    pthread_join(tid[3], NULL);

    queue_cleanup(q);
    queue_cleanup(q2);
    return 0; 
}