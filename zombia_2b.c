#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int compare(const void *a, const void *b) 
{
return *(int *)a - *(int *)b;
}
int main() 
{
int pid, status;
int arr[] = {1, 5, 3, 2, 4};
pid = fork();
if (pid > 0) 
{
printf("Parent process sorting integers...\n");
qsort(arr, sizeof(arr) / sizeof(int), sizeof(int), compare);
printf("Parent process finished sorting integers.\n");
wait(&status);
} 
else 
{
printf("Child process sorting integers...\n");
qsort(arr, sizeof(arr) / sizeof(int), sizeof(int), compare);
printf("Child process finished sorting integers.\n");
exit(0);
}
if (WIFEXITED(status)) 
{
printf("Child process exited normally.\n");
} 
else if 
(WIFSIGNALED(status)) 
{
printf("Child process was terminated by a signal.\n");
} 
else 
{
printf("Child process is a zombie.\n");
}
return 0;
}
