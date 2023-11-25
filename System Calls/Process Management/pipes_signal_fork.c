/*Create a C program on a UNIX-like OS that uses pipes and signals to
count the number of processes created by fork() while allowing the child to
write and the parent to read without using wait().*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
int main() {
int pipefd[2];
int count = 0;
if (pipe(pipefd) == -1) {
perror("pipe");
exit(EXIT_FAILURE);
}
pid_t child_pid = fork();
if (child_pid == -1) {
perror("fork");
exit(EXIT_FAILURE);
}
if (child_pid == 0) {
close(pipefd[0]);
sleep(1);
kill(getppid(), SIGUSR1);
exit(EXIT_SUCCESS);
} else {
close(pipefd[1]);
pause();
count++;
char buffer[1];
while (read(pipefd[0], buffer, 1) > 0) {
count++;
}
printf("Number of processes created by fork(): %d\n", count);
close(pipefd[0]);
exit(EXIT_SUCCESS);
}
return 0;
}
