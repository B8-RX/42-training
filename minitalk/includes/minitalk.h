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
# define PID_MAX 4194304

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include "libft.h"

typedef struct s_bits_8
{
	int				curr;
	unsigned char	total;
	int				start;
	int				signal_pid;
	unsigned char	*str;
}	t_bits_8;

void	char_to_bin(unsigned char c, int processus);
void	send_message(unsigned char *str, int pid);

#endif // !MINITALK_H
