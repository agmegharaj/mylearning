#include <stdio.h>

main()
{
FILE *fs,*ft;
char ch;
fs=fopen("7-4.txt","r");
ft=fopen("7-4_1.txt","w");
if(ft==NULL)
printf("file cannot be open\n");

while(1)
{
ch=fgetc(fs);

if( ch ==EOF)
break;
else
fputc(ch,ft);
}
fclose(ft);
fclose(fs);
}

/* strings in double quote, wheras character in single quotes*/

