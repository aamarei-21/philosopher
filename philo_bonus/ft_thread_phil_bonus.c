/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_phil_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 18:57:34 by aamarei           #+#    #+#             */
/*   Updated: 2021/07/20 13:20:51 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_died(void *dt)
{
	t_philos	*phil;

	phil = (t_philos *)dt;
	while (1)
	{
		if (ft_relative_time() > phil->time_died)
		{
			informer(phil, 6, ft_relative_time(), 0);
			exit (1);
		}
		usleep(10);
	}
	return (0);
}

void	ft_thread_cicle(t_philos *phil, pthread_t	th)
{
	unsigned long long	i;
	unsigned long long	time;

	i = 0;
	while (i++ != phil->start_data->num_eat)
	{
		sem_wait(phil->forks);
		time = ft_relative_time();
		informer(phil, 1, time, 1);
		sem_wait(phil->forks);
		time = ft_relative_time();
		informer(phil, 2, time, 1);
		time = ft_relative_time();
		informer(phil, 3, time, 1);
		phil->time_died = time + phil->start_data->died;
		ft_wait(phil->start_data->eating);
		sem_post(phil->forks);
		sem_post(phil->forks);
		time = ft_relative_time();
		informer(phil, 4, time, 1);
		ft_wait(phil->start_data->sleeping);
		time = ft_relative_time();
		informer(phil, 5, time, 1);
	}
	exit(0);
}

void	main_thread(t_philos phil, unsigned long long time)
{
	pthread_t			th;

	phil.time_died = time + phil.start_data->died;
	pthread_create(&th, NULL, monitor_died, (void *)(&phil));
	pthread_detach(th);
	if ((phil.num & 1) == 0)
		ft_wait(10);
	ft_thread_cicle(&phil, th);
}

int	ft_make_philoph(t_philos **phil, t_phil_data *tm)
{
	int					i;
	pid_t				*pid;
	int					status;
	unsigned long long	time;

	i = 0;
	pid = (pid_t *)malloc(sizeof(pid_t) * (tm->num_phil + 1));
	time = ft_relative_time();
	while (++i <= tm->num_phil)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			main_thread((*phil)[i], time);
	}
	waitpid(0, &status, 0);
	status = WEXITSTATUS(status);
	i = 0;
	if (status != 0)
		while (++i <= tm->num_phil)
			kill(pid[i], SIGKILL);
	else
		while (++i < tm->num_phil)
			waitpid(0, &status, 0);
	free(pid);
	return (0);
}
