#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    char buf[20];
    int bufLenght;
    int fileDescriptor;
    int writeInfo;
    int readInfo;
    int seekInfo;

    //Fájl megnyitása

    fileDescriptor = open("BK6QE8.txt",O_RDWR);
    if (fileDescriptor == -1) {
        perror("open() hiba:");
        exit(fileDescriptor);
    }
    printf("File Descriptor erteke: %d\n",fileDescriptor);

    seekInfo = lseek(fileDescriptor, 0, SEEK_SET);
    if (seekInfo == -1){
        perror ("A pozicionalas nem volt sikeres.");
        exit(seekInfo);
    }
    printf("A kurzor pozicioja: %d\n", seekInfo);

    readInfo = read(fileDescriptor, buf, 15);
    if (readInfo == -1){
        perror("Az olvasas nem volt sikeres.");
        exit(seekInfo);
    }
    printf("A read() erteke: %d\n",readInfo);
    printf("A beolvasott ertek: %s", buf);

    strcpy (buf, "Ez egy teszt");
    bufLenght = strlen(buf);
    writeInfo = write(fileDescriptor, buf, bufLenght);
    if (writeInfo == -1){
        perror("Az iras nem volt sikeres.");
        exit(writeInfo);
    }
    printf("A write()-al beirt byte-ok szama: %d\n", writeInfo);
    return 0;
}
