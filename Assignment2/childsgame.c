//Author : Piyush Sawarkar
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#define MAX 1
#define MIN 0
#define BUFSIZE 80
void CchildSigHandler ( int sig )
{
 if (sig == SIGUSR1) {
 printf("C win and D loss\n");
 sleep(1);
 }
 exit(0);
}
void DchildSigHandler ( int sig )
{
 if (sig == SIGUSR2) {
 printf("D win and C loss\n");
 sleep(1);
 }
 exit(0);
}
int main(void){
int cfd[2],dfd[2];
int i,n;
char line1[BUFSIZE],line2[BUFSIZE];
int cpid,dpid;
int res_c=0;
int res_d=0;
int parent_rand;
int cans,dans;
pipe(cfd);
pipe(dfd);
srand((unsigned int )time(NULL));
if ((cpid=fork())==0){
srand(0);//here srand(cpid) also works
 signal(SIGUSR1, CchildSigHandler);
 signal(SIGUSR2, CchildSigHandler);
close(cfd[0]);
close(dfd[0]);
close(dfd[1]);
while(1){
n=rand()%200;
sprintf(line1,"%d",n);
write(cfd[1], line1, BUFSIZE);
}
}
else if((dpid=fork())==0){
signal(SIGUSR1, DchildSigHandler);
 signal(SIGUSR2, DchildSigHandler);
close(cfd[0]);
close(dfd[0]);
close(cfd[1]);
while(1){
n=rand()%200;
sprintf(line2,"%d",n);
write(dfd[1], line2, BUFSIZE);
}
}
else{//parent
close(cfd[1]);
close(dfd[1]);
while(res_c!=10 || res_d!=10){
parent_rand=rand()%2;
read(cfd[0], line1, BUFSIZE);
sscanf(line1,"%d",&cans);
read(dfd[0], line2, BUFSIZE);
sscanf(line2,"%d",&dans);
printf("parent_rand=%d,cans=%d,dans=%d",parent_rand,cans,dans);
if(parent_rand==MAX){
if (cans>dans){
printf("\nChild: C gains point...");
res_c+=1;
sleep(1);
}
else if(cans<dans){
printf("\nChild: D gains point...");
res_d+=1;
sleep(1);
}
else if(cans==dans){
printf("\nNo One Wins...");
continue;
}
}
else if(parent_rand==MIN){
if (cans<dans){
printf("\nChild: C gains point...");
res_c+=1;
sleep(1);
}
else if(cans>dans){
printf("\nChild: D gains point...");
res_d+=1;
sleep(1);
}
else if(cans==dans){
printf("\nNo One Wins...");
continue;
}
}
printf("\tResult:\tc:%d,d:%d\n\n",res_c,res_d);
if (res_c==10){
kill(cpid,SIGUSR1);
exit(0);
}
else if (res_d==10){
kill(dpid,SIGUSR2);
exit(0);
}
}
}
exit(0);
}

