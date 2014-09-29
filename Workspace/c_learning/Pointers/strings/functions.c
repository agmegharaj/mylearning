#include<stdio.h>
#include<string.h>

main()
{

char str1[]="megharaj";
char str2[]=" don of the world";
char str3[50];

int l,k;

l=strlen(str1);
printf("string length of str1 is %d\n",l);

strcpy(str3,str2);
printf("printf %s\n",str3);

k=strcmp(str3,str2);
printf("after copying value of k  is  %d\n",k);

k=strcmp(str1,str2);
printf("after copying value of k  is  %d\n",k);

strcat(str1,str2);
printf("printf %s\n",str1);

}
