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

char	*ft_fill_ul_str(t_printf *printf_props, unsigned long nb)
{
	char	*base;
	char	*res;
	char	*temp;

	base = printf_props -> base;
	res = ft_strjoin("", "");
	while (nb >= ft_strlen(base))
	{
		temp = malloc(2);
		if (!temp)
			return (NULL);
		temp[0] = base[nb % ft_strlen(base)];
		temp[1] = '\0';
		res = ft_strjoin(temp, res);
		free(temp);
		nb /= ft_strlen(base);
	}
	temp = malloc(2);
	if (!temp)
		return (NULL);
	temp[0] = base[nb % ft_strlen(base)];
	temp[1] = '\0';
	res = ft_strjoin(temp, res);
	free(temp);
	if (printf_props -> specifier == 'p')
	{
		temp = ft_strjoin("0x", res);
		free(res);
		res = ft_strjoin(temp, "");
		free(temp);
	} 
	return (res);
}

char	*ft_ultoa(t_printf *printf_props, unsigned long n)
{
	if (n == 0)
		return (ft_strjoin("0", ""));

	return (ft_fill_ul_str(printf_props, n));
}
