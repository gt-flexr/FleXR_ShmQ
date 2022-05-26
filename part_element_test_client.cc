#include <flexr_shmq.h>
#include <bits/stdc++.h>

using namespace std;

int main()
{
  FlexrShmQueueMeta meta;
  meta.initQueue("/part_elem", 5, 1024*1024*10, true);
  meta.printInfo();

  char *t = new char[1024*1024*10];
  int num = 0;
  while(1)
  {
    bool res;
    int occupiedElem = 0;
    res = meta.dequeueElemPart(              t, occupiedElem,           0, 1024*1024*5, true, false);
    printf("occupiedElem : %d\n", occupiedElem);
    res = meta.dequeueElemPart(&t[1024*1024*5], occupiedElem, 1024*1024*5, 1024*1024*5, true, true);
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

