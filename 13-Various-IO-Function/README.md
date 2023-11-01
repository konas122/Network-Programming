## `send`&`recv`

```C
include <sys.socket.h>

ssize_t send(int sockfd, const void *buf, ssize_t nbytes, int flags);

ssize_t recv(int sockfd, const void *buf, ssize_t nbytes, int flags);
/**
 * sockfd:  表示数据接收对象的连接的套接字文件描述符
 * buf:     保存接收数据的缓冲区地址
 * nbytes:  可接受的最大字节数
 * flags:   接收数据时可选项信息
*/
```

成功时返回接收的字节数（收到`EOF`则返回0），失败则返回-1

| `flags` | 含义 | `send` | `recv` | 
|---|---|---|---|
| `MSG_OOB` | 用于传输带外数据(Out-of-band data) | · | · |
| `MSG_PEEK` | 验证缓冲区中是否存在接收的数据 |   | · |
| `MSG_DONTROUTE` | 数据传输过程中不参照路由(Routing)表，在本地(Local)网络中寻找目的地 | · |   |
| `MSG_DONTWAIT` | 调用I/O函数不阻塞，用于使用非阻塞(Non-blocking)I/O | · | · |
| `MSG_WAITALL` | 防止函数返回，直到接受全部请求的字节数 |   | · |


`MSG_OOB`的真正意义在于督促数据接收对象尽快处理数据。这是紧急模式的全部内容，而且tcp“保持传输顺序”的传输特性依然成立。
