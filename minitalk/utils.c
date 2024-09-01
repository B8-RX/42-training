/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 10:11:22 by ssghioua          #+#    #+#             */
/*   Updated: 2024/09/01 10:11:25 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./minitalk.h"

t_bits_8	bits = {128, 0};	

void	handle_sigint(int sig)
{ 
	if (sig == SIGUSR1)
		bits.total += bits.curr;
	bits.curr /= 2;
	if (bits.curr < 1)
	{
		write(1, &bits.total, 1);
		bits.curr = 128;
		bits.total = 0;
	}
}

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
		usleep(100);
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
