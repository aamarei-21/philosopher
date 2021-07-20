/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 10:46:50 by aamarei           #+#    #+#             */
/*   Updated: 2021/07/20 13:20:20 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	pars_arg(int c, t_phil_data *phil, char **v)
{
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
	sem_unlink("print");
	phil->prin = sem_open("print", O_CREAT, 0600, 1);
	return (0);
}

void	ft_init_phil(t_philos **phil, t_phil_data *tm, sem_t *forks)
{
	int		i;

	i = 0;
	*phil = (t_philos *)malloc(sizeof(t_philos) * (tm->num_phil + 1));
	sem_unlink("forks");
	forks = sem_open("forks", O_CREAT, 0600, tm->num_phil);
	while (++i <= tm->num_phil)
	{
		(*phil)[i].num = i;
		(*phil)[i].time_died = 0;
		(*phil)[i].start_data = tm;
		(*phil)[i].forks = forks;
	}
}

int	main(int argc, char **argv)
{
	t_phil_data		*phil;
	t_philos		*philosoph;
	sem_t			*forks;
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
	forks = malloc(sizeof(sem_t) * phil->num_phil);
	ft_init_phil(&philosoph, phil, forks);
	ft_make_philoph(&philosoph, phil);
	sem_close(phil->prin);
	sem_close(philosoph->forks);
	sem_unlink("forks");
	free(forks);
	return (0);
}
