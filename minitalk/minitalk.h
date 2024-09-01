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

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include "ft_printf.h"

typedef struct s_bits_8 {
	int curr;
	int	total;
}	t_bits_8;

void	handle_sigint(int sig);
void	char_to_bin(char c, int processus);
int		ft_atoi(const char *str);
