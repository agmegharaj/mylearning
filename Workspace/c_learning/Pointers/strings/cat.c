#include<stdio.h>
#include<string.h>
void xcat(char*,char *,int,int);

main()
{

char str1[50]="megharaj";
char str2[]=" is a don";

int len1,len2;
len1=strlen(str1);
len2=strlen(str2);
printf("1 of = %d\n",len1);
printf("1 of = %d\n",len2);
printf("before calling functions\n");
printf("1 of = %s\n",str1);
printf("2 of = %s\n",str2);



xcat(str1,str2,len1,len2);


printf("1 of = %s\n",str1);
printf("2 of = %s\n",str2);

}

void xcat(char *s,char *t,int len1,int len2)
{
	int i=0;
	s = s + len1;
	while(i<len2) {
		if(*t!='\0')
			*s=*t;
		s++;
		t++;
		i++;

	}// while 1
}//

// written by ag megharaj

