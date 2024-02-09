/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 07:05:13 by ssghioua          #+#    #+#             */
/*   Updated: 2024/02/07 07:05:14 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/ft_printf.h"

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

int	ft_print_char(char c)
{
	return (write(1, &c, 1));
}

int	ft_print_hexa(unsigned long nb, int size, char format, char *base)
{
	size_t	base_len;

	base_len = ft_strlen(base);
	if (format == 'p' && !nb)
		return (write(1, "(nil)", 5));
	if (nb >= base_len)
	{
		size = 1 + ft_print_hexa(nb / base_len, size, format, base);
		write(1, &base[nb % base_len], 1);
	}
	else
	{
		if (format == 'p')
			size += write(1, "0x", 2);
		size += write(1, &base[nb], 1);
	}
	return (size);
}

int	ft_print_str(char *str, int size)
{
	if (!str)
		return (ft_print_str("(null)", size));
	while (*str != '\0')
	{
		size += ft_print_char(*str);
		str++;
	}
	return (size);
}

int	ft_print_nbr(int nb, int size)
{
	char	num;

	if (nb == -2147483648)
		return (write(1, "-2147483648", 11));
	if (nb < 0)
	{
		size += write(1, "-", 1);
		return (ft_print_nbr(-nb, size));
	}
	if (nb > 9)
	{
		size = 1 + ft_print_nbr(nb / 10, size);
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
