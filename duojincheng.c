#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

static int g_num=0;
static pthread_mutex_t g_mutex;
void *thread_handle(void *arg)
{
	int i=0;
	for(i=0;i<10;i++)
	{
		pthread_mutex_lock(&g_mutex);
		printf("线程[1] brfore %d\n",g_num);
		g_num++;
		sleep(1);
		printf("线程[1] after %d\n",g_num);
		pthread_mutex_unlock(&g_mutex);
		sleep(1);	
	}
	printf("线程[1] exit\n");
	return NULL;
}

void *thread_handle_new(void *arg)
{
	int i=0;
	for(i=0;i<10;i++)
	{
		pthread_mutex_lock(&g_mutex);
		printf("线程[2] brfore %d\n",g_num);
		g_num--;
		sleep(2);
		printf("线程[2] after %d\n",g_num);
		pthread_mutex_unlock(&g_mutex);
		sleep(2);	
	}
	printf("线程[2] exit\n");
	return NULL;
}
int main()
{	
	pthread_mutex_init(&g_mutex,NULL);
	pthread_t pid =0;
	int ret=pthread_create(&pid,NULL,thread_handle,NULL);
	if(ret!=0)
	{
		perror(strerror(errno));
		return 0;
	}
	int ret_new= pthread_create(&pid,NULL,thread_handle_new,NULL);
	if(ret_new!=0)
	{
		perror(strerror(errno));
		return 0;
	}
	pthread_join(pid,NULL);
        pthread_mutex_destroy(&g_mutex);
	printf("退出\n");
	return 0;
}
