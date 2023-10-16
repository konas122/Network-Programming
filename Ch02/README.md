## `socket()`

创建套接字

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

### 协议族

| domain | 协议族 |
| --- | --- |
| PF_INET | IPv4协议族 |
| PF_INET6 | IPv6协议族 |
| PF_LOCAL | 本地UNIX协议族 |
| PF_PACKET | 底层套接字协议族 |
| PF_IPX | IPX Novell协议族 |

