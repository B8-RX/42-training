/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:00:15 by ssghioua          #+#    #+#             */
/*   Updated: 2024/08/27 01:00:17 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H

# define MINITALK_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include "ft_printf.h"

typedef struct s_bits_8
{
	int	curr;
	int	total;
	int	start;
	int	signal_pid;
}	t_bits_8;

void	get_pid(int sig, siginfo_t *info, void *context);
void	handle_sigint(int sig);
void	char_to_bin(char c, int processus);
void	send_ack(void);
int		ft_atoi(const char *str);


#endif // !MINITALK_H
