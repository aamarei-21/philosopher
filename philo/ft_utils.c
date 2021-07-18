/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 13:02:20 by aamarei           #+#    #+#             */
/*   Updated: 2021/07/17 16:42:16 by aamarei          ###   ########.fr       */
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
	while (num != 0 && s[++i] != '\0')
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

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
		i++;
	return (i);
}

int	ft_output_err(int code, char *str)
{
	write(2, str, ft_strlen(str));
	return (code);
}

int	ft_even(int c)
{
	if (c % 2 == 0)
		return (1);
	else
		return (0);
}
