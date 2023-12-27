#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer = 0; // Shared buffer
int readers_count = 0; // Number of readers currently accessing the buffer
sem_t mutex, write_mutex, read_mutex;

void *writer(void *arg) {
    int item = 1;
    while (1) {
        // Write item to buffer
        sleep(1); // Simulate some delay

        sem_wait(&write_mutex);

        printf("Writer %ld is writing item %d to buffer.\n", (long)arg, item);
        buffer = item;
        item++;

        printf("Buffer is now: %d\n", buffer);

        sem_post(&write_mutex);
    }
}

void *reader(void *arg) {
    while (1) {
        // Read item from buffer
        sleep(2); // Simulate some delay

        sem_wait(&read_mutex);
        sem_wait(&mutex);
        readers_count++;

        if (readers_count == 1) {
            sem_wait(&write_mutex);
        }

        sem_post(&mutex);
        sem_post(&read_mutex);

        printf("Reader %ld is reading item %d from buffer.\n", (long)arg, buffer);

        sem_wait(&mutex);
        readers_count--;

        if (readers_count == 0) {
            sem_post(&write_mutex);
        }

        sem_post(&mutex);
    }
}

int main() {
    pthread_t writer1_thread, writer2_thread, reader1_thread, reader2_thread;

    sem_init(&mutex, 0, 1);
    sem_init(&write_mutex, 0, 1);
    sem_init(&read_mutex, 0, 1);

    pthread_create(&writer1_thread, NULL, writer, (void *)1);
    pthread_create(&writer2_thread, NULL, writer, (void *)2);
    pthread_create(&reader1_thread, NULL, reader, (void *)1);
    pthread_create(&reader2_thread, NULL, reader, (void *)2);

    pthread_join(writer1_thread, NULL);
    pthread_join(writer2_thread, NULL);
    pthread_join(reader1_thread, NULL);
    pthread_join(reader2_thread, NULL);

    sem_destroy(&mutex);
    sem_destroy(&write_mutex);
    sem_destroy(&read_mutex);

    return 0;
}
