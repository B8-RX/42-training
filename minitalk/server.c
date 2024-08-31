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

# include "minitalk.h"

int	get_pow(int nb, int pow)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (i++ <= nb)
	{
		if (res == 0)
			res = 1;
		else
			res *= pow;
	}
	return (res);
}

void	bits_to_char(int arr[8])
{
	int	j;
	int	sum;

	j = 0;
	sum = 0;
	while(j <= 7)
	{
		if (arr[j] == 1)
			sum += get_pow((7 - j), 2); 
		j++;
	}
	printf("ASCII %d\n", sum);
}

void	handle_sigint(int sig)
{
	ft_printf("Handle signal: \n");
	if (sig == SIGUSR1)
		ft_printf("SIGUSR1 1");
	if (sig == SIGUSR2)
		ft_printf("SIGUSR2 0");
	ft_printf("\n");
}

int	main(void)
{
	int	pid;
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &handle_sigint;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;

	// CHECK IF sigaction == -1 
	pid = getpid();
	while (1)
	{
		if (sigaction(SIGUSR1, &sa, NULL) == -1)
			return (1);
		if (sigaction(SIGUSR2, &sa, NULL) == -1)
			return (1);
		ft_printf("Server is Running...\n");
		ft_printf("PID = %d\n", pid);
		pause();
	}
	return (0);
}
