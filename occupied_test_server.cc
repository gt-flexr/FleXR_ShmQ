#include <flexr_shmq.h>
#include <bits/stdc++.h>

using namespace std;

int main()
{
  FlexrShmQueueMeta meta;
  meta.initQueue("/occupied_server", 5, 1024*1024*10);
  meta.printInfo();

  char *t = new char[1024*1024*10];
  for(int i = 0; i < 1024*512*10; i++)
  {
    t[i] = 'a';
  }
  for(int i = 0; i < 1024*512*10; i++)
  {
    t[i+(1024*512*10)] = 'b';
  }

  for(int i = 0; i < 10; i++)
  {
    bool res = meta.enqueueElem(t, 1024*1024*5);
    if(res == false)
      printf("failed to put data %d \n", i);
    sleep(1);
  }
}

