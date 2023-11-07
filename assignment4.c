#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5;

sem_t empty, full;
pthread_mutex_t mutex;
int in = 0, out = 0;
int buffer[5];

void *producer(void *arg)
{
    while (1)
    {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        // produce item
        buffer[in] = rand() % 10;
        printf("\nProducer produce %d", buffer[in]);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(1);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    while (1)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        // consume item
        printf("\nComsumer comsume %d", buffer[out]);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(2);
    }

    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    int nP, nC;

    printf("\nEnter the No of Producer : ");
    scanf("%d", &nP);
    printf("\nEnter the No of Consumer : ");
    scanf("%d", &nC);

    pthread_t producers[nP], consumers[nC];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);

    for (int i = 0; i < nP; i++)
        pthread_create(&producers[i], NULL, producer, NULL);

    for (int i = 0; i < nC; i++)
        pthread_create(&consumers[i], NULL, consumer, NULL);

    for (int i = 0; i < nP; i++)
        pthread_join(producers[i], NULL);

    for (int i = 0; i < nC; i++)
        pthread_join(consumers[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
