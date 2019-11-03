/*-------------------------------------------------------------------
Author: Aaron Anthony Valoroso
Date: November 3rd, 2019
License: None
Email: Aaron.A.Valoroso@erdc.dren.mil

To Run (Type): make

--------------------------------------------------------------------*/
#include "queue.h"

int main() { 

    queue * q = create_queue();
    queue * q2 = create_queue();
    
    int i = 0, length = 5;
    for(i = 0; i < length; ++i)
        push(q, i * 10);
    
    for(i = 0; i < length; ++i)
        push(q2, i * 20);

    for(i = 0; i < length; ++i)
        printf("Looking at: %d\n", pop(q));
    
    for(i = 0; i < length; ++i)
        printf("Looking at2: %d\n", pop(q));

    queue_cleanup(q);
    queue_cleanup(q2);
    return 0; 
} 