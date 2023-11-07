#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex, count;
int readerCount = 0;
int data = 0;

void *reader(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&count);
        readerCount++;
        if (readerCount == 1)
        {
            pthread_mutex_lock(&mutex);
        }
        pthread_mutex_unlock(&count);

        printf("\nReader %d Read %d", *((int *)arg), data);

        pthread_mutex_lock(&count);
        readerCount--;
        if (readerCount == 0)
            pthread_mutex_unlock(&mutex);
        pthread_mutex_unlock(&count);
        sleep(1);
    }
    pthread_exit(NULL);
}
void *writer(void *arg){
    while (1)
    {
        pthread_mutex_lock(&mutex);

        data = rand()%10;
        printf("\nWriter %d write %d",*((int *)arg),data);
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    int nR, nW;

    printf("\nEnter the No of Reader : ");
    scanf("%d", &nR);
    printf("\nEnter the No of Writer : ");
    scanf("%d", &nW);

    pthread_t readers[nR];
    pthread_t writers[nW];
    // init mutex
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&count, NULL);
    // creating the threads
    for (int i = 0; i < nR; i++)
        pthread_create(&readers[i], NULL, reader, &i);

    for (int i = 0; i < nW; i++)
        pthread_create(&writers[i], NULL, writer, &i);

    // wait for complete
    for (int i = 0; i < nR; i++)
        pthread_join(readers[i], NULL);

    for (int i = 0; i < nW; i++)
        pthread_join(writers[i], NULL);

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&count);

    return 0;
}
