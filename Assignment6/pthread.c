#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *functionC();
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;
int main()
{
 int rc[10];
 pthread_t thread[10];
int i;
 /* Create independent threads each of which will execute functionC */
 for(i=0;i<=9;i++)
 if( (rc[i]=pthread_create( &thread[i], NULL, &functionC, NULL)) )
 printf("Thread creation failed: %d\n", rc[i]);



 /* Wait till threads are complete before main continues. Unless we */
 /* wait we run the risk of executing an exit which will terminate */
 /* the process and all threads before the threads have completed. */
 for(i=0;i<10;i++){
 pthread_join( thread[i], NULL);

 }
 exit(0);
}
void *functionC()
{
 pthread_mutex_lock( &mutex1 );
 counter++;
 printf("Counter value: %d\n",counter);
 pthread_mutex_unlock( &mutex1 );
}
