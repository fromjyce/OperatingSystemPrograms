#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
int main() {
const char *fifo_name = "myfifo";
int fifo_fd;
char buffer[256];
fifo_fd = open(fifo_name, O_RDONLY);
if (fifo_fd == -1) {
perror("Error opening FIFO for reading");
exit(EXIT_FAILURE);
}
ssize_t bytes_read = read(fifo_fd, buffer, sizeof(buffer));
if (bytes_read == -1) {
perror("Error reading from FIFO");
exit(EXIT_FAILURE);
}
printf("Received: %s\n", buffer);
close(fifo_fd);
return 0;
}
