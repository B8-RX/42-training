/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 02:46:50 by ssghioua          #+#    #+#             */
/*   Updated: 2024/01/28 02:46:52 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_num_len(t_printf *printf_props, int nb)
{
	int	num_len;

	num_len = 0;
	while (nb > 9)
	{
		nb /= 10;
		num_len++;
	}
	if (nb > 0)
		num_len++;
	if (printf_props -> flags -> precision > num_len)
		num_len = printf_props -> flags -> precision;
	if (printf_props -> negative_nbr || printf_props -> flags -> plus)
		num_len++;
	if (printf_props -> flags -> blank
		&& !printf_props -> flags -> plus && !printf_props -> negative_nbr)
		num_len++;
	return (num_len);
}

char	*ft_fill_str(t_printf *printf_props, char *res, int nb, int num_len)
{
	int		i;

	i = 0;
	while (nb)
	{
		res[num_len - 1 - i] = (nb % 10) + '0';
		nb /= 10;
		i++;
	}
	if (num_len - 1 - i >= 0)
		while (num_len - 1 - i >= 0)
			res[num_len - 1 - i++] = '0';
	i = 0;
	if (printf_props -> flags -> plus)
		res[i++] = '+';
	else if (printf_props -> negative_nbr)
		res[i++] = '-';
	if (printf_props -> flags -> blank
		&& !printf_props -> flags -> plus && !printf_props -> negative_nbr)
		res[i] = ' ';
	res[num_len] = '\0';
	return (res);
}

char	*ft_itoa(t_printf *printf_props, int n)
{
	int		num_len;
	char	*res;

	num_len = 0;
	if (n == 0)
		return (ft_strjoin("0", ""));
	if (n == -2147483648)
		return (ft_strjoin("-2147483648", ""));
	if (n < 0)
	{
		printf_props -> negative_nbr = 1;
		n *= -1;
	}
	num_len += ft_check_num_len(printf_props, n);
	res = (char *)malloc((num_len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	return (ft_fill_str(printf_props, res, n, num_len));
}
