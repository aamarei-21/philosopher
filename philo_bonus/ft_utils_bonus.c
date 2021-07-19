/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 13:02:20 by aamarei           #+#    #+#             */
/*   Updated: 2021/07/18 13:55:32 by aamarei          ###   ########.fr       */
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
	if (s[i] == '\0' && zn == 1)
		return (num);
	return (0);
}

int	ft_output_err(int code, char *str)
{
	int	len;

	len = 0;
	while (str && str[len] != '\0')
		len++;
	write(1, str, len);
	return (code);
}
