## 创建子进程

```C
#include <unistd.h>

pid_t fork(void);
```
创建成功：
- 父进程返回子进程`pid`
- 子进程返回0
失败则返回`-1`


## 销毁僵尸进程

### `wait()`

```C
#include <sys/wait.h>

pid_t wait(int *statloc);
```

成功则返回子进程`pid`，失败则返回`-1`

- `WIFEXITED`子进程正常终止时返回`true`
- `WEXITSTATUS`返回子进程的返回值


### `waitpid()`

```C
#include <sys/wait.h>

pid_t waitpid(pid_t pid, int *statloc, int options);
/**
 * pid:     等待终止的目标子进程`pid`，若传递`-1`，则与`wait()`相同
 * statloc: 同`wait()`的`statloc`
 * options: 传递`<sys/wait.h>`中声明的常量`WNOHANG`，即使没有终止的子进程也不会进入阻塞态，而是返回0
*/
```

成功则返回子进程`pid`（或0），失败则返回`-1`

