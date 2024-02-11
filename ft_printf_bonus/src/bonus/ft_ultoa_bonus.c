/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 03:07:03 by ssghioua          #+#    #+#             */
/*   Updated: 2024/01/29 03:07:07 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/ft_printf.h"

char	*ft_fill_ul_str(t_printf *printf_props, unsigned long nb, char *res)
{
	char	*base;
	char	*temp;

	base = printf_props->base;
	while (nb >= ft_strlen(base))
	{
		temp = ft_append_char_to_str(res, base[nb % ft_strlen(base)], 1);
		free(res);
		res = ft_strjoin(temp, "");
		free(temp);
		nb /= ft_strlen(base);
	}
	temp = ft_append_char_to_str(res, base[nb % ft_strlen(base)], 1);
	free(res);
	res = ft_strjoin(temp, "");
	free(temp);
	if (printf_props->specifier == 'p' || printf_props->flags->sharp)
		res = ft_append_prefix_hexa(printf_props, res);
	return (res);
}

char	*ft_ultoa(t_printf *printf_props, unsigned long n)
{
	char	*res;

	if (n == 0 && printf_props->specifier == 'p')
		return (ft_strjoin("(nil)", ""));
	else if (n == 0)
		return (ft_strjoin("0", ""));
	res = ft_strjoin("", "");
	return (ft_fill_ul_str(printf_props, n, res));
}

char	*ft_append_prefix_hexa(t_printf *printf_props, char *str)
{
	char	*temp;

	if (printf_props->specifier == 'X')
		temp = ft_strjoin("0X", str);
	else
		temp = ft_strjoin("0x", str);
	free(str);
	str = ft_strjoin(temp, "");
	free(temp);
	return (str);
}
