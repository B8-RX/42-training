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

void	char_to_bin(char c, int *arr, int processus)
{
	int	i;
	int	j;

	i = 7;
	j = 0;
	while (i >= 0)
	{
		arr[j] = (c >> i) & 1;
		ft_printf("%d", arr[j]);
		if (arr[j] == 1)
			kill(processus, SIGUSR1);
		else if (arr[j] == 0)
			kill(processus, SIGUSR2);
		j++;
		i--;
	}
	ft_printf(" ");
}

void	print_bin(int *arr)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		printf("%d", arr[i]);
		i++;
	}
	printf(" ");
}

void	free_bin_arr(int **arr, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}

int	**allocate_bin_arr(int len)
{
	int	**bin_arr;
	int	i;

	bin_arr = malloc (len * sizeof(int*));
	if (!bin_arr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		bin_arr[i] = malloc (8 * sizeof(int));
		if (!bin_arr[i])
		{
			while (i-- > 0)
				free(bin_arr[i]);
			free(bin_arr);
			return (NULL);
		}
		i++;
	}
	return (bin_arr);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 8 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (result == 0)
			result = str[i] - '0';
		else
			result = (result * 10 + str[i]) - '0';
		i++;
	}
	return (result * sign);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("need 2 parameters\n");
		return (0);
	}
	char		*str;
	int			**bin_arr;
	int			i;
	int			len;
	int			processus;

	str = argv[2];
	processus = ft_atoi(argv[1]);
	len = ft_strlen(str);
	bin_arr = allocate_bin_arr(len);
	if (!bin_arr)
		return (1);
	i = 0;
	while (*str)
	{
		char_to_bin(*str, bin_arr[i], processus);
		str++;
		i++;
	}
	printf("\n");
	free_bin_arr(bin_arr, len);
	return (0);
}
