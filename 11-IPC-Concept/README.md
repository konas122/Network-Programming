## 管道实现进程间通信

```C
#include <unistd.h>

int pipe(int filedes[2]);
/**
 * filedes[0]:  管道接受数据时使用的文件描述符，管道出口
 * filedes[1]:  管道传输数据时使用的文件描述符，管道入口
*/
```

成功返回0，失败返回-1



## 消息队列

[Linux 消息队列](./MsgQueue.md)
