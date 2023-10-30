#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h> 
int main() {
int f1, f2, i = 0;
char str[100];
int chart = 0, word = 0, st = 0;
char a[50], b[20], c[20];
FILE *file;
mkfifo("fifo2", 0666);
f1 = open("fifo1", O_RDONLY); 
if (f1 == -1) {
perror("Error opening fifo1");
 exit(1);
 }
    read(f1, str, 100);
    close(f1);
printf("Data Received from process1: %s", str);
while (str[i] != '\0') {
if (str[i] != ' ' && str[i] != '\n') {
chart++;
}
if (str[i] == ' ' || str[i] == '\n') {
word++;
}
if (str[i] == '\n') {
st++;
}
i++;
}
if (chart > 0) {
chart++;
word++;
}
printf("\nNo of characters are %d, words are %d, and sentences are %d.\n", chart, word, st);
f2 = open("fifo2", O_WRONLY); // Open for writing
if (f2 == -1) {
perror("Error opening fifo2");
exit(1);
 }
file = fopen("test.txt", "w");
fprintf(file, "Characters:%d Words:%d Sentences:%d.%s", chart, word, st, str);
fclose(file);
file = fopen("test.txt", "r");
fscanf(file, "%s %s %s", a, b, c);
fclose(file);
strcat(a, b);
strcat(a, c);
write(f2, a, strlen(a) + 1);
close(f2);
return 0;
}
