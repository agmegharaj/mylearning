/* basic create and work*/
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void print_message(void * message) {
	char *to_print;
	to_print = (char *) message;
	printf("%s\n", to_print);
	return to_print;
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
	return 0;
}
