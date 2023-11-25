#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
int main() {
const char *fifo_name = "myfifo";
int fifo_fd;
fifo_fd = open(fifo_name, O_WRONLY);
if (fifo_fd == -1) {
perror("Error opening FIFO for writing");
exit(EXIT_FAILURE);
}
char message[] = "Hello, FIFO!";
write(fifo_fd, message, strlen(message) + 1);
close(fifo_fd);
return 0;
}