#include<stdio.h>
#include<malloc.h>

struct node {
int data;
struct node *next;
};

int enque (struct node **start, int data) {
	struct node *temp;
	if(start == NULL) {
		printf("i am in the first cycle\n");
		temp = (struct node *) malloc (sizeof(struct node));
		temp->data = data;
		temp->next = NULL;
		*start = temp;
		return 0;
	}
	temp = (struct node *) malloc (sizeof(struct node));
	temp->data = data;
	temp->next = *start;
	*start = temp;
	return 0;
}

int display(struct node *start) {
	struct node *temp;
	temp = start;
	while(temp != NULL) {
		printf("data in queue:display is %d\n",temp->data);
		temp = temp->next;
	}
}

int deque(struct node **start) {
	struct node *temp,*previous;
	temp = *start;
	while(temp->next != NULL) {
		previous = temp;
		temp = temp->next;
	}
	previous->next = NULL;
	free(temp);
}

int main()
{
	struct node *start;
	start = NULL;
	enque(&start,10);
	enque(&start,20);
	enque(&start,30);
	enque(&start,40);
	enque(&start,50);
	enque(&start,60);
	display(start);
	printf("finished put\n");
	deque(&start);
	deque(&start);
	deque(&start);
	deque(&start);
	display(start);
	deque(&start);
	deque(&start);
	display(start);
	return 0;
}

