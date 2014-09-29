#include<stdio.h>


struct book
{
char name[50];
char author[50];
int pages;
};
display(struct book *);

main()
{
struct book b1={"let us c", "YPR",101};
struct book *p;

p=&b1;

display(p);
}

display(struct book *p)
{

printf(" %s\n %s\n %d\n",p->name,p->author,p->pages);
}
