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

void	char_to_bin(char c, int *arr)
{
	int	i;
	int	j;

	i = 7;
	j = 0;
	while (i >= 0)
	{
		arr[j] = (c >> i) & 1;
		j++;
		i--;
	}
}

void	print_char_to_bin(int *arr)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		ft_printf("%d", arr[i]);
		i++;
	}
	ft_printf(" ");
}

void	free_bin_arr(int **arr, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("need 2 parameters\n");
		return (0);
	}
	char	*str;
	int		**arr_bin;
	int		i;
	int		len;

	str = argv[2];
	len = ft_strlen(str);
	i = 0;
	arr_bin = malloc (len * sizeof(int*));
	if (!arr_bin)
		return (0);
	while (i < len)
	{
		arr_bin[i] = malloc (8 * sizeof(int));
		if (!arr_bin[i])
		{
			while (i-- > 0)
				free(arr_bin[i]);
			free(arr_bin);
			return (0);
		}
		i++;
	}
	i = 0;
	while (*str)
	{
		char_to_bin(*str, arr_bin[i]);
		print_char_to_bin(arr_bin[i]);
		str++;
		i++;
	}
	ft_printf("\n");
	free_bin_arr(arr_bin, len);
}
