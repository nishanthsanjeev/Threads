#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex,wrt;
//int data =0;
int readercnt=0;

void* read(void* sem){

	sem_wait(&mutex);
	readercnt++;
	
	if(readercnt==1){
		sem_wait(&wrt);//tell writerss to wait
	}
	
	sem_post(&mutex);
	//reading time
	
	printf("I am reading %d\n",(int)sem);
	sem_post(&mutex);
	
	readercnt--;
	
	if(readercnt==0)
		sem_post(&wrt);
		
		
	sem_post(&mutex);

}

void* write(void* sem){
	
	sem_wait(&wrt);
	//writing performed
	printf("I am writing %d\n",(int)sem);
	sem_post(&wrt);


}




int main(){

	sem_init(&mutex,0,1);
	sem_init(&wrt,0,1);
	
	pthread_t rtid[10],wtid[10];
	
	
	for(int i=0; i<3; i++){
	
		//pthread_create (&rtid[i],NULL,read,(void*)i);
		pthread_create (&wtid[i],NULL,write,(void*)i);
		pthread_create (&rtid[i],NULL,read,(void*)i);
	}
	
	
	//wait also
	
	
	for(int i=0; i<3; i++){
		pthread_join(rtid[i],NULL);
		pthread_join(wtid[i],NULL);
	}
	

}
