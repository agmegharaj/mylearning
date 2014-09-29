/* pthread with mutex lock output goes below
nowon@nowon-HP-dx2480-MT-VP562PA:~/ubuntuone/misc/threads$ ./a.out 
counter value is 1 thread1
counter value is 2 thread2
 return values 0 0 
counter value is 2 in main
nowon@nowon-HP-dx2480-MT-VP562PA:~/ubuntuone/misc/threads$ 

pthread_mutex_trylock() - attempt to lock a mutex or will return error code if busy. Useful for preventing deadlock conditions. */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int counter;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void print_message(void *message) {
	pthread_mutex_lock(&mutex1);
	char *to_print;
	to_print = (char *) message;
	counter++;
	printf("counter value is %d %s\n", counter, to_print);	
	pthread_mutex_unlock(&mutex1);
}

int main()
{
	pthread_t thread1, thread2;
	char *message1 = "thread1", *message2 = "thread2";
	int ret1 = 0, ret2 = 0;
	ret1 = pthread_create(&thread1, NULL, (void *)&print_message, (void *) message1);
	ret2 = pthread_create(&thread2, NULL, (void *)&print_message, (void *) message2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	printf(" return values %d %d \n", ret1, ret2);
	printf("counter value is %d in main\n", counter);	
	return 0;
}
