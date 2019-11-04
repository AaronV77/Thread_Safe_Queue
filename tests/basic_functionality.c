#include <check.h>
#include "../queue.h"        
#include <stdlib.h>


START_TEST(test_queue_fill) {
    int number = 0;
    queue * q = create_queue();
    push(q, 10);
    number = pop(q);
    printf("The number: %d\n", number);
    ck_assert_int_eq(number, 20);
    queue_cleanup(q);
} END_TEST


Suite * queue_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("queue");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_queue_fill);
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