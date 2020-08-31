#include"rw_lock_list.h"
#include<iostream>
RWlockList::RWlockList() :head(), size(0)
{
	head = new node();
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

bool RWlockList::find_if(int val)
{
	MyRWlock.AddReadLock();
	node* cur = head->next;
	while (cur != NULL){
		if(cur->data == val){
			MyRWlock.ReleaseReadLock();
			return true;
		}
		cur = cur->next;
	}
	//std::cout << cur->data << std::endl;
	MyRWlock.ReleaseReadLock();
	return false;
}



