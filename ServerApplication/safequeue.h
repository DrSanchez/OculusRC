#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H

#include <QMutex>
#include <QQueue>
#include <QSemaphore>
#include <QMutexLocker>

#define SEMAPHORE_MAX 32

template <class T>
class SafeQueue
{
public:
    SafeQueue();

    //thread safe queue operations
    void safeEnqueue(T * data);
    T safeDequeue();
    T safeHead();
    const T safeHead() const;
    int safeSize() const;
    int safeCount() const;
    bool isEmpty() const;
    bool isFull() const;

    //queue reference
    SafeQueue * getQueuePtr();

private:
    //private members
    QQueue<T> * _q;
    QSemaphore * _free;
    QSemaphore * _used;
    QMutex * _lock;

};

template <class T>
SafeQueue<T>::SafeQueue()
    : _q(nullptr), _free(nullptr),
      _used(nullptr), _lock(nullptr)
{
    _free = new QSemaphore(SEMAPHORE_MAX);
    _used = new QSemaphore(SEMAPHORE_MAX);
    _lock = new QMutex();
    _q = new QQueue<T>();
}

template <class T>
void SafeQueue<T>::safeEnqueue(T * data)
{
    _free->acquire(1);
    QMutexLocker locker(_lock);
    _q->enqueue(*data);
    _used->release(1);
}

template <class T>
T SafeQueue<T>::safeDequeue()
{
    _used->acquire(1);
    QMutexLocker locker(_lock);
    T value = _q->dequeue();
    _free->release(1);
    return value;
}

template <class T>
T SafeQueue<T>::safeHead()
{
    _used->acquire(1);
    QMutexLocker locker(_lock);
    T value = _q->head();
    _used->release(1);
    return value;
}

template <class T>
const T SafeQueue<T>::safeHead() const
{
    _used->acquire(1);
    QMutexLocker locker(_lock);
    const T value = _q->head();
    _used->release(1);
    return value;
}

template <class T>
SafeQueue<T> * SafeQueue<T>::getQueuePtr()
{
    return this;
}

template <class T>
int SafeQueue<T>::safeSize() const
{
    _used->acquire(1);
    QMutexLocker locker(_lock);
    int value = _q->size();
    _used->release(1);
    return value;
}

template <class T>
int SafeQueue<T>::safeCount() const
{
    _used->acquire(1);
    QMutexLocker locker(_lock);
    int value = _q->count();
    _used->release(1);
    return value;
}

template <class T>
bool SafeQueue<T>::isEmpty() const
{
    return _used->available() == 0;
}

template <class T>
bool SafeQueue<T>::isFull() const
{
    return _free->available() == 0;
}

#endif // SAFEQUEUE_H
