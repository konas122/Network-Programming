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

`wait`函数会引起程序阻塞，还可以考虑调用`waitpid`函数，可以防止阻塞

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


## 信号处理

### `signal()`

```C
#include <signal.h>

void (*signal(int signo, void (*func)(int)))(int);
```

为了在产生信号时调用，返回之前注册的函数指针

返回类型为函数指针

上述函数中，第一个参数为特殊情况信息，第二个参数为特殊情况下将要调用的函数指针。

特殊情况：
- `SIGNALRM`:   已到通过调用`alarm`函数注册的时间
- `SIGINT`:     输入`CTRL+C`
- `SIGCHLD`:    子进程终止


### `alarm()`

```C
#include <unistd.h>

unsigned int alarm(unsigned int second);
```

返回0或以秒为单位的距`SIGALRM`信号发生所剩时间


### `sigaction()`

```C
#include <signal.h>

int sigaction(int signo, const struct sigaction *act, struct sigaction *oldact);
/**
 * `signo`:     与`signal`函数相同
 * `act`:       对应于第一个参数的信号处理函数信息
 * `oldact`:    通过此参数获取之前注册的信号处理函数指针，若不需要则传递0
*/
```

创建成功返回0，失败则返回`-1`


#### `struct sigaction`

```C
struct sigaction
{
    void (*sa_handler)(int);    // 信号处理函数的指针
    // 现在我们主要是防止僵尸进程，以下两个成员变量初始化为0即可，可暂时不用管
    sigset_t sa_mask;
    int sa_flags;
};
```
