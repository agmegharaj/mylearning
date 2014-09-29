#include<stdio.h>
#include<string.h>
xcpy(char*,char *);

main()
{

char str1[]="megharaj";
char str2[30];

xcpy(str1,str2);


printf("1 of = %s\n",str1);
printf("2 of = %s\n",str2);

}

xcpy(char *s,char *t)
{

while(*s !='\0')
{
*t=*s;

s++;
t++;
}
*t='\0';


}
