/*-------------------------------------------------------------------
Author: Aaron Anthony Valoroso
Date: November 3rd, 2019
License: None
Email: valoroso99@gmail.com
--------------------------------------------------------------------*/
#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if THREADS
    #include <pthread.h>
#endif

#define queue_datatype int

// Debugging Color Specification. 
#define O_NOR  "\x1B[0m"     // NORMAL
#define O_ERR  "\x1B[31m"    // RED
#define O_SUC  "\x1B[32m"    // GREEN
#define O_WAR  "\x1B[33m"    // YELLOW
#define O_BEG  "\x1B[34m"    // BLUE
#define O_DEB  "\x1B[35m"    // Magenta
#define O_END  "\x1B[36m"    // CYAN

struct QNode { 
    queue_datatype key; 
    struct QNode* next; 
}; 

struct Queue_Container { 
    int size;
    struct QNode *front, *rear; 
}; 

typedef struct QNode node;
typedef struct Queue_Container queue;

queue * create_queue();
void push(queue * q, queue_datatype k);
queue_datatype pop(queue * q);
queue_datatype queue_size(queue * q);
void list_queue(queue * node);
void queue_cleanup(queue * q);
void queue_util_debugger();

#endif
