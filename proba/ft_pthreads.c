#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct	s_def
{
	int				x;
	pthread_mutex_t	mutex;
}				t_def;

void	*routine(void *k)
{
	t_def	*pr;
	int		i;

	pr = (t_def *) k;
	i = 0;
	printf("%d\n", pr->x);
	while (i++ < 15000000)
	{
		pthread_mutex_lock(&(pr->mutex));

		pr->x++;
		pthread_mutex_unlock(&(pr->mutex));

	}
	usleep (10);
	printf("%d\n", pr->x);
	return(0);
}

int	main(int argc, char **argv)
{
	struct timeval time0, time1;
	size_t		tm, tm1;
	pthread_t	*th;
	t_def		per;
	int			i;
	int			k;

	k = 6;
	th = (pthread_t *)malloc(sizeof(pthread_t) * k);
	per.x = 0;
	i = 0;
	pthread_mutex_init(&per.mutex, NULL);
	printf(" x = %d\n", per.x);
	gettimeofday(&time0, NULL);
	printf("time = %d\n", time0.tv_usec);
	gettimeofday(&time1, NULL);
	tm = (time1.tv_sec - time0.tv_sec) * 1000.0f + (time1.tv_usec - time0.tv_usec) / 1000.0f;
	printf("D time = %zd\n", (size_t)tm);
	while (i++ < k)
	{
		pthread_create(&th[i], NULL, routine, (void *)(&per));
		printf("Start thread - %d\n", i);
	}
	i = 0;
	while (i++ < k)
	{
		pthread_join(th[i], NULL);
		printf("Finished thread - %d\n", i);

	}
	pthread_mutex_destroy(&per.mutex);
	printf(" x = %d\n", per.x);
	gettimeofday(&time1, NULL);
	tm1 = (time1.tv_sec - time0.tv_sec) * 1000.0f + (time1.tv_usec - time0.tv_usec) / 1000.0f;
	printf("time = %d\n", time1.tv_usec);
	printf("D time = %zd\n", tm1);
	free(th);
	return (0);
}
