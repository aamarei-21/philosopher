/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 10:19:37 by aamarei           #+#    #+#             */
/*   Updated: 2021/07/18 19:44:04 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

//typedef struct s_forks
//{
//	pthread_mutex_t	fork;
//}					t_forks;

typedef struct s_phil_data
{
	int					fl;
	int					num_phil;
	unsigned long long	died;
	unsigned long long	eating;
	unsigned long long	sleeping;
	int					num_eat;
	sem_t				*prin;
}						t_phil_data;

typedef struct s_philos
{
	unsigned int	num;
	//pthread_t		th;
	sem_t			forks;
	//t_forks			*forks;
	//unsigned int	left;
	//unsigned int	right;
	unsigned int	time_died;
	t_phil_data		*start_data;
}					t_philos;

void				*main_thread(void *phil);
int					ft_create_philoph(t_philos **phil, t_phil_data *tm);
unsigned long long	ft_gettime(void);
unsigned long long	ft_relative_time(void);
void				ft_wait(unsigned long long tm);
void				informer(t_philos **phil, int k,
						unsigned long long time, int fl);
void				ft_wait(unsigned long long tm);
int					ft_atoi(char *s);
int					ft_output_err(int code, char *str);
int					pars_arg(int c, t_phil_data *phil, char **v);

#endif
