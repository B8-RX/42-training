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

void	handle_sigint(int sig)
{
	printf("Caught signal %d\n", sig);
	

}

int	main(void)
{
	int	pid;
	struct sigaction sa;

	sa.sa_handler = handle_sigint;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGINT, &sa, NULL);
	// CHECK IF sigaction == -1 
	pid = getpid();

	while (1)
	{
		ft_printf("Running...\n");
		ft_printf("PID = %d\n", pid);
		pause();
	}

	return (0);
}
