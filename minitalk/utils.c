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

t_bits_8	g_bits = {128, 0, 0, -1};

void	get_pid(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (g_bits.signal_pid == -1)
		g_bits.signal_pid = info->si_pid;
	handle_sigint(sig);
}

void	handle_sigint(int sig)
{
	if (g_bits.start == 0)
	{
		g_bits.start = 1;
		write(1, "Client send: ", 13);
	}
	if (sig == SIGUSR1)
		g_bits.total += g_bits.curr;
	g_bits.curr /= 2;
	if (g_bits.curr < 1)
	{
		if (g_bits.total == 0)
		{
			write(1, "\n", 1);
			kill(g_bits.signal_pid, SIGUSR1);
			g_bits.signal_pid = -1;
			g_bits.start = 0;
		}
		else
			write(1, &g_bits.total, 1);
		g_bits.curr = 128;
		g_bits.total = 0;
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
		usleep(500);
		j++;
		i--;
	}
}

void	send_ack(void)
{
	char	*ack_message = "Message received!\n";

	while (*ack_message)
	{
		char_to_bin(*ack_message, g_bits.signal_pid);
		ack_message++;
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
