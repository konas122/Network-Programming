## Get host by name

```C
#include <netdb.h>

struct hostent *gethostbyname(const char *hostname);
```

成功则返回`hostent`结构体地址值，失败则返回`NULL`

```C
struct hostent
{
    char *h_name;       // office name
    char **h_aliases;   // alias list
    int h_addrtype;     // host address type
    int h_length;       // address length 
    ubt **h_addr_list;  // address list
}
```

## Get host by address

```C
#include <netdb.h>

struct hostent *gethostaddr(const char *addr, socklen_t len, int family);
/**
 * addr:    含IP地址信息的`in_addr`结构体指针。为了同时传递IPv4地址外的其他信息，该变量的类型声明为char指针
 * len:     向第一个参数传递地址信息的字节数，IPv4时为4，IPv6时为6
 * family:  传递地址族信息，IPv4时为AF_INET，IPv4时为AF_INET6
*/
```

成功则返回`hostent`结构体地址值，失败则返回`NULL`
