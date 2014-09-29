#include<stdio.h>
#include<malloc.h>


struct node {
	int data;
	struct node *link;
};

int main()
{
	struct node *p;
	p = NULL;
	append(&p, 1);
	append(&p, 2);
	append(&p, 3);
	append(&p, 4);
	append(&p, 5);
	printf("display appended data\n");
	display(&p);
	add_beg(&p,7);
	printf("display add beggining 7 \n");
	display(&p);
	add_after(&p, 2,10);
	printf("display add after 2 pos, 10 \n");
	display(&p);
	delete_beg(&p);
	printf("delete beggining \n");
	display(&p);
	delete_end(&p);
	printf("delete end \n");
	display(&p);
	delete_num(&p, 10);
	printf("delete num 10 \n");
	display(&p);
	return 0;
}

int append(struct node **q, int num) {
	struct node *temp,*r;
	temp = *q;
	if(temp == NULL) {
		temp = malloc(sizeof(struct node));
		temp->data = num;
		temp->link = NULL;
		*q = temp;
	}
	else {
		while(temp->link != NULL)
			temp = temp->link;
		r = malloc(sizeof(struct node));
		r->data = num;
		temp->link = r;
		r->link = NULL;
	}
	return 0;
}

int display(struct node **q) {
	struct node *temp;
	temp = *q;
	while(temp != NULL) {
		printf("data in listt = %d\n", temp->data);
		temp = temp->link;
	}
	return 0;
}

int add_beg(struct node **q, int num) {
	struct node *temp;
	temp = malloc(sizeof(struct node));
	temp->data = num;
	temp->link = (*q);
	(*q) = temp;
	return 0;
}

int add_after(struct node **q, int loc, int num) {
	struct node *temp, *r;
	int i;
	temp = *q;
	for(i = 0; i<loc; i++)
		temp = temp->link;
	r = malloc(sizeof(struct node));
	r->data = num;
	r->link = temp->link;
	temp->link = r;
	return 0;
}

int delete_beg(struct node **q) {
	struct node *temp;
	temp = *q;
	(*q) = temp->link;
	free(temp);
	return 0;
}

int delete_end(struct node **q) {
	struct node *temp, *old;
	temp = *q;
	while(temp->link != NULL) {
		old = temp;
		temp = temp->link;
	}
	free(temp);
	old->link = NULL;
	return 0;
}

int delete_num(struct node **q, int num) {
	struct node *temp, *old;
	temp = *q;
	while(temp != NULL) {
		if(temp->data == num) {
			if(temp == *q) {
				*q = temp->link;
				free(temp);
				return 0;
			}
			else {
				old->link = temp->link;
				free(temp);
				return 0;
			}
		}
		old = temp;
		temp = temp->link;
	}
	printf("number to delete was not found\n");
	return 0;
}
				

	
		
	
