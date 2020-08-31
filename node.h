#pragma once
struct node {
	int data;
	node* next;
	node() {
		data = 0;
		next = NULL;
	}
	node(int data, node* next) {
		this->data = data;
		this->next = next;
	}
};