/*Implement interprocess communication (IPC) using shared memory on UNIX
to allow multiple processes to exchange data*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int main() {
key_t key = ftok("/tmp/myfile", 'R');
if (key == -1) {
perror("ftok");
exit(1);
}
int shmid = shmget(key, sizeof(int), 0666 | IPC_CREAT);
if (shmid == -1) {
perror("shmget");
exit(1);
}
int *shm_ptr;
shm_ptr = (int *)shmat(shmid, NULL, 0);
if (shm_ptr == (int *)-1) {
perror("shmat");
exit(1);
}
*shm_ptr = 42;
if (shmdt(shm_ptr) == -1) {
perror("shmdt");
exit(1);
}
printf("Shared memory operations completed successfully.\n");
return 0;
}
