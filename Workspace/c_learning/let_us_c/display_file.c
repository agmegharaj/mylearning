#include <stdio.h>

main()
{
FILE *fp;
char ch;
fp=fopen("7-4.txt","r");

while(1)
{
ch=fgetc(fp);

if( ch ==EOF)
break;
else
printf("%c",ch);
}
fclose(fp);

}

/* strings in double quote, wheras character in single quotes*/

