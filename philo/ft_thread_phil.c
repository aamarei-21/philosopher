/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_phil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 18:57:34 by aamarei           #+#    #+#             */
/*   Updated: 2021/07/18 14:11:44 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_died(void *dt)
{
	t_philos	*phil;

	phil = (t_philos *)dt;
	while (1)
	{
		if (ft_relative_time() > phil->time_died)
		{
			phil->start_data->fl = 0;
			informer(&phil, 6, ft_relative_time(), 0);
			return (0);
		}
		ft_wait(1);
	}
	return (0);
}

void	ft_thread_cicle(t_philos **phil, pthread_t	th)
{
	unsigned long long	i;
	unsigned long long	time;

	i = 0;
	while (i++ != (*phil)->start_data->num_eat)
	{
		pthread_mutex_lock(&(*phil)->forks[(*phil)->right].fork);
		time = ft_relative_time();
		informer(&(*phil), 1, time, 1);
		pthread_mutex_lock(&(*phil)->forks[(*phil)->left].fork);
		time = ft_relative_time();
		informer(&(*phil), 2, time, 1);
		time = ft_relative_time();
		informer(&(*phil), 3, time, 1);
		(*phil)->time_died = time + (*phil)->start_data->died;
		ft_wait((*phil)->start_data->eating);
		pthread_mutex_unlock(&(*phil)->forks[(*phil)->right].fork);
		pthread_mutex_unlock(&(*phil)->forks[(*phil)->left].fork);
		time = ft_relative_time();
		informer(&(*phil), 4, time, 1);
		ft_wait((*phil)->start_data->sleeping);
		time = ft_relative_time();
		informer(&(*phil), 5, time, 1);
	}
}

void	*main_thread(void *ph)
{
	t_philos			*phil;
	unsigned long long	time;
	pthread_t			th;

	phil = (t_philos *)ph;
	pthread_detach(phil->th);
	time = ft_relative_time();
	phil->time_died = time + phil->start_data->died;
	pthread_create(&th, NULL, monitor_died, (void *)(phil));
	pthread_detach(th);
	if ((phil->num & 1) == 0)
		ft_wait(10);
	ft_thread_cicle(&phil, th);
	phil->start_data->fl = 2;
	return (0);
}

int	ft_create_philoph(t_philos **phil, t_phil_data *tm)
{
	int				i;

	i = 0;
	while (++i <= tm->num_phil)
		pthread_create(&(*phil)[i].th, NULL, main_thread,
			(void *)(&(*phil)[i]));
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
