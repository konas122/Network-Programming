## 设置检查（监视）范围及超时

```C
#include <sys/select.h>
#include <sys/time.h>

int select(int maxfd, fd_set *readset, fd_set *writeset, fd_set *exeption, const struct timeval *timeout);
/**
 * maxfd:       监视对象文件描述符数量
 * readset:     将所有关注“是否存在带读取数据”的文件描述符注册到`fd_set`
 * writeset:    将所有关注“是否可传输无阻塞数据”的文件描述符注册到`fd_set`
 * exception:   将所有关注“是否发生异常”的文件描述符注册到`fd_set`
 * timeout:     调用`select`后，为防止陷入无限阻塞的状态，传递超时（time-out）信息
*/
```

成功返回大于`0`的值，失败则返回`-1`，超时返回`0`

```C
struct timeval
{
    long tv_sec;    // second
    long tv_usec;   // microsecond
}
```
