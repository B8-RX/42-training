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
	size_t	str_len;
	char	*res;
	char	*temp;

	str_len = ft_strlen(str);
	precision = printf_props -> flags -> precision;
	width = printf_props -> flags -> width;
	if (!str)
		return (ft_print_str(printf_props, "(null)", size, flags));
	if (flags)
	{
		res = malloc(1);
		res[0] = '\0';
		if (precision)
		{
			temp = ft_strjoin("", str);
			str = ft_substr(temp, 0, precision);
			free(temp);
		}
		if (width && width > precision)
		{
			width -= precision;
			while (width)
			{
				temp = ft_strjoin("", res);
				free(res);
				res = ft_strjoin(temp, " ");
				free(temp);
				width--;
			}
		}
		temp = ft_strjoin("", res);
		free(res);
		res = ft_strjoin(temp, str);
		free(temp);
		if (precision)
			free(str);
		while (res[width] != '\0')
		{
			size += write(1, &res[width], 1);
			width++;
		}
		free(res);
	}
	else
		while (*str != '\0')
		{
			size += write(1, &*str, 1);
			str++;
		}
	return (size);
}
