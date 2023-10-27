#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    int status;
    pid_t pid = fork();

    if (pid == 0) {
        sleep(16);
        return 3;
    }
    else
    {
        while (!waitpid(pid, &status, WNOHANG))
        {
            sleep(2);
            puts("sleep 2sec. ");
        }

        if (WIFEXITED(status))
            printf("Child send %d \n", WEXITSTATUS(status));
    }

    return 0;
}
