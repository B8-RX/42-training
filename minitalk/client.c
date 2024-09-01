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

# include "minitalk.h"

int	main(int argc, char **argv)
{
	char	*str;
	int		len;
	int		processus;
	
	if (argc != 3)
	{
		ft_printf("valid format: [exec] [PID] [MESSAGE]\n");
		return (1);
	}
	str = argv[2];
	processus = ft_atoi(argv[1]);
	if (processus == -1)
		return (1);
	len = ft_strlen(str);
	while (*str)
	{
		char_to_bin(*str, processus);
		str++;
	}
	char_to_bin('\n', processus);
	return (0);
}
