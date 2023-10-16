# 地址信息表示

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

## 关于`sin_family`

`sockaddr_in`是保存IPv4地址信息的结构体。那为何还需要通过`sin_family`单独制定地址族信息呢？这与之前讲过的`sockaddr`有关。结构体`sockaddr`并非只为IPv4设计，为了与`sockaddr`保持一致，`sockaddr_in`要求在`sin_family`中指定地址族信息。

# 字节序转换

[小端法转大端法 代码](./Ch03/endian_conv.c)

在实际代码编写中，字节序转换过程是自动的。除了向`sockaddr_in`结构体变量填充数据外，其他情况均无需考虑字节序问题。

## `inet_addr`

```C
#include <arpa/inet.h>

in_addr_t inet_addr(const char* string);
```

成功则返回32位大端序整数值，失败则返回`INADDR_NONE`. 

## `inet_aton`

```C
#include <arpa/inet.h>

int inet_aton(const char *string, struct in_addr *addr);
```

成功则返回1（true），失败则返回0（false）

## `inet_ntoa`

```C
#include <arpa/inet.h>

char * inet_ntoa(struct in_addr addr);
```

成功则返回转换的字符串地址，失败则返回-1

## `INADDR_ANY`

每次创建服务器端套接字都要输入IP地址会有些繁琐，此时我们可以利用常数`INADDR_ANY`分配服务器端的IP地址。此法，可自动获取运行服务器的计算机IP地址，不必亲自输入。
