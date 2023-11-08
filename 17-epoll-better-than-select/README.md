# `epoll`理解及应用


## `epoll_event`

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

## `epoll_create`

`epoll_create`: 创建保存`epoll`文件描述符的空间

```C
#include <sys/epoll.h>

int epoll_create(int size);
/*
size:   `epoll`实例大小
*/
```

成功时返回`epoll`文件描述符，失败时返回`-1`

调用`epoll_create`函数创建的文件描述符保存空间称为“`epoll`例程”，但有些情况不同。

通过参数`size`传递的值决定`epoll`例程的大小，但该值只是向操作系统提的建议。

换言之，`size`并非用来决定`epoll`例程大小，而仅供操作系统参考。（`Linux 2.6.8`后内核会完全忽略`size`参数）

## `epoll_ctl`

`epoll_ctl`:    向空间注册并注销文件描述符
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
- `EPOLLIN`：   表示对应的文件描述符可以读（包括对端`SOCKET`正常关闭）。
- `EPOLLOUT`：  表示对应的文件描述符可以写。
- `EPOLLPRI`：  表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）。
- `EPOLLDHUP`： 表示对应的文件描述符被挂断，在边缘触发模式下很有用。
- `EPOLLERR`：  表示对应的文件描述符发生错误。
- `EPOLLET`：   将`EPOLL`设为边缘触发(`Edge Triggered`)模式，这是相对于水平触发(`Level Triggered`)来说的。
- `EPOLLONESHOT`：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里。发送一次事件后，相应的文件描述符不再收到事件通知。因此需要向`epoll_ctl`函数的第二个参数传递`EPOLL_CTL_MOD`，再次设置事件。

可以通过位运算同时传递多个上述参数。

## `epoll_wait`

`epoll_wait`:   与`select`函数类似，等待文件描述符发生变化

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


# 条件触发和边沿触发

`epoll`中有两种触发方式：条件触发`LT(Level Trigger)`和边缘触发`ET(Edge Trigger)`。

- 条件触发：只要输入缓冲中有数据就一直通知该事件。
- 边缘触发：只有当输入缓冲收到数据时注册一次该事件，之后即使输入缓冲中还有数据也不会再注册。
- `epoll`默认以条件触发方式工作。`select`函数也是以条件触发方式工作的。

## 条件触发

[Example](./echo_EPLTserv.c)

该示例与[echo_epollserv.c](./echo_epollserv.c)之间的差异如下：
- 将调用`read`函数时使用的缓冲大小减为`4` ([第10行](./echo_EPLTserv.c#L10))
- 插入验证`epoll_wait`函数调用次数的语句 ([第56行](./echo_EPLTserv.c#L56))

## 边沿触发

[Example](./echo_EPETserv.c)

将文件（套接字）改为非阻塞模式

```C
#include <fcntl.h>
int fcntl(int filedes, int cmd, ...);
        // 功能：更改或读取文件属性。
        // 参数：filedes：要更改属性的文件描述符；cmd：指明函数调用的目的；...：可变参数，根据 cmd 的不同值会有不同情况。
```

成功时返回`cmd`参数相关值，失败时返回`-1`


`cmd`的可取值（包括但不限于以下）：
1. `F_GETFL`：取此值时，`fcntl`函数用于获取文件描述符`filedes`的属性（会返回相应值）。
2. `F_SETFL`：更改文件描述符属性。

将文件（套接字）改为非阻塞模式要使用如下的两条语句：

```C
int flag = fcntl(fd, F_GETFL, 0);      // 获取之前的属性
fcntl(fd, F_SETFL, flag|O_NONBLOCK);   // 在此基础上添加非阻塞`O_NONBLOCK`标志。
```
