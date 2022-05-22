#pragma once

#include <thread>
#include <cstdint>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

class FlexrShmQueue
{
public:
  pthread_mutex_t lock;
  uint32_t rear;
  uint32_t front;
  uint32_t numElem;
  char data[1];
};



class FlexrShmQueueMeta
{
public:
  uint32_t maxElem;
  uint32_t elemSize;
  uint32_t totalDataSize;
  uint32_t queueSize;

  char* name;
  int shmemFd;
  FlexrShmQueue* queue;

  FlexrShmQueueMeta();
  ~FlexrShmQueueMeta();

  bool initQueue(char const* name, uint32_t maxElem, uint32_t elemSize);
  bool initQueue(char const* name, uint32_t maxElem, uint32_t elemSize, bool removeFile);
  void cleanInit();
  void closeQueue();

  bool isFull();
  bool isEmpty();

  // blocking & nonblocking semantics
  bool enqueueElem(void* element, int len, bool blocking=false);
  bool dequeueElem(void* element, int len, bool blocking=false);

  bool enqueueElemPart(void* element, int offset, int len, bool blocking, bool done);
  bool dequeueElemPart(void* element, int offset, int len, bool blocking, bool done);
};

