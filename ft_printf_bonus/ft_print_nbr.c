/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:15:51 by ssghioua          #+#    #+#             */
/*   Updated: 2024/01/18 21:15:53 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_nbr(t_printf *printf_props  ,int nb, int size)
{
	char	num;
	char	*temp;

	if (!printf_props -> itoa)
		printf_props -> itoa = malloc(sizeof(char));
	if (!printf_props -> itoa)
		return (0);
	else
		*printf_props -> itoa = '\0';
	if (nb == -2147483648)
	{
		temp = ft_strjoin(printf_props -> itoa, "");
		free(printf_props -> itoa);
		printf_props -> itoa = ft_strjoin(temp, "-2147483648");
		free(temp);
		return (ft_print_str(printf_props, printf_props -> itoa, size));
	}
	if (nb < 0)
	{
		printf_props -> negative_nbr = 1;
		nb = -nb;
	}
	if (nb > 9)
	{
		num = nb % 10 + '0';
		temp = ft_strjoin(printf_props -> itoa, "");
		free(printf_props -> itoa);
		printf_props -> itoa = ft_strjoin(temp, &num);
		free(temp);
		ft_print_nbr(printf_props, nb / 10, size);
	}
	else
	{
		temp = ft_strjoin(printf_props -> itoa, "");
		free(printf_props -> itoa);
		num = nb + '0';
		printf_props -> itoa = ft_strjoin(temp , &num);
		free(temp);	
	}
	return (ft_print_str(printf_props, printf_props -> itoa, size));
}
