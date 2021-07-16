/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 10:46:50 by aamarei           #+#    #+#             */
/*   Updated: 2021/07/16 10:36:58 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *s)
{
	int		i;
	int		zn;
	int		num;

	i = -1;
	zn = 1;
	num = 1;
	while(num != 0 && s[++i] != '\0')
	{
		if (s[i] == '-')
			zn = -1 * zn;
		else if (s[i] >= 48 && s[i] <= 57)
			num = 0;
		else if (!(s[i] == ' ' || s[i] == '\t' || s[i] == '\v' || s[i] == '+'
				|| s[i] == '\r' || s[i] == '\f'))
			return (0);
	}
	while ((s[i] >= 48 && s[i] <= 57) && s[i] != '\0')
	{
		num = 10 * num + s[i] - 48;
		i++;
	}
	if (s[i] == '\0')
		return (zn * num);
	return (0);

}

int	ft_digit(char *d)
{
	int		num;

	num = ft_atoi(d);
	if (num < 0)
		num = 0;
	return (num);
}

int	pars_arg(int c, t_phil_data *phil, char **v)
{
	phil->num_phil = ft_digit(v[1]);
	phil->died = ft_digit(v[2]);
	phil->eating = ft_digit(v[3]);
	phil->sleeping = ft_digit(v[4]);
	if (phil->num_phil == 0 || phil->died == 0 || phil->eating == 0
		|| phil->sleeping == 0)
		return (-1);
	if (c == 6)
	{
		phil->num_eat = ft_digit(v[5]);
		if (phil->num_eat <= 0)
			return (-1);
	}
	else if (c == 5)
		phil->num_eat = 0;
	else if (c > 6)
		return (-1);
	return (0);
}

void	ft_init_phil(t_philosopher **phil, t_phil_data *tm)
{
	int		i;

	i = -1;
	*phil = (t_philosopher *)malloc(sizeof(t_philosopher) * tm->num_phil);
	while (++i < tm->num_phil)
	{

		(*phil)[i].num = i;
		(*phil)[i].forks = malloc(sizeof(t_forks));
		(*phil)[i].forks->right = &phil[i]->fork;
		if (i == 0)
		{
			if (tm->num_phil == 1)
				(*phil)[i].forks->left = &phil[i]->fork;
			else
				(*phil)[i].forks->left = &phil[tm->num_phil - 1]->fork;
		}
		else
			(*phil)[i].forks->left = &phil[i - 1]->fork;
		(*phil)[i].time_died = 0;
	}
}

int	ft_init_mutex(t_philosopher *phil, t_phil_data *tm)
{
	int	i;
	int	er;

	i = 0;
	while (i < tm->num_phil)
	{
printf("++++ philosopher = %d\n", phil[i].num);
		er = pthread_mutex_init(&phil[i].fork, NULL);
		if (er != 0)
			return (-1);
		i++;
	}
	return (0);
}


int	main(int argc, char **argv)
{
	t_phil_data		*phil;
	t_philosopher	*philosoph;
	int				fl;

	phil = malloc(sizeof(t_phil_data));

	if (argc >= 5)
	{
		fl = pars_arg(argc, phil, argv);
		if (fl < 0)
		{
			write(2, "Incorrect data\n", 15);
			return (1);
		}
		printf("number philosopher = %d\n", phil->num_phil);
		//printf("time died = %llu\n", phil->died);
		//printf("time eating = %llu\n", phil->eating);
		//printf("time sleeping = %llu\n", phil->sleeping);
		//printf("number eating = %d\n", phil->num_eat);
	}
	else
	{
		write(2, "Incorrect data\n", 15);
		return (1);
	}
	philosoph = NULL;
	ft_init_phil(&philosoph, phil);
	if (ft_init_mutex(philosoph, phil) == -1)
		return (1); //!Вывысти ошибку
	ft_create_philoph(&philosoph, phil);


	return (0);
}
