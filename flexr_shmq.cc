#include "flexr_shmq.h"

FlexrShmQueueMeta::FlexrShmQueueMeta():
  maxElem(0), elemSize(0), totalDataSize(0), queueSize(0), name(nullptr), shmemFd(-1), queue(nullptr)
{}


FlexrShmQueueMeta::~FlexrShmQueueMeta()
{
  closeQueue();
}


void FlexrShmQueueMeta::cleanInit()
{
  if (this->shmemFd != -1)
  {
    close(this->shmemFd);
    shm_unlink(name);
  }
  free(name);
}


void FlexrShmQueueMeta::closeQueue()
{
  munmap(this->queue, this->queueSize);
  cleanInit();
}


bool FlexrShmQueueMeta::initQueue(const char *name, uint32_t maxElem, uint32_t elemSize)
{
  bool created;

  this->maxElem       = maxElem;
  this->elemSize      = elemSize;
  this->totalDataSize = maxElem * elemSize;
  this->name          = strdup(name);
  this->queueSize     = totalDataSize + sizeof(FlexrShmQueue) - 1;

  created = false;

  this->shmemFd = shm_open(name, O_RDWR, S_IRUSR | S_IWUSR);
  if (this->shmemFd == -1)
  {
    if (errno == ENOENT)
    {
      this->shmemFd = shm_open(name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
      if (this->shmemFd == -1)
      {
        cleanInit();
        return false;
      }
      created = true;
    }
    else
    {
      cleanInit();
      return false;
    }
  }

  if (created && (-1 == ftruncate(this->shmemFd, this->queueSize)))
  {
    cleanInit();
    return false;
  }

  this->queue = (FlexrShmQueue*) mmap(NULL, this->queueSize, PROT_READ | PROT_WRITE, MAP_SHARED, this->shmemFd, 0);
  if (this->queue == MAP_FAILED)
  {
    cleanInit();
    return false;
  }

  if (created) {
    queue->rear = queue->front = queue->numElem = 0;

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);

    pthread_mutex_init(&queue->lock, &attr);

    pthread_mutexattr_destroy(&attr);
  }

  return true;
}



bool FlexrShmQueueMeta::enqueueElem(void *element, int len)
{
  return enqueueElemPart(element, 0, len, true);
}


bool FlexrShmQueueMeta::dequeueElem(void *element, int len)
{
  return dequeueElemPart(element, 0, len, true);
}


bool FlexrShmQueueMeta::enqueueElemPart(void *element, int offset, int len, bool done)
{
  if(queue->numElem == maxElem)
  {
    return false;
  }

  if (offset+len > this->elemSize)
  {
    return false;
  }

  pthread_mutex_lock(&this->queue->lock);

  uint32_t elemHead = queue->rear * elemSize;
  memcpy(&queue->data[elemHead + offset], element, len);

  if(done == true)
  {
    queue->numElem++;
    queue->rear = (queue->rear+1) % maxElem;
  }

  pthread_mutex_unlock(&queue->lock);
  return true;
}


bool FlexrShmQueueMeta::dequeueElemPart(void *element, int offset, int len, bool done)
{
  if(queue->numElem == 0)
  {
    return false;
  }

  if (offset+len > this->elemSize)
  {
    return false;
  }

  pthread_mutex_lock(&queue->lock);
  uint32_t elemHead = queue->front * elemSize;

  memcpy(element, &queue->data[elemHead+offset], len);

  if(done == true)
  {
    queue->numElem--;
    queue->front = (queue->front+1) % maxElem;
  }

  pthread_mutex_unlock(&queue->lock);
  return true;
}

