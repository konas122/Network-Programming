# 使用标准`I/O`函数

## 利用`fdopen`函数转换为`FILE`结构体

```C
#include <stdio.h>

FILE *fdopen(int fildes, const char *mode);
/**
 * fildes:  需要转换的文件描述符
 * mode:    将要创建的FILE结构体的模式(mode)信息
*/
```

成功则返回转换的`FILE`结构体指针，失败则返回`NULL`

**Example**: [desto.c](./desto.c#L15)


## 利用`fdopen`函数转换为文件描述符

```C
#include <stdio.h>

int fileno(FILE *stream);
```

成功则返回转换的文件描述符，失败则返回-1

**Example**: [todes.c](./todes.c#L16)
