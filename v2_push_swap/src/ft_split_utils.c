/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:37:26 by ssghioua          #+#    #+#             */
/*   Updated: 2024/04/27 18:37:27 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/push_swap.h"

int	count_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

int	ft_is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long int	ft_atol(const char *str)
{
	long	res;
	int		parity;

	parity = 1;
	res = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r' || *str == '\f' || *str == '\v')
		str++;

	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			parity = -1;
		str++;
	}

	while (ft_is_digit(*str))
		res = res * 10 + (*str++ - '0');
	return (res * parity); 
}

int	get_len_value(const char *value)
{
	int	j;

	j = 0;
	while (value[j] && value[j] != ' ')
		j++;
	return (j);
}

void	*free_array_str(char **array)
{

	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
	return (NULL);
}
