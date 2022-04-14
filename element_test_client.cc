#include <flexr_shmq.h>
#include <bits/stdc++.h>

using namespace std;

int main()
{
  FlexrShmQueueMeta meta;
  meta.initQueue("/elem_server", 5, 1024*1024*10);

  char *t = new char[1024*1024*10];
  int num = 0;
  while(1)
  {
    bool res = meta.dequeueElem(t, 1024*1024*10);
    if(res == true)
    {
      cout << t << endl;
      num++;
    }

    if(num == 10) break;
  }

  printf("done...\n");
}

