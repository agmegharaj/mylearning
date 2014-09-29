#include <stdio.h>

main()
{

union checking
{
char a;
char ab;
int b;
int ba;
float c;
};

union checking check;

printf ("enter char\n");
scanf ("%c",&check.a);

printf ("enter second char\n");
scanf ("%c",&check.ab);


printf ("enter int\n");
scanf ("%d",&check.b);

printf ("enter second int int\n");
scanf ("%d",&check.ba);


/*
printf ("enter float\n");
scanf ("%f",&check.c);
*/
/* now print the values*/
printf ("char is %c\n",check.a);
printf ("second char is char is %c\n",check.ab);

printf ("int is %d\n",check.b);
printf ("float is %f\n",check.c);
}

