#include<stdio.h>
#include<malloc.h>

struct node {
int data;
struct node *next;
};

int put (struct node **start, int data) {
	struct node *temp;
	if(start == NULL) {
		printf("i am in the first cycle\n");
		temp = (struct node *) malloc (sizeof(struct node));
		temp->data = data;
		temp->next = NULL;
		*start = temp;
		//printf("data in stack is %d\n",*start->data);
		return 0;
	}
	temp = (struct node *) malloc (sizeof(struct node));
	temp->data = data;
	temp->next = *start;
	*start = temp;
	return 0;
}

int pop(struct node **start) {
	struct node *temp;
	temp = *start;
	*start = temp->next;
	free(temp);
	return 0;		
}

int display(struct node *start) {
	struct node *temp;
	temp = start;
	while(temp != NULL) {
		printf("data in stack:display is %d\n",temp->data);
		temp = temp->next;
	}
}

/*int display(struct node *start) {
return 0;
}*/


int main()
{
	struct node *start;
	start = NULL;
	put(&start,10);
	put(&start,20);
	put(&start,30);
	put(&start,40);
	put(&start,50);
	put(&start,60);
	display(start);
	printf("finished put\n");
	pop(&start);
	pop(&start);
	pop(&start);
	pop(&start);
	display(start);
	pop(&start);
	pop(&start);
	display(start);
	return 0;
}

/* *start->next this thing does not work. foe that to work we need to write (*q)->next*/
