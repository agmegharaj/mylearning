#include <stdio.h>
#include <string.h>

main()
{

FILE *fp;
char another='y';
fp=fopen("employement.txt","w");
struct employement
{
char name[40];
int age;
};
struct employement e;

printf("enter employement details\n");

while(another=='y')
{
scanf("%s %d\n",e.name,&e.age);
fprintf(fp,"name=%s age=%d\n",e.name,e.age);
printf("do you want to enter another details\n");
//fflush ( stdin ) ;
another = getch( ) ;
}
fclose(fp);
}

