## 半关闭

```C
#include <sys.socket.h>

int shutdown(int sock, int howto);

/**
 * sock:    虚断开的套接字文件描述符
 * howto:   传递方式信息
*/
```

成功时返回0，失败则返回-1

howto:
- SHUT_RD:      断开输入流
- SHUT_WR:      断开输出流
- SHUT_RDWR:    同时断开I/O流
