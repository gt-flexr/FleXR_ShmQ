# FleXR_ShmQ

This is a lightweight shared memory queue library on Linux (tested on Ubuntu 18.04,20.04,22.04). 
I originally write FleXR_ShmQ for my main project, [FleXR](https://github.com/gt-flexr), but this can be useful for other usage.

## Install & Test
```
git clone https://github.com/gt-flexr/FleXR_ShmQ.git
cd FleXR_ShmQ && mkdir build && cd build
cmake .. && make -j$(nproc)
sudo make install

./test.sh
```

## Features
Other than the basic queue functionalities, there are additional and useful functionalities.

### Type free & Queue Size

| FlexrShmQueue | FlexrElemMeta + Elem Data | FlexrElemMeta + Elem Data | FlexrElemMeta + Elem Data | ... |

Each data of queue element is treated as byte array.
As shown above, each element has meta data for the actual data of the queue element; the initial FlexrShmQueue is the meta data about the queue itself (rear, front, current # of elemes, and lock).
You can set the maximum number of queue elements.
 

### Communication Semantics: Blocking and Non-blocking
When the API is called, blocking/non-blocking can be set for enqueuing/dequeuing.
With blocking semantics, the en/dequeue wait for the receiving end's corresponding operations.

For instance, when enqueuing with blocking, the sending process waits for the receiving process to dequeue.
When dequeuing with blocking, the receiving process waits for the sending process to enqueue.
With non-blocking, it checkes the queue memory for figuring out the queue element existence.
If no element in the queue, it returns nothing.

### Partial Enqueue/Dequeue
When necessary, you can put multiple variables into a queue element with total size. Then, the receiving end can dequeue a element in multiple times (partial dequeue).
You can serialize the multiple data via boost or other serialization methods, but sometimes it can overkill; you need to add additional methods to your project as a dependency.
If you want to do it in a quick way, use this feature.

