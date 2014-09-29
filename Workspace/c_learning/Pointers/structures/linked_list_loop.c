#include<stdio.h>
#include<malloc.h>


struct node {
int data;
struct node *next;
};

int main() 
{
	struct node *start = NULL;
	add(&start,10);
	add(&start,20);
	add(&start,30);
	add(&start,40);
	add(&start,50);
	add(&start,60);
	add(&start,70);
	add(&start,80);
	display(start);
	printf("after adding loop\n");
	start->next->next->next->next = start->next->next; /* just creating a loop*/
	//display(start); /* when there is loop dont call display function goes to infinite loop*/
	detect_loop_remove(&start);
	display(start);
	return 0;
}

int add(struct node **start,int data) {
	struct node *temp,*add;
	printf("add\n");
	fflush(stdout);
	if(*start == NULL) {
		add = (struct node *) malloc(sizeof(struct node));
		add->data = data;
		add->next = NULL;
		*start = add;
		return 0;
	}
	temp = *start;
	while(temp->next != NULL) 
		temp = temp->next;
	add = (struct node *)malloc(sizeof(struct node));
	add->data = data;
	add->next = NULL;
	temp->next = add;
	return 0;
}

int display(struct node *start) {
	struct node *temp;
	temp = start;
	while(temp != NULL) {
		printf("data in list = %d\n",temp->data);
		fflush(stdout);
		temp = temp->next;
	}
	return 0;
}

int detect_loop_remove(struct node **start) {
	struct node *slow = *start, *fast = *start;
	while((slow) && (fast) && (fast->next)) {
		slow = slow->next;
		fast = fast->next->next;
		if(slow = fast) {
			removeLoop(slow,*start);
			printf("loop found\n");
			return 0;
		}
	}
	return 0;
}

int removeLoop(struct node *loop_node, struct node *head)
{
	struct node *ptr1;
   	struct node *ptr2;
	ptr1 = head;
	while(1) {
		ptr2 = loop_node;
		while(ptr2->next != loop_node && ptr2->next != ptr1) {
			ptr2 = ptr2->next;  
		}
		if(ptr2->next == ptr1)
			break;
		else
			ptr1 = ptr1->next;		
	}
	ptr2->next = NULL;
	return 0;
}

