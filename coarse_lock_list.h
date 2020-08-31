#pragma once
#include<pthread.h>
#include<memory>
#include<iostream>
#include"node.h"

class CoarseLockList {
public:
	CoarseLockList();
	~CoarseLockList();

	void add(const int val);//��ĩβ���Ԫ��
	void remove();//��ĩβ�Ƴ��ڵ�
	//bool find_if(const int location);//
	void print_list();
	void find_if();
	void test_read1();
	void test_read2();
	void test_write();

private:
	node* head;
	pthread_mutex_t coarseLock;
	int size;
};



