/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 03:53:25 by ssghioua          #+#    #+#             */
/*   Updated: 2024/11/23 03:53:27 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

long long	ft_atoll(char *num)
{
	long long	sum;

	sum = 0;
	while (*num && (*num >= 48 && *num <= 57))
	{
		sum = sum * 10 + (*num - '0');
		num++;
	}
	return (sum);
}

bool	is_digits(char *arg)
{
	while (arg && *arg)
	{
		if (*arg < 48 || *arg > 57)
			return (false);
		arg++;
	}
	return (true);
}

int	ft_atoi(char *num)
{
	int	sum;
	int	sign;

	sign = 1;
	sum = 0;
	if (*num == '-' || *num == '+')
	{
		if (*num == '-')
			sign = -1;
		num++;
	}
	while (*num && (*num >= 48 && *num <= 57))
	{
		sum = sum * 10 + (*num - '0');
		num++;
	}
	return (sum * sign);
}

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
