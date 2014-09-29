#include <stdio.h>
int main()
{
    float f = 0.1;
    if (f == 0.1)
      printf("True");
    else
      printf("False");
    return 0;
}
//The output is false.

#include <stdio.h>
int main()
{
    float f = 0.1;
    if (f == (float)0.1)
      printf("True");
    else
      printf("False");
    return 0;
}

// the output is true.
/* 0.1 literal is double. You loose precision here float f = 0.1;
You could say we loose precision during comparison again, so why isn't f == 0.1 true anyway? Because float extends to double, not the opposite. In C smaller type always extends to the bigger one.

Possible solutions:

    use double instead of float as a type of f.
    use cast as in your 2nd example
    use float literals - replace all 0.1 with 0.1f
*/
