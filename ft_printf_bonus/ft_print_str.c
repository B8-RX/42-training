/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:16:08 by ssghioua          #+#    #+#             */
/*   Updated: 2024/01/18 21:16:09 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_str(t_printf *printf_props, char *str, int size, int flags)
{
	int		precision;
	int		width;
	char	*res;
	char	*temp;
	int		i;

	precision = printf_props -> flags -> precision;
	width = printf_props -> flags -> width;
	if (!str)
		return (ft_print_str(printf_props, "(null)", size, flags));
	if (flags)
	{
		res = malloc(1);
		res[0] = '\0';
		if (precision)
			str = ft_substr(str, 0, precision);
		if (width > precision)
		{
			width -= precision;
			i = 0;
			while (i < width)
			{
				temp = ft_strjoin(res, "");
				free(res);
				res = ft_strjoin(temp, " ");
				free(temp); 
				i++;
			}
		}
		if (printf_props -> flags -> minus)
			temp = ft_strjoin(str, res);
		else
			temp = ft_strjoin(res, str);
		free(res);
		if (precision)
			free(str);
		i = 0;
		while (temp[i] != '\0')
		{
			size += write(1, &temp[i], 1);
			i++;
		}
		free(temp);
	}
	else
		while (*str != '\0')
		{
			size += write(1, &*str, 1);
			str++;
		}
	return (size);
}
