#pragma once

#include <pthread.h>
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


  // enqueue exact element
  bool enqueueElem(void* element, int len);
  bool dequeueElem(void* element, int len);

  bool enqueueElemPart(void* element, int offset, int len, bool done);
  bool dequeueElemPart(void* element, int offset, int len, bool done);
};

