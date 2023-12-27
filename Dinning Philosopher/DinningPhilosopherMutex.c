#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_mutex_t mutex;

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
        pthread_mutex_lock(&mutex);
        pthread_mutex_lock(&forks[left_fork]);
        pthread_mutex_lock(&forks[right_fork]);
        pthread_mutex_unlock(&mutex);

        // Eat
        logAction("is eating", id);
        sleep(1); // Simulating eating time

        // Release the forks
        pthread_mutex_unlock(&forks[left_fork]);
        pthread_mutex_unlock(&forks[right_fork]);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_mutex_init(&forks[i], NULL);
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

    // Destroy mutex
    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
/*
pseudo 
// Constants
NUM_PHILOSOPHERS = 5

// Mutexes
mutex: Mutex for critical sections
forks[NUM_PHILOSOPHERS]: Array of mutexes for each fork

// Function to log philosopher's action
logAction(action, id):
    print("Philosopher ", id, " ", action)

// Function for philosopher's behavior
philosopher(id):
    left_fork = id
    right_fork = (id + 1) % NUM_PHILOSOPHERS

    for i in range(3):  // Philosophers eat three times
        // Think
        logAction("is thinking", id)

        // Wait for the forks to be available
        lock(mutex)
        lock(forks[left_fork])
        lock(forks[right_fork])
        unlock(mutex)

        // Eat
        logAction("is eating", id)
        sleep(1)  // Simulating eating time

        // Release the forks
        unlock(forks[left_fork])
        unlock(forks[right_fork])

// Main function
main():
    threads[NUM_PHILOSOPHERS]: Array of threads for philosophers
    philosopher_ids[NUM_PHILOSOPHERS]: Array to store philosopher IDs

    // Initialize mutex
    initialize(mutex)

    // Initialize forks
    for i in range(NUM_PHILOSOPHERS):
        initialize(forks[i])

    // Create philosopher threads
    for i in range(NUM_PHILOSOPHERS):
        philosopher_ids[i] = i
        create_thread(philosopher, philosopher_ids[i], threads[i])

    // Join philosopher threads
    for i in range(NUM_PHILOSOPHERS):
        join_thread(threads[i])

    // Destroy mutex
    destroy(mutex)

    // Destroy forks
    for i in range(NUM_PHILOSOPHERS):
        destroy(forks[i])
*/