#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_READERS 3
#define NUM_WRITERS 2

// Define semaphores
sem_t mutex, readCountMutex, writeMutex;

// Buffer to store values
int buffer[BUFFER_SIZE];
int readCount = 0;

void logAction(const char *action, int value, int id, const char *role) {
    printf("%-10s %d by %s %d\n", action, value, role, id);
}

void displayBuffer() {
    printf("Buffer: [");
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        if (buffer[i] < 10) {
            printf(" ");
        }
        printf("%d", buffer[i]);
        if (i < BUFFER_SIZE - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void *reader(void *arg) {
    int reader_id = *(int *)arg;

    for (int i = 1; i <= 10; ++i) {
        sem_wait(&mutex);
        sem_wait(&readCountMutex);
        readCount++;
        if (readCount == 1) {
            sem_wait(&writeMutex);
        }
        sem_post(&readCountMutex);
        sem_post(&mutex);

        // Read operation
        int value = buffer[0];  // Read the first element

        logAction("Read:", value, reader_id, "Reader");
        displayBuffer();

        sem_wait(&readCountMutex);
        readCount--;
        if (readCount == 0) {
            sem_post(&writeMutex);
        }
        sem_post(&readCountMutex);

        sleep(1);  // Simulate time taken to read
    }

    return NULL;
}

void *writer(void *arg) {
    int writer_id = *(int *)arg;

    for (int i = 1; i <= 5; ++i) {
        sem_wait(&writeMutex);

        // Write operation
        int value = i * 10;
        buffer[0] = value;  // Write to the first element

        logAction("Write:", value, writer_id, "Writer");
        displayBuffer();

        sem_post(&writeMutex);

        sleep(1);  // Simulate time taken to write
    }

    return NULL;
}

int main() {
    pthread_t readerThreads[NUM_READERS], writerThreads[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&readCountMutex, 0, 1);
    sem_init(&writeMutex, 0, 1);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; ++i) {
        reader_ids[i] = i + 1;
        pthread_create(&readerThreads[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; ++i) {
        writer_ids[i] = i + 1;
        pthread_create(&writerThreads[i], NULL, writer, &writer_ids[i]);
    }

    // Join reader threads
    for (int i = 0; i < NUM_READERS; ++i) {
        pthread_join(readerThreads[i], NULL);
    }

    // Join writer threads
    for (int i = 0; i < NUM_WRITERS; ++i) {
        pthread_join(writerThreads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&readCountMutex);
    sem_destroy(&writeMutex);

    return 0;
}
