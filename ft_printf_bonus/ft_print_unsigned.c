/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:16:40 by ssghioua          #+#    #+#             */
/*   Updated: 2024/01/18 21:16:41 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_unsigned(unsigned int nb, int size)
{
	char	num;

	if (nb > 9)
	{
		size = 1 + ft_print_unsigned(nb / 10, size);
		num = nb % 10 + '0';
		write(1, &num, 1);
	}
	else
	{
		num = nb + '0';
		size += write(1, &num, 1);
	}
	return (size);
}
