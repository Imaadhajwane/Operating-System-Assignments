#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
sem_t mutex, empty, full;

int in = 0, out = 0;

void display_buffer() {
    printf("Buffer is now: [ ");
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        printf("%d ", buffer[i]);
    }
    printf("]\n");
}

void *producer(void *arg) {
    int item = 1;
    while (1) {
        // Produce item
        sleep(1); // Simulate some delay

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = item;
        printf("Produced item %d at position %d. ", item, in);
        in = (in + 1) % BUFFER_SIZE;
        item++;

        display_buffer();

        sem_post(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *arg) {
    while (1) {
        // Consume item
        sleep(2); // Simulate some delay

        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[out];
        printf("Consumed item %d from position %d. ", item, out);
        out = (out + 1) % BUFFER_SIZE;

        display_buffer();

        sem_post(&mutex);
        sem_post(&empty);
    }
}

int main() {
    pthread_t producer_thread, consumer1_thread, consumer2_thread;

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer1_thread, NULL, consumer, NULL);
    pthread_create(&consumer2_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer1_thread, NULL);
    pthread_join(consumer2_thread, NULL);

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
