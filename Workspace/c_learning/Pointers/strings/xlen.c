#include<stdio.h>
#include<string.h>
xlen(char*);

main()
{

char str1[]="megharaj";
 int len1, len2;

len1=xlen(str1);
len2=xlen("megharaj is a don");


printf("len1 of %s = %d\n",str1,len1);
printf("len2 of %s = %d\n","megharaj is a don",len2);

}

xlen(char *s)
{
int i=0;
while(*s !='\0')
{

i++;
s++;
}

return i;

}
