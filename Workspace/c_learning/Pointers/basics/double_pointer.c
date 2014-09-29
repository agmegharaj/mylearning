#include <stdio.h>

main()
{
int i=3;
int *j,**k;

j=&i;
k=&j;

printf(" addreess of i =%u\n",&i);
printf(" addreess of i =%u\n",j);
printf(" addreess of i =%u\n",*k);
printf(" addreess of j =%u\n",&j);
printf(" addreess of j =%u\n",k);
printf(" addreess of k =%u\n",&k);

printf(" value of j =%u\n",j);
printf(" value of k =%u\n",k);
printf(" value of i =%u\n",i);
printf(" value of i =%u\n",*(&i));
printf(" value of i =%u\n",*j);
printf(" value of i =%u\n",**k);

}
