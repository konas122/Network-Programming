## `getsockopt`

```C
#include <sys/socket.h>

int getsockopt(int sock, int level, int optname, void *optval, socklen_t *optlen);
/**
 * sock:    要查看的套接字文件描述符
 * level:   要查看的可选项的协议层
 * optname: 要查看的可选项名
 * optval:  保存查看结果的缓冲地址值
 * optlen:  第四个参数`optval`传递的缓冲区大小
*/

int setsockopt(int sock, int level, int optname, void *optval, socklen_t *optlen);
/**
 * sock:    用于更改可选项的套接字文件描述符
 * level:   要更改的可选项的协议层
 * optname: 要更改的可选项名
 * optval:  保存要更改的选项信息的缓冲地址值
 * optlen:  第四个参数`optval`传递的缓冲区大小
*/
```

成功时返回0，失败则返回-1

