#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024


int main(int argc, char *argv[]) {
	int serv_sock, clnt_sock;
	FILE * readfp;
	FILE * writefp;
	
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;
    char buf[BUF_SIZE] = { 0, };

    serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr));
	listen(serv_sock, 5);
    clnt_adr_sz = sizeof(clnt_adr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &clnt_adr_sz);

    // 调用fdopen函数生成FILE指针
    readfp = fdopen(clnt_sock, "r");
    // 调用dup函数，对clnt_sock套接字，复制出一个新的文件描述符
    writefp = fdopen(dup(clnt_sock), "w");

    fputs("FROM SERVER: Hi~ client? \n", writefp);
	fputs("I love all of the world \n", writefp);
	fputs("You are awesome! \n", writefp);
	fflush(writefp);
	
    // 针对`fileno`函数返回的文件描述符调用`shutdown`。从而，服务器端进入了半关闭状态，冰箱客户端发送`EOF`
    // 调用`shutdown`函数时，无论复制出多少文件描述符都可以进入半关闭状态，同时传递`EOF`。
	shutdown(fileno(writefp), SHUT_WR);
	fclose(writefp);
	
	fgets(buf, sizeof(buf), readfp); fputs(buf, stdout); 
	fclose(readfp);
	return 0;
}
