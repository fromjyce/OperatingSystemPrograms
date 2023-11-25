/*Create a C program in a Unix-based environment that uses pipes to count
the total number of processes created using the fork() system call.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
int pipefd[2];
int total_processes = 0;
if (pipe(pipefd) == -1) {
perror("pipe");
exit(EXIT_FAILURE);
}
for (int i = 0; i < 5; i++) {
pid_t child_pid = fork();
if (child_pid == -1) {
perror("fork");
exit(EXIT_FAILURE);
}
if (child_pid == 0) { // Child process
close(pipefd[0]); // Close the read end of the pipe
// Increment the count and send it to the parent
total_processes++;
write(pipefd[1], &total_processes, sizeof(int));
close(pipefd[1]); // Close the write end of the pipe in the child
exit(EXIT_SUCCESS);
}
}
close(pipefd[1]);
for (int i = 0; i < 5; i++) {
int child_count;
read(pipefd[0], &child_count, sizeof(int));
total_processes += child_count;
}
close(pipefd[0]);
printf("Total number of processes created: %d\n", total_processes);
return 0;
}
