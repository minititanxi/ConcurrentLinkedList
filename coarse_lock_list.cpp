#include"coarse_lock_list.h"

CoarseLockList::CoarseLockList():size(0)
{
	pthread_mutex_init(&coarseLock, NULL);
	head = new node();
}

CoarseLockList::~CoarseLockList()
{
	pthread_mutex_destroy(&coarseLock);
	/*while(head->next!=NULL)
	{
		remove();
	}*/
}

void CoarseLockList::add(const int val)
{
	pthread_mutex_lock(&coarseLock);
	node* cur = head;
 	while (cur->next!= NULL)
		cur = cur->next;
	node* add_candidate = new node(val, NULL);
	cur->next = add_candidate;
	size++;
	pthread_mutex_unlock(&coarseLock);
}

void CoarseLockList::remove()
{
	if (size == 0)
		return;
	pthread_mutex_lock(&coarseLock);
	node* previous = head;
	node* cur = head->next;
	while (cur->next != NULL)
	{
		previous = cur;
		cur = cur->next;
	}
	previous->next = NULL;
	delete cur;
	size--;
	pthread_mutex_unlock(&coarseLock);
	return;	
}

void CoarseLockList::print_list()
{
	pthread_mutex_lock(&coarseLock);
	node* cur = head->next;
	while (cur != NULL)
	{
		std::cout << cur->data << ' ';
		cur = cur->next;
	}
	pthread_mutex_unlock(&coarseLock);
}

void CoarseLockList::find_if()
{
	pthread_mutex_lock(&coarseLock);
	node* cur = head->next;
	while (cur != NULL && cur->next != NULL)
		cur = cur->next;
	//std::cout << cur->data << std::endl;
	pthread_mutex_unlock(&coarseLock);
}

void CoarseLockList::test_read1()
{
	pthread_mutex_lock(&coarseLock);
	while (1)
		std::cout << "read1" << std::endl;
	//MyRWlock.ReleaseReadLock();
}

void CoarseLockList::test_read2()
{
	pthread_mutex_lock(&coarseLock);
	while (1)
		std::cout << "read2" << std::endl;
	//MyRWlock.ReleaseReadLock();
}

void CoarseLockList::test_write()
{
	pthread_mutex_lock(&coarseLock);
	while (1)
		std::cout << "write" << std::endl;
	pthread_mutex_unlock(&coarseLock);
}






