#include <flexr_shmq.h>
#include <bits/stdc++.h>

using namespace std;

int main()
{
  FlexrShmQueueMeta meta;
  meta.initQueue("/part_elem", 5, 1024*1024*10);

  char *t = new char[1024*1024*10];
  int num = 0;
  while(1)
  {
    bool res;
    res = meta.dequeueElemPart(              t,           0, 1024*1024*5, false);
    res = meta.dequeueElemPart(&t[1024*1024*5], 1024*1024*5, 1024*1024*5, true);
    if(res == true)
    {
      cout << t[1024*1024*5-1] << endl;
      cout << t[1024*1024*5] << endl;
      cout << t[1024*1024*10-1] << endl << endl;
      num++;
    }

    if(num == 12) break;
  }

  cout << "done..." << endl;
}

