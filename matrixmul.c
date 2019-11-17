#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int a[3][3];
int b[3][2];
	int c[3][2];

typedef struct{int x; int y;}pair;

void* each(void* ptr){
		
	
	int sum=0;
	
	for(int k=0; k<3; k++){
	
		sum+=a[((pair*)ptr)->x][k]*b[k][((pair*)ptr)->y];
	}
	
	return (void*)sum;
	
}


void* thrmain(void* argument){


	
	pthread_t th[3][2];
	
	pair pass[3][2];
	
	
	
	for(int i=0; i<3; i++){
		for(int j=0; j<2; j++){
		
			
			pass[i][j].x=i;
			pass[i][j].y=j;
			
			pthread_create (&th[i][j],NULL,each,&pass[i][j]);
			
		}
	}

	
	int ret;
	for(int i=0; i<3; i++){
		for(int j=0; j<2; j++){
			pthread_join(th[i][j],(void*)&ret);
			c[i][j]=ret;
		}
	}
	
	//pthread_exit(0);
}


int main()
{
	pthread_t tmain;
	
	//struct arg_struct args;
	
	a[0][0] = 1;
a[0][1] = 0;
	a[0][2] = 0;
	a[1][0] = 0;
	a[1][1] = 1;
	a[1][1] = 0;
a[2][0] = 0;//a[m][k]
a[2][1] = 0;//a[m][k]
a[2][2] = 1;//a[m][k]
b[0][0]= 3;
b[0][1]= 2;
b[1][0]= 1;
b[1][1]= 2;
b[2][0]= 3;
b[2][1]= 1;
	
	

	
	
	
	pthread_attr_t at1;
	//pthread_attr_t at2;
	
	pthread_attr_init(&at1);
	//pthread_attr_init(&at2);
	
	
	pthread_create(&tmain,NULL,thrmain,NULL);
		
			pthread_join(tmain,NULL);
	
		
	printf("Returned Matrix: \n\n");
	for(int i=0;i<3;i++)	
	{
		for(int j=0;j<2;j++)
		{
			printf("%d ",c[i][j]);
		}
		printf("\n");
	}


	return 0;


}
