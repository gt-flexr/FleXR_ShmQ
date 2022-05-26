#include <flexr_shmq.h>
#include <bits/stdc++.h>

using namespace std;

int main()
{
  FlexrShmQueueMeta meta;
  meta.initQueue("/part_elem", 5, 1024*1024*10);
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

  for(int i = 0; i < 12; i++)
  {
    bool res;

    res = meta.enqueueElemPart(t, 0, 1024*512*10, true, false);
    if(res == false) printf("failed to put the first half of data %d \n", i);

    res = meta.enqueueElemPart(&t[1024*512*10], 1024*512*10, 1024*512*10, true, true);
    if(res == false) printf("failed to put the rest of data %d \n", i);

    sleep(1);
  }
}

