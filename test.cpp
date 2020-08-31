#include <iostream>
#include <pthread.h>
#include <time.h>
#include "rw_lock.h"
#include "coarse_lock_list.h"
#include "rw_lock_list.h"
#include <chrono>
#include <random>
using namespace std;
using namespace chrono;

#define NUMOFNODE 5000
#define READCOUNT 10000
#define WRITECOUNT 3000
RWlock testRWlock;
RWlockList MyRWlockList;
CoarseLockList MyCoarseLockList;
vector<int> TestVecRead;
vector<int> TestVecWrite;

void init()
{
	for (int i = 0; i < NUMOFNODE; i++)
		MyRWlockList.add(i + 1);
	for (int i = 0; i < NUMOFNODE; i++)
		MyCoarseLockList.add(i + 1);
	default_random_engine e;
	for (int i = 0; i < READCOUNT; i++)
		TestVecRead.push_back(e() % NUMOFNODE + 1);
	for (int i = 0; i < WRITECOUNT; i++)
		TestVecWrite.push_back(e() % NUMOFNODE + 1);
}

void *test_read_CoarseLockList(void *arg)
{
	int count = 0;
	while (count < READCOUNT)
	{
		MyCoarseLockList.find_if(TestVecRead[count]);
		count++;
	}
	return NULL;
}

void *test_write_CoarseLockList(void *arg)
{
	int count = 0;
	while (count < WRITECOUNT)
	{
		MyCoarseLockList.add(TestVecWrite[count]);
		count++;
	}
	return NULL;
}

void *test_read_RWLockList(void *arg)
{
	int count = 0;
	while (count < READCOUNT)
	{
		MyRWlockList.find_if(TestVecRead[count]);
		count++;
	}
	return NULL;
}

void *test_write_RWLockList(void *arg)
{
	int count = 0;
	while (count < WRITECOUNT)
	{
		MyCoarseLockList.add(TestVecWrite[count]);
		count++;
	}
	return NULL;
}

int main()
{
	init();
	pthread_t t1, t2, t3, t4, t5, t6, t7, t8;
	auto start = system_clock::now();
	pthread_create(&t1, NULL, test_read_CoarseLockList, NULL);
	pthread_create(&t2, NULL, test_read_CoarseLockList, NULL);
	pthread_create(&t3, NULL, test_read_CoarseLockList, NULL);
	pthread_create(&t4, NULL, test_read_CoarseLockList, NULL);
	pthread_create(&t5, NULL, test_read_CoarseLockList, NULL);
	pthread_create(&t6, NULL, test_read_CoarseLockList, NULL);
	pthread_create(&t7, NULL, test_read_CoarseLockList, NULL);
	pthread_create(&t8, NULL, test_write_CoarseLockList, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	pthread_join(t5, NULL);
	pthread_join(t6, NULL);
	pthread_join(t7, NULL);
	pthread_join(t8, NULL);
	auto end = system_clock::now();
	auto duration = duration_cast<milliseconds>(end - start);
	std::cout << "CoarseLockList time:" << duration.count() << "ms" << std::endl;

	pthread_t t11, t21, t31, t41, t51, t61, t71, t81;
	auto start1 = system_clock::now();
	pthread_create(&t11, NULL, test_read_RWLockList, NULL);
	pthread_create(&t21, NULL, test_read_RWLockList, NULL);
	pthread_create(&t31, NULL, test_read_RWLockList, NULL);
	pthread_create(&t41, NULL, test_read_RWLockList, NULL);
	pthread_create(&t51, NULL, test_read_RWLockList, NULL);
	pthread_create(&t61, NULL, test_read_RWLockList, NULL);
	pthread_create(&t71, NULL, test_read_RWLockList, NULL);
	pthread_create(&t81, NULL, test_write_RWLockList, NULL);
	pthread_join(t11, NULL);
	pthread_join(t21, NULL);
	pthread_join(t31, NULL);
	pthread_join(t41, NULL);
	pthread_join(t51, NULL);
	pthread_join(t61, NULL);
	pthread_join(t71, NULL);
	pthread_join(t81, NULL);
	auto end1 = system_clock::now();
	auto duration1 = duration_cast<milliseconds>(end1 - start1);
	std::cout << "RWLockList time:" << duration1.count() << "ms" << std::endl;
	system("pause");
	return 0;
}
