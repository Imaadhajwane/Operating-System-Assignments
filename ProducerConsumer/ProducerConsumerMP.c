// To implement message passing between threads, you can use a shared data structure to exchange messages.
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 1
#define NUM_CONSUMERS 1
#define MAX_QUEUE_SIZE 10  // Maximum size of the message queue

// Define mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Buffer to store produced items
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Define message structure
typedef struct {
    int value;
    int id;
    const char *role;
} Message;

// Define message queue
Message messageQueue[MAX_QUEUE_SIZE];
int front = 0, rear = 0;

// Function to enqueue a message
void enqueueMessage(Message msg) {
    messageQueue[rear] = msg;
    rear = (rear + 1) % MAX_QUEUE_SIZE;
}

// Function to dequeue a message
Message dequeueMessage() {
    Message msg = messageQueue[front];
    front = (front + 1) % MAX_QUEUE_SIZE;
    return msg;
}

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

void displayQueue() {
    printf("Message Queue: [");
    for (int i = front; i != rear; i = (i + 1) % MAX_QUEUE_SIZE) {
        printf("(%d, %s, %d)", messageQueue[i].value, messageQueue[i].role, messageQueue[i].id);
        if ((i + 1) % MAX_QUEUE_SIZE != rear) {
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

        // Create a message and enqueue it
        Message msg = {item, producer_id, "Producer"};
        enqueueMessage(msg);
        displayQueue();

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

        // Check if there are messages in the queue
        if (front != rear) {
            // Dequeue a message
            Message msg = dequeueMessage();

            // Consume item from the message
            int item = msg.value;

            // Log consumed item and display buffer
            logAction("Consumed:", item, consumer_id, "Consumer");
            displayBuffer();
            displayQueue();
        }

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