# TCP/IP Network-Programming

## `socket()`

```C
#include <sys/socket.h>

int socket(int domain, int type, int protocol);
/**
 * domain:      套接字中使用的协议族
 * type:        套接字数据传输类型信息(SOCK_STREAM, SOCK_DGRAM)
 * protocol:    计算机间通信中使用的协议信息(决定最终采用的协议)
*/
```

成功则返回文件描述符，失败则返回-1

| domain | 协议族 |
| --- | --- |
| PF_INET | IPv4协议族 |
| PF_INET6 | IPv6协议族 |
| PF_LOCAL | 本地UNIX协议族 |
| PF_PACKET | 底层套接字协议族 |
| PF_IPX | IPX Novell协议族 |


## `open()`

```C
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *path, int flag);
/**
 * path: 文件名字符串地址
 * flag: 文件打开模式
*/
```

成功则返回文件描述符，失败则返回-1

| 打开模式 | 含义 |
| --- | --- |
| O_CREAT | 必要时创建文件 |
| O_TRUNC | 删除全部现有数据 |
| O_APPEND | 维持现有数据，保存到其后面 |
| O_RDONLY | 只读打开 |
| O_WRONLY | 只写打开 |
| O_RDWR | 读写打开 |


## `close()`

```C
#include <unistd.h>

int close(int fd);
/**
 * fd: 需要关闭的文件或套接字的文件描述符
*/
```

成功时返回0，失败则返回-1

## `write()`

```C
#include <unistd.h>

ssize_t write(inf fd, const void* buf, size_t nbytes);
/**
 * fd:  需要关闭的文件或套接字的文件描述符
 * buf: 保存要传输数据的缓冲地址值
 * nbytes:  要传输数据的字符数
*/
```

成功时返回写入的字节数，失败则返回-1

## `read()`

```C
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t nbytes);
/**
 * fd:  需要关闭的文件或套接字的文件描述符
 * buf: 保存要传输数据的缓冲地址值
 * nbytes:  要接收数据的最大字节数
*/
```

成功时返回接收的字节数（但遇到文件结尾则返回0），失败则返回-1


## 地址信息表示

```C
struct sockaddr_in 
{
    sa_family_t     sin_family;     // 地址族
    uint16_t        sin_port;       // 16位TCP/UDP端口号
    struct in_addr  sin_addr;       // 32位IP地址
    char            sin_zero[8]     // 不使用
};

struct in_addr
{
    in_addr_t       s_addr;         // 32位IPv4地址
};
```

| 地址族 | 含义 |
| --- | --- |
| AF_INET | IPv4网络协议使用的地址族 |
| AF_INET6 | IPv6网络协议使用的地址族 |
| AF_LOCAL | 本地通信中采用的UNIX协议的地址族 |


```C
struct sockaddr
{
    sa_family_t sin_family; // 地址族
    char        sa_data;    // 地址信息
};
```
其中，成员`sa_data`保存的地址信息中需包含IP地址和端口号，剩余部分填充0，这也是`bind`函数要求的。

### 关于`sin_family`

`sockaddr_in`是保存IPv4地址信息的结构体。那为何还需要通过`sin_family`单独制定地址族信息呢？这与之前讲过的`sockaddr`有关。结构体`sockaddr`并非只为IPv4设计，为了与`sockaddr`保持一致，`sockaddr_in`要求在`sin_family`中指定地址族信息。

## 字节序转换

[小端法转大端法 代码](./Ch03/endian_conv.c)

在实际代码编写中，字节序转换过程是自动的。除了向`sockaddr_in`结构体变量填充数据外，其他情况均无需考虑字节序问题。

### `inet_addr`

```C
#include <arpa/inet.h>

in_addr_t inet_addr(const char* string);
```

成功则返回32位大端序整数值，失败则返回`INADDR_NONE`. 

### `inet_aton`

```C
#include <arpa/inet.h>

int inet_aton(const char *string, struct in_addr *addr);
```

成功则返回1（true），失败则返回0（false）

### `inet_ntoa`

```C
#include <arpa/inet.h>

char * inet_ntoa(struct in_addr addr);
```

成功则返回转换的字符串地址，失败则返回-1

### `INADDR_ANY`

每次创建服务器端套接字都要输入IP地址会有些繁琐，此时我们可以利用常数`INADDR_ANY`分配服务器端的IP地址。此法，可自动获取运行服务器的计算机IP地址，不必亲自输入。
