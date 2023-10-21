## 基于UDP的数据I/O函数

```C
#include <sys/socket.h>

ssize_t sendto(int sock, void *buff, size_t nbytes, int flags,
                struct sockaddr *to, socklen_t addrlen);

ssize_t recvfrom(int sock, void *buff, size_t nbytes, int flags,
                struct sockaddr *to, socklen_t addrlen);
/**
 * `sock`:      用于传输数据的UDP套接字文件描述符
 * `buff`:      保存待传输数据的缓冲地址值
 * `nbytes`:    待传输的数据长度，亿字节为单位
 * `flags`:     可选项参数，若没有则传递0
 * `to`:        存有目标地址信息的sockaddr结构体的地址
 * `addrlen`:   传递给参数`to`的地址值结构体变量长度
*/
```

成功时返回传输的字节数，失败则返回-1
