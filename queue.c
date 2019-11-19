/*-------------------------------------------------------------------
Author: Aaron Anthony Valoroso
Date: November 3rd, 2019
License: None
Email: valoroso99@gmail.com
--------------------------------------------------------------------*/
#include "queue.h"
 
 // Global Locking mechanism that comes pre-initialized.
 #if THREADS
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
#endif

// Global var to turn the debugger on and off.
int queue_debugger = 0;

//-----------------------------------------------------------------------------------------------------
/**
 * This function sets up the queue data structure for the whole library. You are able to have 
 * more than one queue at any given time, just make sure to clean up your toys when you are 
 * done playing with them. This function is not thread safe and is intended to be ran by the 
 * master thread. If there is a need to make this funciton thread safe, please contact me.
 */
queue * create_queue() { 
    if (queue_debugger) printf("\t%sEntering create_queue()%s\n", O_BEG, O_NOR);
    queue * q = calloc(1, sizeof(queue));
    q->front = q->rear = NULL;
    if (queue_debugger) printf("\t%sLeaving create_queue()%s\n", O_END, O_NOR);
    return q; 
} 

//-----------------------------------------------------------------------------------------------------
/**
 * This function is thread safe and will add a node to the end of your queue structure and update
 * all the pointers needed to do so. How this function works is by checking to see if the incoming 
 * structure is or not empty. If it is empty, then I make sure to set both the from and back pointers 
 * of the queue, and if it is not empty, then I just update the caboose to include the new node. At
 * the end I make sure to increase the size of the queue structure.
 *
 * \param[in] q will be the created queue structure that has memory.
 * \param[in] k is the number that will be stored.
 */
void push(queue * q, queue_datatype k) { 

#if THREADS
    pthread_mutex_lock(&lock);
#endif
    if (queue_debugger) printf("\t%sEntering push()%s\n", O_BEG, O_NOR);
    node * temp = calloc(1, sizeof(node));
    temp->key = k; 
    temp->next = NULL; 

    if (q->front == NULL) {
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
    q->size++;
    if (queue_debugger) printf("\t%sLeaving push()%s\n", O_END, O_NOR);
#if THREADS
    pthread_mutex_lock(&lock);
#endif

    return;
} 

//-----------------------------------------------------------------------------------------------------
/**
 * This function is thread safe and will remove a node from the front of the queue structure and update
 * all the associated pointer. How this function works is by checking to see if the structure is empt 
 * or not. If not, then the system will grab the number being popped, make another pointer to the node 
 * holding the number, and associate a new front node. Once that is completed, the system will free the 
 * copy of the pointer to temp and then decrement the queue structure size.
 *
 * \param[in] q will be the created queue structure that has memory.
 * \param[out] return (on success) the stored number from the popped node.
 * \param[out] return (on failure) a zero.
 */
queue_datatype pop(queue * q) { 

#if THREADS
    pthread_mutex_lock(&lock);
#endif
    if (queue_debugger) printf("\t%sEntering pop()%s\n", O_BEG, O_NOR);
    if (q->front == NULL) {
        if (queue_debugger) printf("\t%sLeaving pop()%s\n", O_END, O_NOR);
        return 0; 
    }
    
    queue_datatype stored_number = q->front->key;
    node * temp = q->front;
    q->front = q->front->next;
    free(temp);
    q->size--;

    if (q->front == NULL)
        q->rear = NULL;
    if (queue_debugger) printf("\t%sLeaving pop()%s\n", O_END, O_NOR);
#if THREADS
    pthread_mutex_unlock(&lock);
#endif

    return stored_number; 
}

//-----------------------------------------------------------------------------------------------------
/**
 * This function is thread safe and will give you the size of the queue. How this function works is 
 * by checking to see if the structure is empt or not. If not, then the system will grab the size
 * of the queue structure that the user or system is looking at.
 *
 * \param[in] q will be the created queue structure that has memory.
 * \param[out] return (on success) the size of the queue structure.
 * \param[out] return (on failure) a zero.
 */
queue_datatype queue_size(queue * q) {

#if THREADS
    pthread_mutex_lock(&lock);
#endif
    if (queue_debugger) printf("\t%sEntering queue_size()%s\n", O_BEG, O_NOR);
    if (q->front == NULL) 
        return 0; 
    
    queue_datatype stored_number = q->size;
    if (queue_debugger) printf("\t%sLeaving queue_size()%s\n", O_END, O_NOR);
#if THREADS
    pthread_mutex_unlock(&lock);
#endif

    return stored_number; 
}

//-----------------------------------------------------------------------------------------------------
/**
 * This function is not thread safe and will print each nodes key by looping through the entire queue 
 * structure. How this function works is by looping through the entire queue, starting at the front
 * and ending at the rear.
 *
 * \param[in] q will be the created queue structure that has memory.
 */
void list_queue(queue * q) {

    if (queue_debugger) printf("\t%sEntering list_queue()%s\n", O_BEG, O_NOR);
    node * temp = q->front;
    while (temp != NULL) {
        printf("The proc: %d\n", temp->key);
        temp = temp->next;
    }
    if (queue_debugger) printf("\t%sLeaving list_queue()%s\n", O_END, O_NOR);

    return;
}

//-----------------------------------------------------------------------------------------------------
/**
 * This function is not thread safe and will cleanup all the associated pointers to your 
 * queue structure. There is not need to clean up the rear and front pointers in the queue
 * structure because the nodes that they point too, are being deallocated.
 *
 * \param[in] q will be the created queue structure that has memory.
 */
void queue_cleanup(queue * q) {

    if (queue_debugger) printf("\t%sEntering queue_cleanup()%s\n", O_BEG, O_NOR);
    node * temp;
    while (q->front != NULL) {
        temp = q->front->next;
        free(q->front);
        q->front = temp;
    }
    free(q);
    if (queue_debugger) printf("\t%sLeaving queue_cleanup()%s\n", O_END, O_NOR);

    return;
}

//-----------------------------------------------------------------------------------------------------
/**
 * This function will turn the debug statments on and off for this file. The purpose for this function is
 * to make it easier for new people to come into this source code and get familiar with it faster or be
 * able to see where the system is crashing quickly. How this code works is by simply changing a global
 * int variable to zero (off) and one (on).
 */
void queue_util_debugger() {
    if (queue_debugger == 0)
        queue_debugger = 1;
    else
        queue_debugger = 0;
    
    return;
}
