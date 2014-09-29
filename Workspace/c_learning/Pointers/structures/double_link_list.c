#include<stdio.h>
#include<malloc.h>

struct node {
	int data;
	struct node *prev;
	struct node *next;
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
	struct node *temp, *r;
	temp = *q;
	if(temp == NULL) {
		temp = malloc(sizeof(struct node));
		temp->prev = NULL;
		temp->data = num;
		temp->next = NULL;
		(*q) = temp;
		return 0;
	}
	else {
		while(temp->next != NULL ) 
			temp = temp->next;
		r = malloc(sizeof(struct node));
		r->next = NULL;
		r->data = num;
		r->prev = temp;
		temp->next = r;
	}
	return 0;
}

int display(struct node **q) {
	struct node *temp;
	temp = *q;
	while(temp != NULL) {
		printf("data in listt = %d\n", temp->data);
		temp = temp->next;
	}
	return 0;
}

int add_beg(struct node **q, int num) {
	struct node *temp, *r;
	temp = *q;
	r = malloc(sizeof(struct node));
	r->prev = NULL;
	r->data = num;
	r->next = temp;
	temp->prev = r;
	*q = r;
	return 0;
}

int add_after(struct node **q, int loc, int num) {
	struct node *temp, *r;
	int i;
	temp = *q;
	for(i = 0; i<loc; i++)
		temp = temp->next;
	r = malloc(sizeof(struct node));
	r->prev = temp;/* alwaysm first settele for r than for temp*/
	r->data = num;
	r->next = temp->next;
	temp->next->prev = r;
	temp->next = r;
	return 0;
}

int delete_beg(struct node **q) {
	struct node *temp;
	temp = *q;
	temp->next->prev = NULL;
	(*q) = temp->next;
	free(temp);
	return 0;
}

int delete_end(struct node **q) {
	struct node *temp;
	temp = *q;
	while(temp->next != NULL) 
		temp = temp->next;
	temp->prev->next = NULL;
	free(temp);
	return 0;
}

int delete_num(struct node **q,int num) {
	struct node *temp;
	temp = *q;
	while(temp != NULL) {
		if(temp->data == num) {
			if((*q) == temp) {
				temp->next->prev = NULL;
				(*q) = temp->next;
				free(temp);
				return 0;
			}
			else {
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				free(temp);
				return 0;
			}
		}
		temp = temp->next;
	}
	return 0;
}

/* always when adding settle things first with respect to the adding data(r), than temp*/
	
