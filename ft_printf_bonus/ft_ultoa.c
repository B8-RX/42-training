/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 03:07:03 by ssghioua          #+#    #+#             */
/*   Updated: 2024/01/29 03:07:07 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_ul_len(unsigned long nb)
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
	return (int_len);
}

char	*ft_fill_ul_str(char *res, unsigned long nb, int int_len)
{
	int	i;

	i = 0;
	while (nb)
	{
		res[int_len - 1 - i] = (nb % 10) + '0';
		nb /= 10;
		i++;
	}
	res[int_len] = '\0';
	return (res);
}

char	*ft_ultoa(unsigned long n)
{
	char	*str;
	int		int_len;

	if (n == 0)
		return (ft_strjoin("0", ""));
	int_len = ft_check_ul_len(n);
	str = (char *)malloc ((int_len + 1) * sizeof(char));
	if (str == NULL)
		return (str);
	return (ft_fill_ul_str(str, n, int_len));
}
