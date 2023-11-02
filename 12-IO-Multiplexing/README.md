# `select`函数

使用`select`函数时，可以将多个文件描述符集中到一起统一监视，项目如下：
- 是否存在套接字接收数据？
- 无需阻塞传输数据的套接字有哪些？
- 哪些套接字发生了异常？

使用步骤：
- 步骤1：
  - 设置文件描述符
  - 指定监视范围
  - 设置超时
- 步骤2：
  - 调用`select`函数
- 步骤3：
  - 查看结果

## 设置文件描述符

```C
FD_ZERO(fd_set *fdset);             // 从`fdset`所有位初始化为0
FD_SET(int fd, fd_set *fdset);      // 从`fdset`指向的变量中注册文件描述符`fd`的信息
FD_CLR(int fd, fd_set *fdset);      // 从`fdset`指向的变量中清除文件描述符`fd`的信息
FD_ISSET(int fd, fd_set *fdset);    // 若`fdset`指向的变量中包含文件描述符`fd`的信息，则返回“真”
```

上述函数中，`FD_ISSET`用于验证`select`函数的调用结果。


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

`select`函数用来验证3种监视项的变化情况

```C
struct timeval
{
    long tv_sec;    // second
    long tv_usec;   // microsecond
}
```
