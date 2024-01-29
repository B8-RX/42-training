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

int	ft_check_int_len(t_printf *printf_props, int nb)
{
	int	int_len;

	int_len = 0;
	while (nb > 9)
	{
		nb /= 10;
		int_len++;
	}
	if (nb > 0)
		int_len++;
	if (printf_props -> negative_nbr)
		int_len++;
	return (int_len);
}

char	*ft_fill_str(t_printf *printf_props, char *res, int nb, int int_len)
{
	int	i;

	i = 0;
	while (nb)
	{
		res[int_len - 1 - i] = (nb % 10) + '0';
		nb /= 10;
		i++;
	}
	if (!printf_props -> negative_nbr && printf_props -> flags -> plus)
		res[0] = '+';
	else if (printf_props -> negative_nbr)
		res[0] = '-';
	res[int_len] = '\0';
	return (res);
}

char	*ft_itoa(t_printf *printf_props, int n)
{
	char	*str;
	int		int_len;

	int_len = 0;
	if (n == 0)
		return (ft_strjoin("0", ""));
	if (n == -2147483648)
		return (ft_strjoin("-2147483648", ""));
	if (!printf_props -> negative_nbr && printf_props -> flags -> plus)
		int_len++;
	if (n < 0)
	{
		printf_props -> negative_nbr = 1;
		n *= -1;
	}
	int_len += ft_check_int_len(printf_props, n);
	str = (char *)malloc ((int_len + 1) * sizeof(char));
	if (str == NULL)
		return (str);
	return (ft_fill_str(printf_props, str, n, int_len));
}
