#include <stdio.h>

void test_stack_growth_direction(recursion_depth) {
  int local_int1;
  printf("%p\n", &local_int1);
  if (recursion_depth < 10) {
    test_stack_growth_direction(recursion_depth + 1);
  }
}

main () {
  test_stack_growth_direction(0);
}
