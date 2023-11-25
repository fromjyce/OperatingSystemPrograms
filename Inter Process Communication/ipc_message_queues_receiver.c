/*Implementation of IPC using Message Queues - Receiver Program*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct mesg_buffer {
long mesg_type;
char mesg_text[100];
} message;
int main()
{
key_t key;
int msgid;
key = ftok("somefile", 65);
msgid = msgget(key, 0666 | IPC_CREAT);
printf("Waiting for a message from client...\n");
msgrcv(msgid, &message, sizeof(message), 1, 0);
printf("Message received from client : %s\n",message.mesg_text);
msgctl(msgid, IPC_RMID, NULL);
return 0;
}