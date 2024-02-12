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

#include "./lib/ft_printf.h"

int	ft_check_num_len(int nb)
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
	return (num_len);
}

char	*ft_fill_str(char *res, int nb, int num_len)
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
	{
		printf_props->negative_nbr = 1;
		return (ft_strjoin("2147483648", ""));
	}
	if (n < 0)
	{
		printf_props->negative_nbr = 1;
		n *= -1;
	}
	num_len += ft_check_num_len(n);
	res = (char *)malloc((num_len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	return (ft_fill_str(res, n, num_len));
}
