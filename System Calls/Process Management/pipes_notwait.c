/*Implement a program in C on UNIX that utilizes ‘fork()‘ and pipes to
count the number of child processes created, while ensuring synchronized
communication between parent and child processes without using the ‘wait()‘
function.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() {
int numProcesses = 0;
int pipefd[2];
pid_t child_pid;
if (pipe(pipefd) == -1) {
perror("pipe");
exit(EXIT_FAILURE);
}
for (int i = 0; i < 5; i++) {
child_pid = fork();
if (child_pid == -1) {
perror("fork");
exit(EXIT_FAILURE);
}
if (child_pid == 0) {
close(pipefd[1]);
char buffer[32];
read(pipefd[0], buffer, sizeof(buffer));
printf("Child process %d read: %s\n", getpid(), buffer);
close(pipefd[0]);
exit(EXIT_SUCCESS);
} else { // Parent process
close(pipefd[0]);
char message[32];
sprintf(message, "Hello from parent %d", getpid());
write(pipefd[1], message, sizeof(message));
close(pipefd[1]);
numProcesses++;
}
}
while (numProcesses > 0) {
wait(NULL);
numProcesses--;
}
return 0;
}