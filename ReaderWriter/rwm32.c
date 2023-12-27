#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer = 0; // Shared buffer
int readers_count = 0; // Number of readers currently accessing the buffer
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t write_mutex = PTHREAD_MUTEX_INITIALIZER;

void display_buffer_state(const char *message) {
    printf("%s Buffer State: %d\n", message, buffer);
}

void *writer(void *arg) {
    int item = 1;
    while (1) {
        // Write item to buffer
        sleep(1); // Simulate some delay

        pthread_mutex_lock(&write_mutex);

        printf("Writer %ld is waiting to write.\n", (long)arg);

        // Wait until there are no readers
        while (readers_count > 0) {
            display_buffer_state("Writer is waiting.");
            pthread_mutex_unlock(&write_mutex);
            sleep(1); // Introduce a delay before retrying
            pthread_mutex_lock(&write_mutex);
        }

        printf("Writer %ld is writing item %d to buffer.\n", (long)arg, item);
        buffer = item;
        item++;

        display_buffer_state("Writer wrote to buffer.");

        pthread_mutex_unlock(&write_mutex);
    }
}

void *reader(void *arg) {
    while (1) {
        // Read item from buffer
        sleep(2); // Simulate some delay

        pthread_mutex_lock(&mutex);
        readers_count++;

        if (readers_count == 1) {
            pthread_mutex_lock(&write_mutex);
        }

        pthread_mutex_unlock(&mutex);

        printf("Reader %ld is reading item %d from buffer.\n", (long)arg, buffer);

        pthread_mutex_lock(&mutex);
        readers_count--;

        if (readers_count == 0) {
            pthread_mutex_unlock(&write_mutex);
        }

        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    pthread_t writer1_thread, writer2_thread, reader1_thread, reader2_thread, reader3_thread;

    pthread_create(&writer1_thread, NULL, writer, (void *)1);
    pthread_create(&writer2_thread, NULL, writer, (void *)2);
    pthread_create(&reader1_thread, NULL, reader, (void *)1);
    pthread_create(&reader2_thread, NULL, reader, (void *)2);
    pthread_create(&reader3_thread, NULL, reader, (void *)3);

    pthread_join(writer1_thread, NULL);
    pthread_join(writer2_thread, NULL);
    pthread_join(reader1_thread, NULL);
    pthread_join(reader2_thread, NULL);
    pthread_join(reader3_thread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&write_mutex);

    return 0;
}
