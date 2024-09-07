/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:45:39 by ssghioua          #+#    #+#             */
/*   Updated: 2024/08/27 00:45:41 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
		g_bits.total |= g_bits.curr;
	g_bits.curr >>= 1;
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

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = &get_pid;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	ft_printf("PID = %d\n", getpid());
	while (1)
		pause();
	return (0);
}
