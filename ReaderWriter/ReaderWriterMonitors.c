#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_READERS 1
#define NUM_WRITERS 1

// Define monitor structure
struct Monitor {
    pthread_mutex_t mutex;
    pthread_cond_t readCondition;
    pthread_cond_t writeCondition;
    int buffer[BUFFER_SIZE];
    int readCount;
};

// Initialize the monitor
struct Monitor monitor = {
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .readCondition = PTHREAD_COND_INITIALIZER,
    .writeCondition = PTHREAD_COND_INITIALIZER,
    .buffer = {0},
    .readCount = 0,
};

void logAction(const char *action, int value, int id, const char *role) {
    printf("%-10s %d by %s %d\n", action, value, role, id);
}

void displayBuffer() {
    printf("Buffer: [");
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        if (monitor.buffer[i] < 10) {
            printf(" ");
        }
        printf("%d", monitor.buffer[i]);
        if (i < BUFFER_SIZE - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void startRead() {
    pthread_mutex_lock(&monitor.mutex);
    while (monitor.buffer[0] == 0) {
        pthread_cond_wait(&monitor.readCondition, &monitor.mutex);
    }
    monitor.readCount++;
    pthread_mutex_unlock(&monitor.mutex);
}

void endRead() {
    pthread_mutex_lock(&monitor.mutex);
    monitor.readCount--;
    if (monitor.readCount == 0) {
        pthread_cond_signal(&monitor.writeCondition);
    }
    pthread_mutex_unlock(&monitor.mutex);
}

void startWrite() {
    pthread_mutex_lock(&monitor.mutex);
    while (monitor.buffer[0] != 0) {
        pthread_cond_wait(&monitor.writeCondition, &monitor.mutex);
    }
}

void endWrite() {
    pthread_cond_signal(&monitor.readCondition);
    pthread_cond_signal(&monitor.writeCondition);
    pthread_mutex_unlock(&monitor.mutex);
}

void *reader(void *arg) {
    int reader_id = *(int *)arg;

    for (int i = 1; i <= 10; ++i) {
        startRead();

        // Read operation
        int value = monitor.buffer[0];  // Read the first element

        // Shift remaining elements in the buffer
        for (int i = 0; i < BUFFER_SIZE - 1; ++i) {
            monitor.buffer[i] = monitor.buffer[i + 1];
        }

        monitor.buffer[BUFFER_SIZE - 1] = 0;  // Set the last element to 0

        // Display the read element and the updated buffer
        logAction("Read:", value, reader_id, "Reader");
        printf("Buffer (after read): [");
        for (int i = 0; i < BUFFER_SIZE; ++i) {
            printf("%2d", monitor.buffer[i]);
            if (i < BUFFER_SIZE - 1) {
                printf(", ");
            }
        }
        printf("]\n");

        endRead();

        sleep(1);  // Simulate time taken to read
    }

    return NULL;
}

void *writer(void *arg) {
    int writer_id = *(int *)arg;

    for (int i = 1; i <= 5; ++i) {
        startWrite();

        // Write operation
        int value = i * 10;

        // Find the next available slot in the buffer
        int nextSlot = 0;
        while (monitor.buffer[nextSlot] != 0 && nextSlot < BUFFER_SIZE) {
            nextSlot++;
        }

        if (nextSlot < BUFFER_SIZE) {
            monitor.buffer[nextSlot] = value;
        } else {
            // Buffer is full, handle accordingly (e.g., wait or discard)
        }

        logAction("Write:", value, writer_id, "Writer");
        displayBuffer();

        endWrite();

        sleep(1);  // Simulate time taken to write
    }

    return NULL;
}

int main() {
    pthread_t readerThreads[NUM_READERS], writerThreads[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

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

    // Destroy mutexes
    pthread_mutex_destroy(&monitor.mutex);
    pthread_cond_destroy(&monitor.readCondition);
    pthread_cond_destroy(&monitor.writeCondition);

    return 0;
}
