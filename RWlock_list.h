#pragma once
#include<pthread.h>
#include<iostream>
#include"RWlock.h"
#include"node.h"

class RWlockList {
public:
	RWlockList();
	~RWlockList();
	void add(const int val);//��ĩβ���Ԫ��
	void remove();//��ĩβ�Ƴ��ڵ�
				  //bool find_if(const int location);//
	void print_list();
	void find_if();
	void test_read1();
	void test_read2();
	void test_write1();
	void test_write2();

private:
	node * head;
	RWlock MyRWlock;
	int size;
};




