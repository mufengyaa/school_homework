#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define c_num 3
#define p_num 5
#define space_num 10

sem_t space, prod, buf;

int Buffer[space_num];

int in = 0, out = 0;
int i = 1, j = 1;

void *producer(void *p)
{
    int id = *(int *)p + 1;
    while (1)
    {
        srand(time(NULL));
        int time = rand() % 3 + 1;
        sem_wait(&space);
        sem_wait(&buf);
        printf("%d号生产者进入缓冲区,准备将第%d个产品放置到Buffer[%d]的位置上！\n", id, i, in);
        sleep(time);
        printf("%d号生产者已经将第%d个产品放置到Buffer[%d]的位置上，退出缓冲区！\n", id, i, in);
        i++;
        in = (in + 1) % space_num;
        sem_post(&prod);
        sem_post(&buf);
    }
    return NULL;
}

void *consumer(void *p)
{
    int id = *(int *)p + 1;
    while (1)
    {
        srand(time(NULL));
        int time = rand() % 2 + 1;
        sem_wait(&prod);
        sem_wait(&buf);
        printf("%d号消费者进入缓冲区,准备将第%d个产品从Buffer[%d]的位置上取出！\n", id, j, out);
        sleep(time);
        printf("%d号消费者已经将第%d个产品从Buffer[%d]的位置上取出，退出缓冲区！\n", id, j, out);
        j++;
        out = (out + 1) % space_num;
        sem_post(&space);
        sem_post(&buf);
    }
    return NULL;
}

int main(void)
{
    sem_init(&space, 0, space_num);
    sem_init(&prod, 0, 0);
    sem_init(&buf, 0, 1);

    pthread_t tid[p_num], tid2[c_num];
    int thread_id[10];

    for (int i = 0; i < 10; i++)
    {
        thread_id[i] = i;
    }

    for (int i = 0; i < p_num; i++)
    {
        int *t = thread_id + i;
        pthread_create(&tid[i], NULL, producer, (void *)t);
    }
    for (int i = 0; i < c_num; i++)
    {
        int *d = thread_id + i;
        pthread_create(&tid2[i], NULL, consumer, (void *)d);
    }

    for (int i = 0; i < p_num; i++)
    {
        pthread_join(tid[i], NULL);
    }
    for (int i = 0; i < c_num; i++)
    {
        pthread_join(tid2[i], NULL);
    }

    sem_destroy(&space);
    sem_destroy(&prod);
    sem_destroy(&buf);

    return 0;
}