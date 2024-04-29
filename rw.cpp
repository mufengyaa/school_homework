#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define M 20
sem_t sdata, sread;

void *reader(void *p)
{
    int id = *(int *)p + 1;
    while (1)
    {
        srand(time(NULL));
        int time = rand() % 3 + 1;
        sem_wait(&sdata);
        sem_wait(&sread);
        sem_post(&sdata);
        printf("%d号读者开始读取文件！\n", id);
        sleep(time);
        printf("%d号读者读取文件成功！\n", id);
        sem_post(&sread);
    }
    return NULL;
}

void *writer(void *p)
{
    int id = *(int *)p + 1;
    while (1)
    {
        srand(time(NULL));
        int time = rand() % 5 + 1;
        sem_wait(&sdata);
        for (int i = 0; i < M; i++)
            sem_wait(&sread);
        printf("%d号写者开始书写文件！\n", id);
        sleep(time);
        printf("%d号写者书写文件成功！\n", id);
        for (int i = 0; i < M; i++)
            sem_post(&sread);
        sem_post(&sdata);
    }
    return NULL;
}

int main(void)
{
    sem_init(&sdata, 0, 1);
    sem_init(&sread, 0, M);
    pthread_t tid[M], tid2[M];
    int thread_id[M];
    for (int i = 0; i < M; i++)
        thread_id[i] = i;
    for (int i = 0; i < M; i++)
    {
        int *t = thread_id + i;
        pthread_create(&tid[i], NULL, reader, (void *)t);
    }
    int thread2_id[M];
    for (int i = 0; i < M; i++)
        thread2_id[i] = i;
    for (int i = 0; i < M; i++)
    {
        int *d = thread2_id + i;
        pthread_create(&tid2[i], NULL, writer, (void *)d);
    }
    
    for (int i = 0; i < M; i++)
    {
        pthread_join(tid[i], NULL);
    }
    for (int i = 0; i < M; i++)
    {
        pthread_join(tid2[i], NULL);
    }

    sem_destroy(&sdata);
    sem_destroy(&sread);

    return 0;
}