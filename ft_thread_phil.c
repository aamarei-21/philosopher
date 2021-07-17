/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_phil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 18:57:34 by aamarei           #+#    #+#             */
/*   Updated: 2021/07/17 11:49:25 by aamarei          ###   ########.fr       */
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
	return (ft_gettime() - start);
}

void	ft_wait(unsigned long long tm)
{
	unsigned long long	finish;

	finish = ft_relative_time() + tm;
	while (ft_relative_time() < finish)
		usleep(1);

}

void informer(t_philos **phil, int k, unsigned long long time)
{
	pthread_mutex_lock((*phil)->start_data->prin);
	if (k == 1)
		printf("%llu ms: %d has taken a right fork\n", time, (*phil)->num);
	else if (k == 2)
		printf("%llu ms: %d has taken a left fork\n", time, (*phil)->num);
	else if (k == 3)
		printf("%llu ms: %d is eating\n", time, (*phil)->num);
	else if (k == 4)
		printf("%llu ms: %d is sleeping\n", time, (*phil)->num);
	else if (k == 5)
		printf("%llu ms: %d is thinking\n", time, (*phil)->num);
	else if (k == 6)
		printf("%llu ms: %d died\n", time, (*phil)->num);
}


void	*monitor_died(void *dt)
{
	t_philos	*phil;

	phil = (t_philos *)dt;
	while (1)
	{
		if (ft_relative_time() > phil->time_died)
		{
			phil->start_data->fl = 0;
			informer(&phil, 6, ft_relative_time());
			return (0);
		}
		ft_wait(1);
	}
	return (0);
}


void	*main_thread(void *ph)
{
	t_philos *phil;
	unsigned long long	time;
	pthread_t		th;
	unsigned long long i;

	i = 0;
	phil = (t_philos *)ph;
	pthread_detach(phil->th);
	time = ft_relative_time();
	phil->time_died = time + phil->start_data->died;
	pthread_create(&th, NULL, monitor_died, (void *)(phil));
	pthread_detach(th);
	if (!ft_even(phil->num))
		ft_wait(1);
	while (i++ != phil->start_data->num_eat)
	{
		pthread_mutex_lock(&phil->forks[phil->right].fork);
		time = ft_relative_time();
		informer(&phil, 1, time);
		pthread_mutex_unlock(phil->start_data->prin);
		pthread_mutex_lock(&phil->forks[phil->left].fork);
		time = ft_relative_time();
		informer(&phil, 2, time);
		pthread_mutex_unlock(phil->start_data->prin);

		time = ft_relative_time();
		informer(&phil, 3, time);
		pthread_mutex_unlock(phil->start_data->prin);
		phil->time_died = time + phil->start_data->died;
		ft_wait(phil->start_data->eating);


		pthread_mutex_unlock(&phil->forks[phil->right].fork);
		pthread_mutex_unlock(&phil->forks[phil->left].fork);
		time = ft_relative_time();
		informer(&phil, 4, time);
		pthread_mutex_unlock(phil->start_data->prin);
		ft_wait(phil->start_data->sleeping);
		time = ft_relative_time();
		informer(&phil, 5, time);
		pthread_mutex_unlock(phil->start_data->prin);
	}
	phil->start_data->fl = 2;
	return (0);
}

int	ft_create_philoph(t_philos **phil, t_phil_data *tm)
{
	int				i;

	i = 0;
	while (++i <= tm->num_phil)
		pthread_create(&(*phil)[i].th, NULL, main_thread, (void *)(&(*phil)[i]));
	while (tm->fl != 2)
	{
		if (tm->fl == 0)
			return (0);
	}
	i = 0;
	while (++i <= tm->num_phil)
		pthread_join((*phil)[i].th, NULL);
	return (0);
}

