#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 1
#define NUM_CONSUMERS 1

// Define mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Buffer to store produced items
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void logAction(const char *action, int value, int id, const char *role) {
    printf("%-10s %d by %s %d\n", action, value, role, id);
}

void displayBuffer() {
    printf("Buffer: [");
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        printf("%2d", buffer[i]);
        if (i < BUFFER_SIZE - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void *producer(void *arg) {
    int producer_id = *(int *)arg;

    for (int i = 1; i <= 5; ++i) {
        // Lock the mutex
        pthread_mutex_lock(&mutex);

        // Produce item
        int item = i * 10;
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        // Log produced item and display buffer
        logAction("Produced:", item, producer_id, "Producer");
        displayBuffer();

        // Unlock the mutex
        pthread_mutex_unlock(&mutex);

        // Sleep to simulate time taken to produce
        sleep(1);
    }

    return NULL;
}

void *consumer(void *arg) {
    int consumer_id = *(int *)arg;

    for (int i = 1; i <= 10; ++i) {
        // Lock the mutex
        pthread_mutex_lock(&mutex);

        // Consume item
        int item = buffer[out];
        buffer[out] = 0;
        out = (out + 1) % BUFFER_SIZE;

        // Log consumed item and display buffer
        logAction("Consumed:", item, consumer_id, "Consumer");
        displayBuffer();

        // Unlock the mutex
        pthread_mutex_unlock(&mutex);

        // Sleep to simulate time taken to consume
        sleep(1);
    }

    return NULL;
}

int main() {
    pthread_t producerThreads[NUM_PRODUCERS], consumerThreads[NUM_CONSUMERS];
    int producer_ids[NUM_PRODUCERS], consumer_ids[NUM_CONSUMERS];

    // Create producer threads
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        producer_ids[i] = i + 1;  // IDs start from 1
        pthread_create(&producerThreads[i], NULL, producer, &producer_ids[i]);
    }

    // Create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        consumer_ids[i] = i + 1;  // IDs start from 1
        pthread_create(&consumerThreads[i], NULL, consumer, &consumer_ids[i]);
    }

    // Join producer threads
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        pthread_join(producerThreads[i], NULL);
    }

    // Join consumer threads
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_join(consumerThreads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
/*Monitor:
    Mutex mutex
    int buffer[BUFFER_SIZE]
    int in, out

    Procedure produceItem(int item):
        buffer[in] = item
        in = (in + 1) % BUFFER_SIZE

    Function consumeItem():
        int item = buffer[out]
        buffer[out] = 0
        out = (out + 1) % BUFFER_SIZE
        return item

ProducerThread:
    Loop 5 times:
        Lock(mutex)
        Produce item
        Log produced item and display buffer
        Unlock(mutex)
        Sleep to simulate time taken to produce

ConsumerThread:
    Loop 10 times:
        Lock(mutex)
        Consume item
        Log consumed item and display buffer
        Unlock(mutex)
        Sleep to simulate time taken to consume

Main:
    Initialize mutex, buffer, in, and out

    Create producer thread
    Create consumer thread

    Start producer thread
    Start consumer thread

    Join producer thread
    Join consumer thread
*/
