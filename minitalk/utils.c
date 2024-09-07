/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 08:06:30 by ssghioua          #+#    #+#             */
/*   Updated: 2024/09/02 08:06:33 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minitalk.h"

void	char_to_bin(char c, int processus)
{
	int		i;
	int		j;

	i = 7;
	j = 0;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			kill(processus, SIGUSR1);
		else
			kill(processus, SIGUSR2);
		usleep(500);
		j++;
		i--;
	}
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 8 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (result == 0)
			result = str[i] - '0';
		else
			result = (result * 10 + str[i]) - '0';
		i++;
	}
	return (result * sign);
}
