#include<stdio.h>


main()
{
int a[5]={0,1,2,3,4};
int i=0;

while(i<5)
{

printf(" address of of element = %u\t",&a[i]);
printf(" value of element of of element = %d\n",a[i]);
printf(" value of element of of element = %d\n",i[a]);
printf(" value of element of of element = %d\n",*(a+i));
printf(" value of element of of element = %d\n",*(i+a));
i++;

}
}

/* dont forget to initialize auto variable to zero*/
