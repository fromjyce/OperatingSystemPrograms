#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main() {
int pipefd[2];
pid_t pid;
if (pipe(pipefd) == -1) {
perror("pipe");
exit(EXIT_FAILURE);
}
pid = fork();
if (pid == -1) {
perror("fork");
exit(EXIT_FAILURE);
}
if (pid == 0) {
close(pipefd[1]);
char buffer[100];
memset(buffer, 0, sizeof(buffer));
ssize_t bytes_read = read(pipefd[0], buffer, sizeof(buffer));
if (bytes_read == -1) {
perror("read");
exit(EXIT_FAILURE);
}
printf("Child Process Received: %s\n", buffer);
close(pipefd[0]);
} else {
close(pipefd[0]);
char message[] = "Hello from Parent!";
ssize_t bytes_written = write(pipefd[1], message, strlen(message));
if (bytes_written == -1) {
perror("write");
exit(EXIT_FAILURE);
}
close(pipefd[1]);
}
return 0;
}