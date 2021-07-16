/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 10:19:37 by aamarei           #+#    #+#             */
/*   Updated: 2021/07/16 11:07:49 by aamarei          ###   ########.fr       */
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
	int					num_phil;
	unsigned long long	died;
	unsigned long long	eating;
	unsigned long long	sleeping;
	int					num_eat;
}						t_phil_data;

typedef struct			s_pfilosopher
{
	int					num;
	pthread_t			th;
	pthread_mutex_t		fork;
	t_forks				*forks;
	unsigned long long	time_died;
	t_phil_data			timest;
}						t_philosopher;

void	*main_thread(void *phil);
int	ft_create_philoph(t_philosopher **phil, t_phil_data *tm);

#endif
