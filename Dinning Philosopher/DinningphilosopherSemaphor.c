#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

// Define semaphores
sem_t forks[NUM_PHILOSOPHERS];
sem_t mutex;

void logAction(const char *action, int id) {
    printf("Philosopher %d %s\n", id, action);
}

void *philosopher(void *arg) {
    int id = *(int *)arg;

    // Philosophers are numbered from 0 to NUM_PHILOSOPHERS - 1
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    for (int i = 0; i < 3; ++i) {
        // Think
        logAction("is thinking", id);

        // Wait for the forks to be available
        sem_wait(&mutex);
        sem_wait(&forks[left_fork]);
        sem_wait(&forks[right_fork]);
        sem_post(&mutex);

        // Eat
        logAction("is eating", id);
        sleep(1); // Simulating eating time

        // Release the forks
        sem_post(&forks[left_fork]);
        sem_post(&forks[right_fork]);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        sem_init(&forks[i], 0, 1);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Join philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        sem_destroy(&forks[i]);
    }

    return 0;
}
/*
pseudo
// Define constants
NUM_PHILOSOPHERS = 5

// Define semaphores
sem_t forks[NUM_PHILOSOPHERS]
sem_t mutex

// Function to log philosopher's action
function logAction(action, id)
    print("Philosopher", id, action)

// Philosopher function
function philosopher(id)
    left_fork = id
    right_fork = (id + 1) % NUM_PHILOSOPHERS

    repeat 3 times:
        // Think
        logAction("is thinking", id)

        // Wait for forks
        wait(mutex)
        wait(forks[left_fork])
        wait(forks[right_fork])
        signal(mutex)

        // Eat
        logAction("is eating", id)
        sleep(1) // Simulating eating time

        // Release forks
        signal(forks[left_fork])
        signal(forks[right_fork])

// Main function
function main()
    // Initialize semaphores
    init(mutex, 1)
    for i = 0 to NUM_PHILOSOPHERS - 1:
        init(forks[i], 1)

    // Create philosopher threads
    for i = 0 to NUM_PHILOSOPHERS - 1:
        create_thread(philosopher, i)

    // Join philosopher threads
    for i = 0 to NUM_PHILOSOPHERS - 1:
        join_thread(philosophers[i])

    // Destroy semaphores
    destroy(mutex)
    for i = 0 to NUM_PHILOSOPHERS - 1:
        destroy(forks[i])
*/