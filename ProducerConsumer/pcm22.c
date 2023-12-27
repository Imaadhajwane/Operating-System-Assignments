#include <stdio.h>
#include <pthread.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *producer(void *arg) {
    int item = 1;
    while (1) {
        // Produce item
        sleep(1); // Simulate some delay

        pthread_mutex_lock(&mutex);

        // Check if the buffer is full
        if ((in + 1) % BUFFER_SIZE == out) {
            printf("Buffer is full. Producer waiting.\n");
            pthread_mutex_unlock(&mutex);
            sleep(1);
        } else {
            // Produce item
            buffer[in] = item;
            printf("Produced item %d at position %d\n", item, in);
            in = (in + 1) % BUFFER_SIZE;
            item++;

            pthread_mutex_unlock(&mutex);
        }
    }
}

void *consumer(void *arg) {
    while (1) {
        // Consume item
        sleep(2); // Simulate some delay

        pthread_mutex_lock(&mutex);

        // Check if the buffer is empty
        if (in == out) {
            printf("Buffer is empty. Consumer waiting.\n");
            pthread_mutex_unlock(&mutex);
            sleep(1);
        } else {
            // Consume item
            int item = buffer[out];
            printf("Consumed item %d from position %d\n", item, out);
            out = (out + 1) % BUFFER_SIZE;

            pthread_mutex_unlock(&mutex);
        }
    }
}

int main() {
    pthread_t producer1, producer2, consumer1, consumer2;

    pthread_create(&producer1, NULL, producer, NULL);
    pthread_create(&producer2, NULL, producer, NULL);
    pthread_create(&consumer1, NULL, consumer, NULL);
    pthread_create(&consumer2, NULL, consumer, NULL);

    pthread_join(producer1, NULL);
    pthread_join(producer2, NULL);
    pthread_join(consumer1, NULL);
    pthread_join(consumer2, NULL);

    return 0;
}
