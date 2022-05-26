#include <flexr_shmq.h>
#include <bits/stdc++.h>

using namespace std;

int main()
{
  FlexrShmQueueMeta meta;
  meta.initQueue("/occupied_server", 5, 1024*1024*10, true);
  meta.printInfo();

  char *t = new char[1024*1024*10];
  int num = 0;
  while(1)
  {
    uint32_t occupiedSize = 0;
    uint32_t bufSize      = 1024*1024*10;
    bool res = meta.dequeueElem(t, occupiedSize, bufSize);
    if(res == true)
    {
      cout << t << endl;
      cout << "occupiedElem: " << occupiedSize << ", elemSize: " << meta.elemSize << endl;
      num++;
    }

    if(num == 10) break;
  }

  printf("done...\n");
}

