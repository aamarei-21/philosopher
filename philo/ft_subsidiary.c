/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subsidiary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 14:46:27 by aamarei           #+#    #+#             */
/*   Updated: 2021/07/19 18:42:15 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	ft_relative_time(void)
{
	static int					fl = 0;
	static unsigned long long	start;
	unsigned long long			finish;
	struct timeval				time;

	gettimeofday(&time, NULL);
	finish = (unsigned long long)time.tv_sec * 1000
		+ (unsigned long long)time.tv_usec / 1000;
	if (fl == 0)
	{
		start = finish;
		fl = 1;
	}
	return (finish - start);
}

void	ft_wait(unsigned long long tm)
{
	unsigned long long	finish;

	finish = ft_relative_time() + tm;
	while (ft_relative_time() < finish)
		usleep(500);
}

void	informer(t_philos **phil, int k, unsigned long long time, int fl)
{
	pthread_mutex_lock(&(*phil)->start_data->prin);
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
	if (fl)
		pthread_mutex_unlock(&(*phil)->start_data->prin);
}
