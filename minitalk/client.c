/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:45:47 by ssghioua          #+#    #+#             */
/*   Updated: 2024/08/27 00:45:48 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_bits_8	g_bits = {128, 0, 0, -1};

void	handle_ack(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("Message Received!.\n");
	else if (sig == SIGUSR2)
		ft_printf("Message Not Received!.\n");
	exit(0);
}

int	main(int argc, char **argv)
{
	char				*str;
	int					processus;
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_printf("valid format: [exec] [PID] [MESSAGE]\n");
		return (1);
	}
	str = argv[2];
	processus = ft_atoi(argv[1]);
	if ((processus < 0 || processus > PID_MAX))
		return (ft_printf("INVALID [PID]\n"), 1);
	sa.sa_handler = &handle_ack;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	while (*str)
		char_to_bin(*str++, processus);
	char_to_bin('\0', processus);
	while (1)
		pause();
	return (0);
}
