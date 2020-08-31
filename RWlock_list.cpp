#include"RWlock_list.h"
#include<iostream>
RWlockList::RWlockList() :head(), size(0)
{
	head = new node();
	RWlock::RWlock();
}

RWlockList::~RWlockList()
{
	/*while (head != NULL)
	{
		node* cur = head->next;
		delete head;
		head = cur;
	}*/
}

void RWlockList::add(const int val)
{
	MyRWlock.AddWriteLock();
	node* cur = head;
	while (cur->next != NULL)
		cur = cur->next;
	node* add_candidate = new node(val, NULL);
	cur->next = add_candidate;
	size++;
	//std::cout << "Ð´²Ù×÷" << std::endl;
	MyRWlock.ReleaseWriteLock();
}

void RWlockList::remove()
{
	if (size == 0)
		return;
	MyRWlock.AddWriteLock();
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
	MyRWlock.ReleaseWriteLock();
	return;

}

void RWlockList::print_list()
{
	
	node* cur = head->next;
	while (cur != NULL)
	{
		std::cout << cur->data << ' ';
		cur = cur->next;
	}
	
}

void RWlockList::find_if()
{
	MyRWlock.AddReadLock();
	node* cur = head->next;
	while (cur != NULL&&cur->next!=NULL)
	{
		cur = cur->next;
	}
	//std::cout << cur->data << std::endl;
	MyRWlock.ReleaseReadLock();
}

void RWlockList::test_read1()
{
	MyRWlock.AddReadLock();
	while (1)
	{
		node* cur = head->next;
		while (cur != NULL)
		{
			cur = cur->next;
		}
		std::cout << "read1" << std::endl;
	}	
	//MyRWlock.ReleaseReadLock();
}

void RWlockList::test_read2()
{
	MyRWlock.AddReadLock();
	while (1)
	{
		node* cur = head->next;
		while (cur != NULL)
		{
			cur = cur->next;
		}
		std::cout << "read2" << std::endl;
	}
	//MyRWlock.ReleaseReadLock();
}

void RWlockList::test_write1()
{
	MyRWlock.AddWriteLock();
	while (1)
		std::cout << "write1" << std::endl;
	MyRWlock.ReleaseWriteLock();
}

void RWlockList::test_write2()
{
	MyRWlock.AddWriteLock();
	while (1)
		std::cout << "write2" << std::endl;
	MyRWlock.ReleaseWriteLock();
}

