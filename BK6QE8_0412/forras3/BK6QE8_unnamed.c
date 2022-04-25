#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd[2];
    int child;

    if(pipe(fd)) {
        perror("pipe");
        return 1;
    }

    child = fork();

    if(child > 0) {
        char s[1024];
        close(fd[1]);
        read(fd[0], s, sizeof(s));
        printf("%s", s);


        close(fd[0]);
    } else if (child == 0) {
        close(fd[0]);
        write(fd[1], "Sziraczki Soma BK6QE8\n", 21);
        close(fd[1]);
    }

    return 0;
}

