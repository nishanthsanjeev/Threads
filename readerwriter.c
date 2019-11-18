#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex,wrt,rd;

int readercnt=0;

void* read(void* sem){

	sem_wait(&rd);
	
	sem_wait(&mutex);
	readercnt++;
	
	if(readercnt==1){
		sem_wait(&wrt);//tell writerss to wait
	}
	
	if(readercnt>2){
			int val;
			sem_getvalue(&wrt,&val);
			
			if(val==0){
				//let writing happen
				//never reaches here
			}
	}
	
	sem_post(&mutex);
	//reading time
	
	printf("I am reading %d\n",(int)sem);
	sem_wait(&mutex);
	
	readercnt--;
	
	if(readercnt==0)
		sem_post(&wrt);//continue writing
		
		
		
	sem_post(&mutex);
	
	sem_post(&rd);

}

void* write(void* sem){
	
	sem_wait(&wrt);//decrements
	//writing performed
	printf("I am writing %d\n",(int)sem);
	sem_post(&wrt);//increments


}




int main(){

	sem_init(&rd,0,5);
	sem_init(&mutex,0,1);
	sem_init(&wrt,0,1);
	
	pthread_t rtid[10],wtid[10];
	
	
	for(int i=0; i<6; i++){
	
		//pthread_create (&rtid[i],NULL,read,(void*)i);
		pthread_create (&wtid[i],NULL,write,(void*)i);
//		pthread_create (&rtid[i],NULL,read,(void*)i);
	}
	
	for(int i=0; i<6; i++){
	
		//pthread_create (&rtid[i],NULL,read,(void*)i);
		//pthread_create (&wtid[i],NULL,write,(void*)i);
		pthread_create (&rtid[i],NULL,read,(void*)i);
	}
	
	//wait also
	
	
	for(int i=0; i<6; i++){

		pthread_join(rtid[i],NULL);
		pthread_join(wtid[i],NULL);
	}
	

}
