/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_phil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 18:57:34 by aamarei           #+#    #+#             */
/*   Updated: 2021/07/16 10:27:33 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_even(int c)
{
	if (c == 2 * (c / 2))
		return (1);
	else
		return (0);
}

unsigned long long	ft_gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((unsigned long long)time.tv_sec * 1000
		+ (unsigned long long)time.tv_usec / 1000);
}

unsigned long long	ft_relative_time(void)
{
	static int					fl = 0;
	static unsigned long long	start;
	unsigned long long			finish;

	if (fl == 0)
	{
		start = ft_gettime();
		fl = 1;
	}
	finish = ft_gettime() - start;
	return (finish);
}

void	*main_thread(void *ph)
{
	t_philosopher *phil;

	phil = (t_philosopher *)ph;

//printf("number philosopher = %d\n", phil->timest.num_phil);
//printf("time died = %llu\n", phil->timest.died);
//printf("time eating = %llu\n", phil->timest.eating);
//printf("time sleeping = %llu\n", phil->timest.sleeping);
//printf("number eating = %d\n", phil->timest.num_phil);


	if (phil->num == phil->timest.num_phil && !ft_even(phil->num))
		usleep(1000);
printf("phil->num = %d : %d\n", phil->num, ft_even(phil->num));
	if (ft_even(phil->num))
	{
		pthread_mutex_lock(phil->forks->right);
		printf("timestamp_in_ms %d has taken a fork\n", phil->num);
		pthread_mutex_lock(phil->forks->left);
		printf("timestamp_in_ms %d has taken a fork\n", phil->num);

	}
	else
	{
		pthread_mutex_lock(phil->forks->left);
		printf("timestamp_in_ms %d has taken a fork\n", phil->num);
		pthread_mutex_lock(phil->forks->right);
		printf("timestamp_in_ms %d has taken a fork\n", phil->num);
	}

		printf("timestamp_in_ms %d is eating\n", phil->num);
		usleep(phil->timest.eating * 1000);

	//if (ft_even(phil->num))
	//{
		pthread_mutex_unlock(phil->forks->right);
		pthread_mutex_unlock(phil->forks->left);
	//}
	//else
	//{
	//	pthread_mutex_unlock(phil->forks->left);
	//	pthread_mutex_unlock(phil->forks->right);
	//}
	return (0);
}

int	ft_create_philoph(t_philosopher **phil, t_phil_data *tm)
{
	int				i;
	//pthread_t		temp;

	i = -1;
	while (++i < tm->num_phil)
	{
	printf("i = %d\n", i);
		//temp = (*phil)[i].th;
		pthread_create(&(*phil)[i].th, NULL, main_thread, (void *)(&(*phil)[i]));
		printf("Start thread - %d\n", i);
	}

	i = -1;
	//while (++i < tm->num_phil)
	//{
	//	pthread_join((*phil)[i].th, NULL);
	//	printf("Finished thread - %d\n", i);
	//}
	return (0);
}

//int	main(void)
//{
//	ft_relative_time();
//	printf ("%llu\n", ft_relative_time());
//	usleep(500000);
//	printf ("%llu\n", ft_relative_time());
//	usleep(500000);
//	printf ("%llu\n", ft_relative_time());
//	usleep(50000);
//	printf ("%llu\n", ft_relative_time());
//	usleep(15555555);
//	printf ("%llu\n", ft_relative_time());
//	return (0);
//}
