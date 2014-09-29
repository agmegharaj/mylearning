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
	reverse_list(&p);
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

int reverse_list(struct node **q) {
	struct node *head, *next, *cursor;
	head = *q;
	cursor = NULL;
	while(head != NULL) {
		next = head->link;
		head->link =cursor;
		cursor = head;
		head = next;
	}
	(*q) = cursor;
	return 0;
}
	

