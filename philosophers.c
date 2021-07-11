#include <stdio.h> 
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NO_OF_PHILOSOPHERS 5

pthread_t philosophers[NO_OF_PHILOSOPHERS];
pthread_mutex_t mutex_forks[NO_OF_PHILOSOPHERS];
unsigned int count[NO_OF_PHILOSOPHERS];
int forks[NO_OF_PHILOSOPHERS];

void sig_handler(int signum){
    for(int j = 0 ; j < 5 ; ++j)
        printf("\n%d => %d", j, count[j]);
    exit(EXIT_SUCCESS);
}
void init(int * a)
{
    int i;
    for(i = 0; i<NO_OF_PHILOSOPHERS; i++){
        forks[i] = 0;
        pthread_mutex_init(&mutex_forks[i], NULL);
        count[i] = 0;
        a[i] = i;
    }
}
//wystarczy odkomentowac linijki z usleep i zostanie rozwiazany problem blokady.
void *philosopher(void* i)
{
    while(1){
    int left = (*(int*)i);
    int right = ((*(int*)i)+1)%5;
    int locked;
    locked = 0;
    while(!locked)
    {
        pthread_mutex_lock(&mutex_forks[*(int*)i]);
        if(forks[right] || forks[left])
        {
            pthread_mutex_unlock(&mutex_forks[*(int*)i]);
            printf("Filozof %d nie moze wziac widelcow. Zamiast tego mysli.\n",(*(int*)i)+1); 
            // usleep(rand() % 1000);
            continue;
        }
        forks[left] = 1;
        pthread_mutex_unlock(&mutex_forks[*(int*)i]);
        // usleep(rand() % 200); 
        pthread_mutex_lock(&mutex_forks[*(int*)i]);
        if(forks[right])
        {
            forks[left] = 0;
            pthread_mutex_unlock(&mutex_forks[*(int*)i]);
            printf("Filozof %d nie moze wziac drugiego widelca. Odklada go i zaczyna myslec.\n",(*(int*)i)+1); 
            // usleep(rand() % 1000);

            continue;
        }
        // usleep(rand() % 1000);
        forks[left] = 1;
        ++count[*(int*)i];
        pthread_mutex_unlock(&mutex_forks[*(int*)i]);
        locked = 1; 
    }

        printf("Filozof %d wzial oba widelce. Zaczyna jesc\n",(*(int*)i)+1);
        // usleep(rand() % 500);
        printf("Filozof %d skonczyl jesc. Odklada widelce.\n",(*(int*)i)+1);
        pthread_mutex_lock(&mutex_forks[*(int*)i]);
        forks[right] = 0;
        forks[left] = 0;
        pthread_mutex_unlock(&mutex_forks[*(int*)i]);
        // usleep(rand() % 1000);
    }
    pthread_exit(NULL);
}

int main()
{
    srand(time(NULL));
    signal(SIGINT, sig_handler);
    int a[NO_OF_PHILOSOPHERS];
    init(a);
    int i;

    for(i = 0; i < NO_OF_PHILOSOPHERS ; i++)
        pthread_create( &philosophers[i], NULL, &philosopher, &a[i]);

    for(i = 0 ; i < NO_OF_PHILOSOPHERS ; i++)
        pthread_join(philosophers[i],NULL);
    return 0;
}