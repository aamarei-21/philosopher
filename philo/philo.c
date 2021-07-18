/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 10:46:50 by aamarei           #+#    #+#             */
/*   Updated: 2021/07/18 13:55:37 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pars_arg(int c, t_phil_data *phil, char **v)
{
	phil->fl = 1;
	phil->num_phil = ft_atoi(v[1]);
	phil->died = ft_atoi(v[2]);
	phil->eating = ft_atoi(v[3]);
	phil->sleeping = ft_atoi(v[4]);
	if (phil->num_phil == 0 || phil->died == 0 || phil->eating == 0
		|| phil->sleeping == 0)
		return (-1);
	if (c == 6)
	{
		phil->num_eat = atoi(v[5]);
		if (phil->num_eat <= 0)
			return (-1);
	}
	else if (c == 5)
		phil->num_eat = -1;
	else if (c > 6)
		return (-1);
	pthread_mutex_init(&phil->prin, NULL);
	return (0);
}

void	ft_init_phil(t_philos **phil, t_phil_data *tm, t_forks *forks)
{
	int		i;

	i = 0;
	*phil = (t_philos *)malloc(sizeof(t_philos) * (tm->num_phil + 1));
	while (++i <= tm->num_phil)
	{
		(*phil)[i].num = i;
		(*phil)[i].right = i;
		if (i == 1)
		{
			if (tm->num_phil == 1)
				(*phil)[i].left = i;
			else
				(*phil)[i].left = tm->num_phil;
		}
		else
			(*phil)[i].left = i - 1;
		(*phil)[i].time_died = 0;
		(*phil)[i].start_data = tm;
		(*phil)[i].forks = forks;
	}
}

int	ft_init_mutex(t_forks *forks, t_phil_data *tm)
{
	int	i;
	int	er;

	i = 0;
	while (++i <= tm->num_phil)
	{
		er = pthread_mutex_init(&forks[i].fork, NULL);
		if (er != 0)
			return (-1);
	}
	return (0);
}

void	ft_destroy_mutex(t_forks *forks, t_phil_data *tm)
{
	int	i;

	i = 0;
	while (++i <= tm->num_phil)
		pthread_mutex_destroy(&forks[i].fork);
}

int	main(int argc, char **argv)
{
	t_phil_data		*phil;
	t_philos		*philosoph;
	t_forks			*forks;
	int				fl;

	phil = malloc(sizeof(t_phil_data));
	if (argc >= 5)
	{
		fl = pars_arg(argc, phil, argv);
		if (fl < 0)
			return (ft_output_err(1, "Incorrect data\n"));
	}
	else
		return (ft_output_err(1, "Incorrect data\n"));
	philosoph = NULL;
	forks = (t_forks *)malloc(sizeof(t_forks) * (phil->num_phil + 1));
	ft_init_phil(&philosoph, phil, forks);
	if (ft_init_mutex(forks, phil) == -1)
		return (ft_output_err(1, "Fatal error\n"));
	ft_create_philoph(&philosoph, phil);
	ft_destroy_mutex(forks, phil);
	pthread_mutex_destroy(&(*phil).prin);
	return (0);
}
