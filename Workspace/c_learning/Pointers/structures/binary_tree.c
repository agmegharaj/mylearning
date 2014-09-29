#include<stdio.h>
#include<malloc.h>

//int insert(struct btreenode **, int);

struct btreenode {
	struct node *leftchild;
	int data;
	struct node *rightchild;
};

int main() 
{
	struct btreenode *bt;
	bt = NULL;
	insert(&bt,20);
	insert(&bt,17);
	insert(&bt,6);
	insert(&bt,8);
	insert(&bt,13);
	insert(&bt,12);
	insert(&bt,5);
	search(&bt,8);
	search(&bt,67);
	search(&bt,6);
	search(&bt,90);
	return 0;
}
	
int insert(struct btreenode **sr, int data) {
	if(*sr == NULL) {
		*sr = (struct btreenode *) malloc(sizeof(struct btreenode));
		(*sr)->leftchild = NULL;
		(*sr)->data = data;
		(*sr)->rightchild = NULL;
		return 0;
	}
	else {
		if(data < (*sr)->data)
			insert(&((*sr)->leftchild),data);
		else
			insert(&((*sr)->rightchild),data);
	}
	return 0;
}

int search(struct btreenode **sr,int data) {
	struct btreenode *temp;
	temp = *sr;
	while(temp != NULL) {
		if(temp->data == data) {
			printf("data foud\n");
			return 0;
		}
		else if (temp->data > data)
			temp = temp->leftchild;
		else
			temp = temp->rightchild;
	}
	printf("data not found\n");
	return 0;
}
