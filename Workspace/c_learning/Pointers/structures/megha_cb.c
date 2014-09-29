#include<stdio.h>
#include<malloc.h>

//macros here
#define BUFFER_SIZE 8

// we can define some global variables here
int read_pointer;
int write_pointer;
int data_size;
int buffer[BUFFER_SIZE];

// prototype of the function goes here
void enter_data(int);
int buffer_full();
int buffer_empty();
void remove_data();

int main()
{
	int i = 0;
	int data_entered;
	int command_data = 0;
	for(i=0; i<BUFFER_SIZE; i++)
		buffer[i] = 0;

	while(command_data != 4) {
		printf(" please do press the valid inputs to access the buffer\n");
	 	printf("\t1 to enter data\n");
	 	printf("\t2 to remove data\n");
	 	printf("\t3 to show data\n");
	 	printf("\t4 to exit the program\n");

		scanf("%d", &command_data);

		if(command_data == 1) {
			printf("enter the data to be placed in the buffer\n");
			scanf("%d", &data_entered);
			//scanf("%d", &data_entered); // twise otherwise it will take enter as input, i dont know why
			if(!buffer_full()) {
				enter_data(data_entered);
			}
			else
				printf("buffer is full, please remove some data\n");
		}

		else if (command_data == 2) {
			if(!buffer_empty())
				remove_data();
			else
				printf("buffer is empty cannot reove data, please do add some\n");
		}

		else if (command_data ==3) {
			printf("data_size = %d\n read_pointer = %d\n write pointer = %d\n",data_size,read_pointer,write_pointer);
			for(i=0; i< BUFFER_SIZE; i++)
				printf("buffer[%d] = %d\n",i, buffer[i]);
		}

		else if (command_data ==4)
			exit(-1);
	}
}
int buffer_full()
{
	return((write_pointer == read_pointer) && (data_size == BUFFER_SIZE));
}

void enter_data(int data_entered)
{
	if(++write_pointer >= BUFFER_SIZE) 
		write_pointer = 0;
	buffer[write_pointer] = data_entered;
	data_size++;
}

void remove_data()
{
	if(++read_pointer >= BUFFER_SIZE)
		read_pointer = 0;
	buffer[read_pointer] = 0;
	data_size--;
}

int buffer_empty()
{
	return(write_pointer == read_pointer && data_size == 0);
}
