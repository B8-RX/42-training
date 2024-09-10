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
#include <stdio.h>

t_bits_8	g_bits = {128, 0, 0, -1, NULL};

unsigned char	*ft_append_char(unsigned char *str, int c)
{
	int				len;
	unsigned char	*res;
	int				i;

	i = 0;
	len = 0;
	if (str)
		len = ft_strlen((char *)str);
	res = malloc ((len + 2) * sizeof(unsigned char));
	if (!res)
		return (NULL);
	if (str)
	{
		while (i < len)
		{
			res[i] = str[i];
			i++;
		}
		free(str);
		str = NULL;
	}
	res[i] = (unsigned char)c;
	res[i + 1] = '\0';
	return (res);
}

void	display_line(t_bits_8 *g_bits)
{
	if (g_bits->start == 0)
		write (1, "Client send: ", 13);
	g_bits->start = 1;
	ft_putstr_fd((char *)g_bits->str, 1);
	free(g_bits->str);
	g_bits->str = NULL;
}

void	handle_sigint(int sig)
{
	size_t	len;

	if (sig == SIGUSR1)
		g_bits.total |= g_bits.curr;
	g_bits.curr >>= 1;
	if (g_bits.curr < 1)
	{
		g_bits.str = ft_append_char(g_bits.str, g_bits.total);
		len = ft_strlen((char *)g_bits.str);
		if (g_bits.total == '\n'
			|| g_bits.total == '\0'
			|| (len > 200 && (char)g_bits.str[len] == ' '))
			display_line(&g_bits);
		if (g_bits.total == 0)
		{
			write(1, "\n", 1);
			kill(g_bits.signal_pid, SIGUSR1);
			g_bits.signal_pid = -1;
			g_bits.start = 0;
		}
		g_bits.curr = 128;
		g_bits.total = 0;
	}
}

void	get_pid(int sig, siginfo_t *info, void *context)
{
	(void) context;
	if (g_bits.signal_pid == -1)
		g_bits.signal_pid = info->si_pid;
	handle_sigint(sig);
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
