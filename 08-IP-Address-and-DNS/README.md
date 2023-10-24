## Get host by name

```C
#include <netdb.h>

struct hostent *gethostbyname(const char *hostname);
```

成功则返回`hostent`结构体，失败则返回`NULL`

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
