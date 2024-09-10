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

void	handle_ack(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("Message Received!.\n");
	else if (sig == SIGUSR2)
		ft_printf("Message Not Received!.\n");
	exit(0);
}

int	is_digit(char *str)
{
	int	i;
	int	is_digit;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
		{
			is_digit = 1;
			i++;
		}
		else
		{
			is_digit = 0;
			break ;
		}
	}
	return (is_digit);
}

void	send_message(unsigned char *str, int pid)
{
	int	len;

	len = 0;
	while (*str && ++len)
	{
		if (len >= 200 && (char)*str == ' ')
		{
			char_to_bin((unsigned char) '\n', pid);
			len = 0;
		}
		else
			char_to_bin(*str++, pid);
	}
	char_to_bin('\0', pid);
}

int	main(int argc, char **argv)
{
	unsigned char		*str;
	int					processus;
	struct sigaction	sa;

	if (argc != 3)
		return (ft_printf("INVALID FORMAT: [exec] [PID] [MESSAGE]\n", 1));
	if (!is_digit(argv[1]))
		return (ft_printf("INVALID [PID]\n"), 1);
	str = (unsigned char *) argv[2];
	processus = ft_atoi(argv[1]);
	if (processus < 0 || processus > PID_MAX || kill(processus, 0) == -1)
		return (ft_printf("INVALID [PID]\n"), 1);
	sa.sa_handler = &handle_ack;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	send_message(str, processus);
	while (1)
		pause();
	return (0);
}
