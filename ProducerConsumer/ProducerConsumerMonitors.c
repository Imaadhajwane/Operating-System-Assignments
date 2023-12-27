#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 1
#define NUM_CONSUMERS 1
#define MAX_QUEUE_SIZE 10  // Maximum size of the message queue

// Define message structure
typedef struct {
    int value;
    int id;
    const char *role;
} Message;

// Define monitor
typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t bufferNotEmpty;
    pthread_cond_t bufferNotFull;
    pthread_cond_t queueNotEmpty;
    pthread_cond_t queueNotFull;

    // Buffer and message queue
    int buffer[BUFFER_SIZE];
    Message messageQueue[MAX_QUEUE_SIZE];
    int in, out, front, rear;
} Monitor;

// Initialize the monitor
Monitor monitor = {
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .bufferNotEmpty = PTHREAD_COND_INITIALIZER,
    .bufferNotFull = PTHREAD_COND_INITIALIZER,
    .queueNotEmpty = PTHREAD_COND_INITIALIZER,
    .queueNotFull = PTHREAD_COND_INITIALIZER,
    .in = 0,
    .out = 0,
    .front = 0,
    .rear = 0,
};

// Function to enqueue a message in the monitor
void enqueueMessage(Monitor *mon, Message msg) {
    mon->messageQueue[mon->rear] = msg;
    mon->rear = (mon->rear + 1) % MAX_QUEUE_SIZE;
}

// Function to dequeue a message in the monitor
Message dequeueMessage(Monitor *mon) {
    Message msg = mon->messageQueue[mon->front];
    mon->front = (mon->front + 1) % MAX_QUEUE_SIZE;
    return msg;
}

// Function to produce item in the monitor
void produceItem(Monitor *mon, int item, int producer_id) {
    mon->buffer[mon->in] = item;
    mon->in = (mon->in + 1) % BUFFER_SIZE;
}

// Function to consume item in the monitor
int consumeItem(Monitor *mon) {
    int item = mon->buffer[mon->out];
    mon->out = (mon->out + 1) % BUFFER_SIZE;
    return item;
}

void logAction(const char *action, int value, int id, const char *role) {
    printf("%-10s %d by %s %d\n", action, value, role, id);
}

void displayBuffer(Monitor *mon) {
    printf("Buffer: [");
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        printf("%2d", mon->buffer[i]);
        if (i < BUFFER_SIZE - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void displayQueue(Monitor *mon) {
    printf("Message Queue: [");
    for (int i = mon->front; i != mon->rear; i = (i + 1) % MAX_QUEUE_SIZE) {
        printf("(%d, %s, %d)", mon->messageQueue[i].value, mon->messageQueue[i].role, mon->messageQueue[i].id);
        if ((i + 1) % MAX_QUEUE_SIZE != mon->rear) {
            printf(", ");
        }
    }
    printf("]\n");
}

void *producer(void *arg) {
    int producer_id = *(int *)arg;

    for (int i = 1; i <= 5; ++i) {
        // Lock the monitor
        pthread_mutex_lock(&monitor.mutex);

        // Wait until the buffer is not full
        while (((monitor.in + 1) % BUFFER_SIZE) == monitor.out) {
            pthread_cond_wait(&monitor.bufferNotFull, &monitor.mutex);
        }

        // Produce item
        int item = i * 10;
        produceItem(&monitor, item, producer_id);

        // Log produced item and display buffer
        logAction("Produced:", item, producer_id, "Producer");
        displayBuffer(&monitor);

        // Enqueue a message
        Message msg = {item, producer_id, "Producer"};
        enqueueMessage(&monitor, msg);
        displayQueue(&monitor);

        // Signal that the buffer is not empty
        pthread_cond_signal(&monitor.bufferNotEmpty);

        // Unlock the monitor
        pthread_mutex_unlock(&monitor.mutex);

        // Sleep to simulate time taken to produce
        sleep(1);
    }

    return NULL;
}

void *consumer(void *arg) {
    int consumer_id = *(int *)arg;

    for (int i = 1; i <= 10; ++i) {
        // Lock the monitor
        pthread_mutex_lock(&monitor.mutex);

        // Wait until the queue is not empty
        while (monitor.front == monitor.rear) {
            pthread_cond_wait(&monitor.queueNotEmpty, &monitor.mutex);
        }

        // Dequeue a message
        Message msg = dequeueMessage(&monitor);

        // Consume item from the message
        int item = msg.value;

        // Log consumed item and display buffer
        logAction("Consumed:", item, consumer_id, "Consumer");
        displayBuffer(&monitor);
        displayQueue(&monitor);

        // Signal that the queue is not full
        pthread_cond_signal(&monitor.queueNotFull);

        // Unlock the monitor
        pthread_mutex_unlock(&monitor.mutex);

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

    return 0;
}
/*Monitor:
    Mutex mutex
    ConditionVariable bufferNotEmpty
    ConditionVariable bufferNotFull
    ConditionVariable queueNotEmpty
    ConditionVariable queueNotFull
    int buffer[BUFFER_SIZE]
    Message messageQueue[MAX_QUEUE_SIZE]
    int in, out, front, rear

enqueueMessage(Monitor mon, Message msg):
    mon.messageQueue[mon.rear] = msg
    mon.rear = (mon.rear + 1) % MAX_QUEUE_SIZE

dequeueMessage(Monitor mon):
    Message msg = mon.messageQueue[mon.front]
    mon.front = (mon.front + 1) % MAX_QUEUE_SIZE
    return msg

produceItem(Monitor mon, int item, int producer_id):
    mon.buffer[mon.in] = item
    mon.in = (mon.in + 1) % BUFFER_SIZE

int consumeItem(Monitor mon):
    int item = mon.buffer[mon.out]
    mon.out = (mon.out + 1) % BUFFER_SIZE
    return item

void producer(int producer_id):
    for i = 1 to 5:
        lock(mon.mutex)
        while (mon.in + 1) % BUFFER_SIZE == mon.out:
            wait(mon.bufferNotFull, mon.mutex)
        
        int item = i * 10
        produceItem(mon, item, producer_id)
        logAction("Produced:", item, producer_id, "Producer")
        displayBuffer(mon)
        
        Message msg = {item, producer_id, "Producer"}
        enqueueMessage(mon, msg)
        displayQueue(mon)
        
        signal(mon.bufferNotEmpty)
        unlock(mon.mutex)
        sleep(1)

void consumer(int consumer_id):
    for i = 1 to 10:
        lock(mon.mutex)
        while mon.front == mon.rear:
            wait(mon.queueNotEmpty, mon.mutex)
        
        Message msg = dequeueMessage(mon)
        int item = msg.value
        
        logAction("Consumed:", item, consumer_id, "Consumer")
        displayBuffer(mon)
        displayQueue(mon)
        
        signal(mon.queueNotFull)
        unlock(mon.mutex)
        sleep(1)

Main:
    Initialize mon.mutex, mon.bufferNotEmpty, mon.bufferNotFull, mon.queueNotEmpty, mon.queueNotFull
    mon.in = 0, mon.out = 0, mon.front = 0, mon.rear = 0

    for i = 1 to NUM_PRODUCERS:
        Create producer thread i
        Start producer thread i

    for i = 1 to NUM_CONSUMERS:
        Create consumer thread i
        Start consumer thread i

    for i = 1 to NUM_PRODUCERS:
        Join producer thread i

    for i = 1 to NUM_CONSUMERS:
        Join consumer thread i
*/