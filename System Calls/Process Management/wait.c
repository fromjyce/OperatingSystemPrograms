#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
pid_t p;
printf("Before Fork");
p = fork();
if (p==0) // child
{
printf("Child's ID: %d, ", getpid());
printf("Parent's ID: %d", getppid());
}
else
{
wait(NULL);
printf("Child's ID: %d", p);
printf("Parent's ID: %d", getpid());
}
printf("Common");
return 0;
}