#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define OPSZ 4
void error_handling(char *message);
int calculate(int opnum, int opnds[], char operator);


int main(int argc, char *argv[]) {
    int serv_sock, clnt_sock;
    char message[BUF_SIZE];

    int result, opnd_cnt, i;
    int recv_cnt, recv_len;

    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;

    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(0);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() Error!");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() Error!");
    
    if (listen(serv_sock, 5) == -1)
        error_handling("listen() Error!");

    clnt_addr_size = sizeof(clnt_addr);
    for (i = 0; i < 5; i++) {
        opnd_cnt = 0;
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
        read(clnt_sock, &opnd_cnt, 1);

        recv_len = 0;
        while ((opnd_cnt * OPSZ + 1) > recv_len) {
            recv_cnt = read(clnt_sock, &message[recv_len], BUF_SIZE - 1);
            recv_len += recv_cnt;
        }
        result = calculate(opnd_cnt, (int *)message, message[recv_len - 1]);
        write(clnt_sock, (char *)&result, sizeof(result));
        close(clnt_sock);
    }
    close(serv_sock);

    return 0;
}


int calculate(int opnum, int opnds[], char operator) {
    puts("Calculating...");
    int result = opnds[0], i;
    switch(operator) {
        case '+':
            for (i = 0; i < opnum; i++)
                result += opnds[i];
            break;
        case '-':
            for (i = 0; i < opnum; i++)
                result -= opnds[i];
            break;
        case '*':
            for (i = 0; i < opnum; i++)
                    result *= opnds[i];
            break;
        case '/':
            for (i = 0; i < opnum; i++)
                result /= opnds[i];
            break;
    }
    printf("result: %d ", result);
    puts("Done...");
    return result;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputs('\n', stderr);
    exit(1);
}

