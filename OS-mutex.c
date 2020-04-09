#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;
//int amount=10;
 struct account{
    long int accountnum;
	int balance;
	pthread_mutex_t mylock;
};

void *transfer_from(void *ptr)
{
	pthread_mutex_lock(&mylock);
	printf("account no.=%d\n",((struct account*)ptr)->accountnum);
	printf("balance=%d\n",((struct account*)ptr)->balance);
	pthread_mutex_unlock(&mylock);
}
void *transfer_to(void *ptr)
{
	pthread_mutex_lock(&mylock);
	printf("account no.=%d\n",((struct account*)ptr)->accountnum);
	printf("balance=%d\n",((struct account*)ptr)->balance);
	pthread_mutex_unlock(&mylock);
}


int main(void){
    struct account *from =(struct account *)malloc (sizeof(struct account));
    printf("*************************************************\n");
     printf("*************TRANSFER MONEY**********************\n");
	printf("Enter your Account no.\n");
	scanf("%li",&from->accountnum);
	if (from->accountnum<=0){
		printf("invalid input");
		exit(0);
	}
	from->balance=10000;
	struct account *to =(struct account *)malloc (sizeof(struct account));
	printf("Enter Account no.\n");
	scanf("%li",&to->accountnum);
		if (to->accountnum<=0){
		printf("invalid input");
		exit(0);
	}
	printf("*************************************************\n");
	printf("*************************************************\n");
	to->balance=1000;
	printf("Enter Amount to be transfered no.\n"); 
    int amount;
	scanf("%d",&amount);
	struct account *lower = (from->accountnum < to->accountnum)?from:to;
    struct account *higher = (from->accountnum < to->accountnum)?to:from;
    pthread_mutex_lock(&(lower->mylock));
    pthread_mutex_lock(&(higher->mylock));
    ((struct account*)from)->balance -= amount;
    ((struct account*)to)->balance += amount;
    pthread_mutex_unlock(&(lower->mylock));
    pthread_mutex_unlock(&(higher->mylock));
	if(from->balance<amount){
		printf("insufficient balance");
		exit(0);
	}  
	pthread_t thread_id1,thread_id2;
    printf("before thread1\n");
    pthread_create(&thread_id1,NULL,transfer_from,(void*)from);
    pthread_join(thread_id1,NULL);
	pthread_create(&thread_id2,NULL,transfer_to,(void*)to);
	pthread_join(thread_id2,NULL);
    printf("after thread2\n");
    printf("********Money Transfer Successful***************\n");
    printf("*************************************************\n");
    exit(0);
	
}
