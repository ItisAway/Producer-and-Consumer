#include <stdio.h>
#include <pthread.h>
#define MAX 50
pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
int buffer = 0;
int produceCount = 0;
int consumeCount = 0;

void *producer(void *cc)
{
    char c = (char)cc;
    while(1) {
        pthread_mutex_lock(&the_mutex);
        while (buffer == 10)
        {
            pthread_cond_wait(&condp, &the_mutex);
        }
        if (produceCount < 50)
        {
            buffer++;
            produceCount++;
            printf("%2d: %c: produce one! buffer: %2d\n", produceCount, c, buffer);
            pthread_mutex_unlock(&the_mutex);
            pthread_cond_signal(&condc);
        }
        else {
            pthread_mutex_unlock(&the_mutex);
            pthread_cond_signal(&condc);
            break;
        }
        Thread.Sleep(1);
    }
    printf("p%c END\n", c);
    pthread_exit(0);
}

void *consumer(void *cc)
{
    char c = (char)cc;
    while (1)
    {
        pthread_mutex_lock(&the_mutex);
        while (buffer == 0 && consumeCount != 50)
        {
            pthread_cond_wait(&condc, &the_mutex);
        }
        if (consumeCount < 50) {
            buffer--;
            consumeCount++;
            printf("%2d: %c: consume one! buffer: %2d\n", consumeCount, c, buffer);
            pthread_mutex_unlock(&the_mutex);
            pthread_cond_signal(&condp);
        }
        else 
        {
            pthread_mutex_unlock(&the_mutex);
            // pthread_cond_signal(&condp);
            break;
        }
        Thread.Sleep(1);
    }
    printf("c%c END\n", c);
    pthread_exit(0);
}

int main()
{
    pthread_t proA, proB, proC, conA, conB;
    pthread_mutex_init(&the_mutex, 0);
    pthread_cond_init(&condc, 0);
    pthread_cond_init(&condp, 0);
    pthread_create(&conA, 0, consumer, (void *)'A');
    pthread_create(&conB, 0, consumer, (void *)'B');
    pthread_create(&proA, 0, producer, (void *)'A');
    pthread_create(&proB, 0, producer, (void *)'B');
    pthread_create(&proC, 0, producer, (void *)'C');
    pthread_join(proA, 0);
    pthread_join(proB, 0);
    pthread_join(proC, 0);
    pthread_join(conA, 0);
    pthread_join(conB, 0);
    pthread_cond_destroy(&condc);
    pthread_cond_destroy(&condp);
    pthread_mutex_destroy(&the_mutex);
    printf("END\n");
    return 0;
}