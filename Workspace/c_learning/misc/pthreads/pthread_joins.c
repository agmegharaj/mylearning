/*pthread code to show join, it is used wait fof the threads to finish.
here goes the output if join is not used
pthread_self() is used to return identifier of current thread 
nowon@nowon-HP-dx2480-MT-VP562PA:~/ubuntuone/misc/threads$ ./a.out 
thread id =139996834977536
counter value is 1
thread id =139996826584832
counter value is 2
 return values 0 0 
counter value is 2 in main
nowon@nowon-HP-dx2480-MT-VP562PA:~/ubuntuone/misc/threads$ 
the process terminates at 2 thread itself without waiting other threads to complete
 */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define NO_THREADS 10//100000
int counter;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void print_message() {
	pthread_mutex_lock(&mutex1);
	printf("thread id =%ld\n", pthread_self());
	counter++;
	printf("counter value is %d\n", counter);	
	pthread_mutex_unlock(&mutex1);
}

int main()
{
	pthread_t thread[NO_THREADS];
	char *message1 = "thread1", *message2 = "thread2";
	int ret1 = 0, ret2 = 0,i;
	for(i = 0; i<NO_THREADS; i++) {
		if(ret1 = pthread_create(&thread[i], NULL, (void *)&print_message, NULL)) {
			printf("failed to create pthread for i = %d\n",i);
			return 0;
		}
	}
	for(i = 0; i<NO_THREADS; i++)
		pthread_join(thread[i], NULL);
	
	printf(" return values %d %d \n", ret1, ret2);
	printf("counter value is %d in main\n", counter);	
	return 0;
}
