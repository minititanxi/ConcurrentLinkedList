#pragma once
#include<pthread.h>
#include<memory>
#include<iostream>
#include"node.h"

class CoarseLockList {
public:
	CoarseLockList();
	~CoarseLockList();
	// 添加一个节点
	void add(const int val);

	// 移除一个节点
	void remove();

	// 打印链表
	void print_list();

	// 查询一个值是否在链表中
	bool find_if(int val);
private:
	node* head;
	pthread_mutex_t coarseLock;
	int size;
};



