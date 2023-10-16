## `open()`

打开文件

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

关闭文件

```C
#include <unistd.h>

int close(int fd);
/**
 * fd: 需要关闭的文件或套接字的文件描述符
*/
```

成功时返回0，失败则返回-1

## `write()`

将数据写入文件

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

读取文件中的数据

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


