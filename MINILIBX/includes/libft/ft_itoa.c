/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 01:16:04 by ssghioua          #+#    #+#             */
/*   Updated: 2023/11/24 04:26:39 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_int_len(int nb, int parity)
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
	if (parity == -1)
		int_len++;
	return (int_len);
}

char	*ft_fill_str(char *res, int nb, int int_len, int parity)
{
	int	i;

	i = 0;
	while (nb)
	{
		res[int_len - 1 - i] = (nb % 10) + '0';
		nb /= 10;
		i++;
	}
	if (parity == -1)
		res[0] = '-';
	res[int_len] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		int_len;

	sign = 1;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		sign = -1;
	n *= sign;
	int_len = ft_check_int_len(n, sign);
	str = (char *)malloc ((int_len + 1) * sizeof(char));
	if (str == NULL)
		return (str);
	return (ft_fill_str(str, n, int_len, sign));
}
