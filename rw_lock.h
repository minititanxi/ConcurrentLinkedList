#pragma once
class RWlock {
public:
  RWlock();
  ~RWlock();
  void AddWriteLock();
  void AddReadLock();
  void ReleaseWriteLock();
  void ReleaseReadLock();

private:
  pthread_mutex_t mtx;
  pthread_cond_t cond;
  int write;
  int read;
};
