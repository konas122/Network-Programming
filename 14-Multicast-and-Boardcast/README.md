# 多播

多播（multicast）是基于`UDP`完成的，可以同时向多个主机传输数据


## 设置`TTL`

`TTL`（`Time to Live`生存时间），可参考[Chapter-09-README](../09-Socket-Optional-Types/README.md)

**code**: [news_sender.c](./news_sender.c)

```C
int send_sock;
int time_alive = 64;
...
send_sock = socket(PF_INET, SOCK_DGRAM, 0);
setsockopt(send_sock, IPPROTO_IP, IP_MULTICAST_TTL, (void *)&time_alive, sizeof(time_alive));
...
```

## 加入多播组

`setsockopt`可参考[Chapter-09-README](../09-Socket-Optional-Types/README.md)

**code**: [news_receiver.c](./news_receiver.c)

```C
int recv_sock;
struct ip_mreq join_addr;
...
recv_sock = socket(PF_INET, SOCK_DGRAM, 0);
...
join_addr.imr_multiaddr.s_addr = "多播组地址信息";
join_addr.imr_interface.s_addr = "加入多播组的主机地址信息";
...
setsockopt(send_sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&time_alive, sizeof(time_alive));

...
```

```C
struct ip_mreq
{
    struct in_addr imr_multiaddr;
    struct in_addr imr_interface;
};
```

# 广播

广播（Boardcast）在“一次性向多个主机发送数据”这一点与多播有些类似，但传输范围有区别。多播即使在跨越不同网络下，只要加入了多播组就能接收数据。

相反，广播只能向同一个网络中的主机传输数据。
