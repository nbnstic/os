#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
int main() {
   int f1, f2;
 char buf[100], str1[100];  
    if (mkfifo("fifo1", 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }
    printf("Enter a String: \n");
    fgets(str1, 100, stdin);
    f1 = open("fifo1", O_WRONLY);
    write(f1, str1, strlen(str1));
    close(f1);
 if (mkfifo("fifo2", 0666) == -1) {
 perror("mkfifo");
  exit(1);
    }
    f2 = open("fifo2", O_RDONLY);
    read(f2, buf, sizeof(buf));
    close(f2);
    printf("\n%s\n", buf);
return 0;}
