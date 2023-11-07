# `epoll`理解及应用

`epoll_create`: 创建保存`epoll`文件描述符的空间
`epoll_ctl`:    向空间注册并注销文件描述符
`epoll_wait`:   与`select`函数类似，等待文件描述符发生变化

`epoll`函数将通过如下结构体`epoll_event`，将发生变化的（发生事件的）文件描述符单独集中到一起。

```C
struct epoll_event
{
    __uint32_t events;
    epoll_data_t data;
};

typedef union epoll_data
{
    void *ptr;
    int fd;
    __uint32_t u32;
    __uint64_t u64;
} epoll_data_t;
```


```C
#include <sys/epoll.h>

int epoll_create();
```

成功时返回`epoll`文件描述符，失败时返回`-1`

```C
#include <sys/epoll.h>

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
/*
epfd:   用于注册监视对象的`epoll`例程文件描述符。
op:     用于指定监视对象的增删改等操作
fd:     需要注册的监视对象文件描述符
event:  监视对象的事件
*/
```

成功时返回`epoll`文件描述符，失败时返回`-1`

参数`op`的可取值：
1. `EPOLL_CTL_ADD`：将文件描述符注册到`epoll`例程。
2. `EPOLL_CTL_DEL`：从`epoll`例程中删除文件描述符。如果`fd`取此值，则第四个参数`event`应为`NULL`。
3. `EPOLL_CTL_MOD`：更改注册的文件描述符的关注事件发生情况。

参数`event`的使用：这里用到的是`epoll_event`结构体的`events`成员，`events`成员用来指明关注的事件类型。
`events`可以指明的事件类型不止3种，它的可取值如下：
- `EPOLLIN`：需要读取数据的情况。
- `EPOLLOUT`：输出缓冲为空，可以立即发送数据的情况。
- `EPOLLPRI`：收到`OOB`数据的情况。
- `EPOLLDHUP`：断开连接或半关闭的情况，在边缘触发模式下很有用。
- `EPOLLERR`：发送错误的情况。
- `EPOLLET`：以边缘触发的情况得到事件通知。
- `EPOLLONESHOT`：发送一次事件后，相应的文件描述符不再收到事件通知。因此需要向`epoll_ctl`函数的第二个参数传递`EPOLL_CTL_MOD`，再次设置事件。

可以通过位运算同时传递多个上述参数。

```C
#include <sys/epoll.h>
int epoll_wait(int epfd, struct epoll_event* events, int maxevents, int timeout);
/*
功能：监视发生事件的文件描述符

参数：
    `epfd`：        `epoll`例程的文件描述符；
    `events`：      保存发生事件的文件描述符集合的结构体地址；
    `maxevents`：   最多监听的事件数，必须大于 0；
    `timeout`：     超时时间，以`ms`为单位。如果`timeout`为 -1，则一直等待到事件发生。（注意类型为 int，和 select 函数中的不同）

返回值：成功时返回发生事件的文件描述符数量，失败时返回 -1。
*/
```

## 条件触发

[Example](./echo_EPLTserv.c)

该示例与[echo_epollserv.c](./echo_epollserv.c)之间的差异如下：
- 将调用`read`函数时使用的缓冲大小减为`4`([第10行](./echo_EPLTserv.c#L10))
- 插入验证`epoll_wait`函数调用次数的语句([第56行](./echo_EPLTserv.c#L56))
