#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
//Create left and right child if n>=10, otherwise direct calculate maximum
void find_max(int arr[], int l, int r){
	int status;
	int size_of_array,i,c=0;
	int max1,max2,max;
	int cpid1,cpid2;
	int m;
	for (i=l;i<=r;i++)
		c++;
	size_of_array=c;
	if(size_of_array<10){//Directly compute max
		max = arr[0];
		for(i=l;i<=r;i++){
			if(arr[i] >= max)
			max = arr[i];	
		}
		printf("PID = %d \t parent PID = %d \t max = %d\n",getpid(),getppid(),max);
		exit(max);	
	}
	else{//Create 2 child processes
		m=(l+r)/2;
		if((cpid1 = fork()) == 0){//Left child
			//printf("Left Child");
			//for (i=l;i<=m;i++){
			//	printf("%d ",arr[i]);
			//}
			find_max(arr, l, m);		
		}
		else if((cpid2 = fork()) == 0){//Right child
			//printf("Right Child");
			//for (i=m+1;i<=r;i++){
			//	printf("%d ",arr[i]);
			//}
			find_max(arr,m+1, r);		
		}
		else{//Parent
			waitpid(cpid1, &status, 0);
			max1 = WEXITSTATUS(status);//Get the returned value
			waitpid(cpid2, &status, 0);
			max2 = WEXITSTATUS(status);//Get the returned value
			max = max1>max2?max1:max2;
			printf("PID = %d \t parent PID = %d \t max = %d\n",getpid(),getppid(),max);
			exit(max);		
		}
	}
}
int main(int argc, char * argv[]){
	srand((unsigned int)time(NULL));//so as to seed the rand() with a different starting value
	//time_t is the return type of time(NULL) which is to be type casted to unsigned int 
	//as time is current time with refference to 1 st jan 1970
	int arr[100];
	int n,i,status;
	int cpid;
	//Check for valid number of command line arguments sent
	if(argc!=2){
		printf("Invalid arguments!!\n");
		exit(0);
	}
	n = atoi(argv[1]);//converts string type data directly in integer as char * argv stires string type data
	//Generate random numbers
	for(i=0;i<n;++i)
		arr[i] = rand()%128;
	printf("Original array is : ");	
	for(i=0;i<n;++i)
		printf("%d ",arr[i]);
	printf("\n\n");
	//Fork a child process which computes max
	if((cpid = fork()) == 0){//Child process
		find_max(arr, 0, n-1);	
	}
	else{//Parent process
		waitpid(cpid, &status, 0);//wait for child to complete
		printf("The maximum value in the array is : %d\n",WEXITSTATUS(status));
	}
	sleep(30);//So that xterm can be hold . . . for wrapper.c "code" .... as xterm is needed it is made to hold for 20 seconds
	exit(0);
}