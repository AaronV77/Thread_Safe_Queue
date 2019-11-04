/*-------------------------------------------------------------------
Author: Aaron Anthony Valoroso
Date: November 3rd, 2019
License: None
Email: Aaron.A.Valoroso@erdc.dren.mil

Useful URLs:
http://www.ccs.neu.edu/home/skotthe/classes/cs5600/fall/2015/labs/intro-check.html
https://libcheck.github.io/check/index.html
--------------------------------------------------------------------*/
#include <check.h>
#include "../queue.h"        
#include <stdlib.h>
#include <pthread.h>

queue * q2 = NULL;

void * worker_threads() {

    int number = 0;

    while(1) {
        if (queue_size(q2) > 0)
            number = pop(q2);
        else
            break;
    }

    return NULL;
}

START_TEST(basic_functions) {
    int number = 0;
    queue * q = create_queue();
    push(q, 10);
    push(q, 20);
    push(q, 30);
    number = queue_size(q);
    ck_assert_int_eq(number, 3);
    number = pop(q);
    ck_assert_int_eq(number, 10);
    queue_cleanup(q);
} END_TEST

START_TEST(basic_thread_functions) {
    pthread_t tid[2];
     q2 = create_queue();
    
    for(int i = 0; i < 5; ++i)
        push(q2, i * 20);

    pthread_create(&tid[0], NULL, worker_threads, NULL);
    pthread_create(&tid[1], NULL, worker_threads, NULL);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

     queue_cleanup(q2);
} END_TEST


Suite * queue_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("queue");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, basic_functions);
    suite_add_tcase(s, tc_core);

    tcase_add_test(tc_core, basic_thread_functions);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
  int no_failed = 0;                   
  Suite *s;                            
  SRunner *runner;                     

  s = queue_suite();                   
  runner = srunner_create(s);          

  srunner_run_all(runner, CK_NORMAL);  
  no_failed = srunner_ntests_failed(runner); 
  srunner_free(runner);

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;  
}