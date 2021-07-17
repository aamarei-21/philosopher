/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 10:19:37 by aamarei           #+#    #+#             */
/*   Updated: 2021/07/17 11:53:53 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct		s_forks
{
	pthread_mutex_t	fork;
}					t_forks;

typedef struct			s_phil_data
{
	int					fl;
	int					num_phil;
	unsigned long long	died;
	unsigned long long	eating;
	unsigned long long	sleeping;
	int					num_eat;
	pthread_mutex_t		*prin;
}						t_phil_data;

typedef struct		s_philos
{
	unsigned int	num;
	pthread_t		th;
	t_forks			*forks;
	unsigned int	left;
	unsigned int	right;
	unsigned int	time_died;
	t_phil_data		*start_data;
}					t_philos;

//typedef struct		s_philosophers
//{
//	t_philos		*philosoph;
//	t_forks			*forks;
//}					t_philosophers;


//typedef struct			s_pfilosopher
//{
//	int					num;
//	t_forks
//	pthread_t			th;
//	pthread_mutex_t		fork;
//	t_forks				*forks;
//	unsigned long long	time_died;
//	t_phil_data			timest;
//}						t_philosopher;

void	*main_thread(void *phil);
int		ft_create_philoph(t_philos **phil, t_phil_data *tm);
void	informer(t_philos **phil, int k, unsigned long long time);
void	ft_wait(unsigned long long tm);

#endif
