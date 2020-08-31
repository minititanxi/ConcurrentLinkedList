#pragma once
#include<pthread.h>
#include<iostream>
#include"rw_lock.h"
#include"node.h"

class RWlockList {
public:
	RWlockList();
	~RWlockList();
	void add(const int val);
	void remove();
	void print_list();
	bool find_if(int val);
private:
	node * head;
	RWlock MyRWlock;
	int size;
};




