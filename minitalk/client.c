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

void	printBinary(char c)
{
	int i;

	i = 7;
	while (i >= 0)
	{
		ft_printf("%d", c >> i & 1);
		i--;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		ft_printf("1er argument: %s\n", argv[1]);
		ft_printf("2eme argument: %s\n", argv[2]);
		char	*str = argv[2];

		while (*str)
		{
			printBinary(*str);
			if (*(++str) != '\0') 
				ft_printf(" ");
		}
	}
	if (argc < 3)
		ft_printf("client take 2 parameters");
	return (0);
}
