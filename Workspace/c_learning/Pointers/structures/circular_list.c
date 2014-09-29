#include<stdio.h>
#include<malloc.h>

struct node {
	int data;
	struct node *link;
};

int main()
{
	struct node *f,*r;
	r = f = NULL;
	add_cir(&f,&r,10);
	add_cir(&f,&r,20);
	add_cir(&f,&r,30);
	add_cir(&f,&r,40);
	add_cir(&f,&r,50);
	add_cir(&f,&r,60);
	add_cir(&f,&r,70);
	add_cir(&f,&r,80);
	display(&f);
	del_cir(&f,&r);
	del_cir(&f,&r);
	del_cir(&f,&r);
	del_cir(&f,&r);
	display(&f);
	return 0;
}

int add_cir(struct node **f, struct node **r, int data) {
	struct node *q,*temp;
	q = (struct node *) malloc(sizeof(struct node));
	q->data =data;
	if(*f == NULL)
		*f = q;
	else 
		(*r)->link = q;
	*r = q;
	(*r)->link = *f;
	return 0;
}

int del_cir(struct node **f,struct node **r) {
	struct node *q;
	if(*f == NULL)
		printf("circular linked list is empty\n");
	else if(*f == *r) {
		free(*f);
		*f = NULL;
		*r = NULL;
		return 0;
	}
	else {
		q = *f;
		*f = (*f)->link;
		(*r)->link = *f;
		free(q);
	}
	return 0;
}

int display(struct node **f) {
	printf("display\n");
	fflush(stdout);

	struct node *temp = NULL, *q = *f;
	while(q != temp) {
		printf("data = %d\n",q->data);
		q = q->link;
		temp = *f;	
	}
			
	return 0;
}	
