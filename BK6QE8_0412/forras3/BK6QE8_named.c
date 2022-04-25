#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int child;

    mkfifo("Sziraczki Soma", S_IRUSR | S_IWUSR);
    child = fork();

    if(child > 0) {
        char s[888];
        int fd;

        fd = open("Sziraczki Soma", O_RDONLY);
        read(fd, s, sizeof(s));
        printf("%s", s);
        close(fd);
        unlink("Sziraczki Soma");

    } else if(child == 0) {
        int fd = open("Sziraczki Soma", O_RDONLY);
        write(fd, "SZS BK6QE8\n", 12);
        close(fd);
    }
    return 0;
}
