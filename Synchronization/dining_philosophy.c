/*Implementation of Dining Philosophy Problem*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#define NUM_PHILOSOPHERS 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
int state[NUM_PHILOSOPHERS];
sem_t mutex;
sem_t S[NUM_PHILOSOPHERS];
void test(int phnum) {
if (state[phnum] == HUNGRY && state[(phnum + 1) %
NUM_PHILOSOPHERS] != EATING
&& state[(phnum + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS] != EATING) {
state[phnum] = EATING;
sleep(2);
printf("Philosopher %d picks up forks %d and %d\n", phnum, (phnum + 1)
% NUM_PHILOSOPHERS, phnum);
printf("Philosopher %d is eating\n", phnum);
sem_post(&S[phnum]);
}
}
void take_forks(int phnum) {
sem_wait(&mutex);
state[phnum] = HUNGRY;
printf("Philosopher %d is hungry\n", phnum);
test(phnum);
sem_post(&mutex);
sem_wait(&S[phnum]);
sleep(1);
}
void put_forks(int phnum) {
sem_wait(&mutex);
state[phnum] = THINKING;
printf("Philosopher %d puts down forks %d and %d\n", phnum, (phnum + 1)
% NUM_PHILOSOPHERS, phnum);
printf("Philosopher %d is thinking\n", phnum);
test((phnum + 1) % NUM_PHILOSOPHERS);
test((phnum + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS);
sem_post(&mutex);
}
void* philosopher(void* num) {
int* phnum = (int*)num;
while (1) {
sleep(1);
take_forks(*phnum);
sleep(0);
put_forks(*phnum);
}
}
int main() {
int i;
pthread_t thread_id[NUM_PHILOSOPHERS];
sem_init(&mutex, 0, 1);
for (i = 0; i < NUM_PHILOSOPHERS; i++)
sem_init(&S[i], 0, 0);
for (i = 0; i < NUM_PHILOSOPHERS; i++) {
pthread_create(&thread_id[i], NULL, philosopher, &i);
printf("Philosopher %d is thinking\n", i);
}
for (i = 0; i < NUM_PHILOSOPHERS; i++)
pthread_join(thread_id[i], NULL);
return 0;
}
