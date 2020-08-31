#include<pthread.h>
#include<iostream>
#include"rw_lock.h"
RWlock::RWlock()
	: write(0),read(0)
{
	pthread_mutex_init(&mtx, NULL);
	pthread_cond_init(&cond, NULL);
}

RWlock::~RWlock()
{
	pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&cond);
}

void RWlock::AddReadLock()
{
	pthread_mutex_lock(&mtx);
	while(write==1)
		pthread_cond_wait(&cond, &mtx);
	read++;
	pthread_mutex_unlock(&mtx);
}

void RWlock::ReleaseReadLock()
{
	pthread_mutex_lock(&mtx);
	read--;
	if (read == 0)
		pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mtx);
}

void RWlock::AddWriteLock()
{
	pthread_mutex_lock(&mtx);
	while (write!=0||read>0)
		pthread_cond_wait(&cond, &mtx);
	write = 1;
	pthread_mutex_unlock(&mtx);
}

void RWlock::ReleaseWriteLock()
{
	pthread_mutex_lock(&mtx);
	write = 0;
	pthread_cond_broadcast(&cond); 
	pthread_mutex_unlock(&mtx);
}

