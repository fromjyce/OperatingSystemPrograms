/*Create a C program in a Unix environment that establishes communication
between a parent and a child process using a pipe for IPC, without directly
using the ’close()’ system call to close file descriptors.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main() {
int pipe_fd[2];
pid_t pid;
char message[] = "Hello, child!";
if (pipe(pipe_fd) == -1) {
perror("pipe");
exit(EXIT_FAILURE);
}
pid = fork();
if (pid == -1) {
perror("fork");
exit(EXIT_FAILURE);
}
if (pid == 0) {
close(pipe_fd[1]);
char buffer[100];
int bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));
if (bytes_read == -1) {
perror("read");
exit(EXIT_FAILURE);
}
buffer[bytes_read] = '\0';
printf("Child received: %s\n", buffer);
close(pipe_fd[0]);
} else {
close(pipe_fd[0]);
write(pipe_fd[1], message, strlen(message));
close(pipe_fd[1]);
printf("Parent sent: %s\n", message);
}
return 0;
}
