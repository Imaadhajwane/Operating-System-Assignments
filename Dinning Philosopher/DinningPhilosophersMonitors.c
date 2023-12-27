#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define NUM_CYCLES 3

enum {
    THINKING,
    HUNGRY,
    EATING
} state[NUM_PHILOSOPHERS];

pthread_mutex_t mutex;
pthread_cond_t forks[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int id = *(int *)arg;

    for (int cycle = 0; cycle < NUM_CYCLES; ++cycle) {
        printf("Philosopher %d is thinking (Cycle %d)\n", id, cycle + 1);

        usleep(rand() % 1000000); // Simulate thinking

        pthread_mutex_lock(&mutex);
        state[id] = HUNGRY;
        printf("Philosopher %d is hungry (Cycle %d)\n", id, cycle + 1);
        test(id);
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex);
        if (state[id] != EATING) {
            pthread_cond_wait(&forks[id], &mutex);
        }
        pthread_mutex_unlock(&mutex);

        // Philosopher is eating
        printf("Philosopher %d is eating (Cycle %d)\n", id, cycle + 1);

        usleep(rand() % 1000000); // Simulate eating

        pthread_mutex_lock(&mutex);
        state[id] = THINKING;
        printf("Philosopher %d has finished eating (Cycle %d)\n", id, cycle + 1);
        test((id + 1) % NUM_PHILOSOPHERS);
        test((id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void test(int id) {
    if (state[id] == HUNGRY &&
        state[(id + 1) % NUM_PHILOSOPHERS] != EATING &&
        state[(id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS] != EATING) {

        state[id] = EATING;
        pthread_cond_signal(&forks[id]);
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_cond_init(&forks[i], NULL);
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_join(philosophers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_cond_destroy(&forks[i]);
    }

    return 0;
}
