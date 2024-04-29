#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

sem_t sfork[5];

void *philosopher(void *p)
{ // 方案1
    int id = *((int *)p);
    while (1)
    {
        srand(time(NULL));
        int time = rand() % 3 + 1;
        sleep(time);
        if (id % 2 == 0)
        {
            sem_wait(&sfork[id]);
            sem_wait(&sfork[(id + 1) % 5]);
        }
        else
        {
            sem_wait(&sfork[(id + 1) % 5]);
            sem_wait(&sfork[id]);
        }
        printf("%d号哲学家拿到两双筷子，开始吃饭了！\n", id);
        sleep(time);
        printf("%d号哲学家吃饭完成！放下筷子\n", id);
        sem_post(&sfork[id]);
        sem_post(&sfork[(id + 1) % 5]);
    }
    return NULL;
}
int main(void)
{
    pthread_t tid[5];

    for (int i = 0; i < 5; i++)
        sem_init(&sfork[i], 0, 1);

    int thread_id[5];
    for (int i = 0; i < 5; i++)
        thread_id[i] = i;

    for (int i = 0; i < 5; i++)
    {
        int *t = thread_id + i;
        pthread_create(&tid[i], NULL, philosopher, (void *)t);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(tid[i], NULL);
    }

    for (int i = 0; i < 5; i++)
        sem_destroy(&sfork[i]);

    return 0;
}