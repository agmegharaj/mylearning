#include<stdio.h>
#include<malloc.h>

struct node {
	int data;
	struct node *next;
};

int insert(struct node *start, int data) {
	struct node *pointer; 
	pointer = start;
	while(pointer->next != start) {
		pointer = pointer->next;
	}
	pointer->next = (struct node *) malloc(sizeof(struct node));
	pointer = pointer->next;
	pointer->data = data;
	pointer->next = start;
	return 0;
}

int delete(struct node *start, int data) {
	struct node *pointer, *previous;
	pointer = start;
	while ((pointer->next != start) && (pointer->next->data != data)) {
		previous = pointer;
		pointer = pointer->next;
	}
	if(pointer->next == start) {
		printf("data not present to delete\n");
		return 0;
	}
	previous = pointer;
	pointer = pointer->next;
	previous->next = pointer->next;
	free(pointer);
	return 0;
}

void print_data(struct node *start,struct node *pointer)
{
        if(pointer==start)
        {
                return;
        }
        printf("%d ",pointer->data);
        print_data(start,pointer->next);
}

int find(struct node *start, int data) {
	struct node *pointer;
	pointer = start;
	pointer =  pointer -> next; //First node is dummy node.
	while(pointer != start) {
		if(pointer->data == data) {
			printf("data found\n");
			return 0;		
		}
		else 
			pointer = pointer->next; 
	}
	printf("data not found in the list\n");
	return 0;
}

int main()
{
	int querry = 0;
	struct node *start, *temp;
	start = (struct node *) malloc (sizeof(struct node));
	//temp = (struct node *) malloc (sizeof(struct node));
	/* we assume starting node as dummy node*/
	//start->next = temp;
	temp = start;
	temp->next = start;
	while(1) {
		printf("please enter the query command you want to do\n");
		printf("\t 1 to insert\n");
		printf("\t 2 to delete\n");
		printf("\t 3 to print\n");
		printf("\t 4 to find\n");
		scanf("%d",&querry);
	
		if(querry == 1) {
			int data = 0;
			scanf("%d",&data);
			insert(start,data);
		}

		else if (querry == 2) {
			int data = 0;
			scanf("%d",&data);
			delete(start,data);
		}

		else if (querry == 3) {
			print_data(start,start->next);
		}

		else if (querry == 4) {
			int data = 0;
			scanf("%d",&data);
			find(start,data);
		}
	}
	return 0;
}
		
	
		
