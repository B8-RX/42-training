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
	int	precision;
	int	width;

	precision = printf_props -> flags -> precision;
	width = printf_props -> flags -> width;
	if (!str)
		return (ft_print_str(printf_props, "(null)", size, flags));
	if (flags)
	{
		if (precision)
			str = ft_substr(str, 0, precision);
		else
			str = ft_substr(str, 0, ft_strlen(str));
		size += ft_print_str_flags(printf_props, str, width, precision);
	}
	else
		while (*str != '\0')
		{
			size += write(1, &*str, 1);
			str++;
		}
	return (size);
}

int	ft_print_str_flags(t_printf *printf_props, char *str, int width, int precision)
{
	char	*result;
	char	*infill;
	int		size;
	int		i;
	
	size = 0;
	infill = malloc(sizeof(char));
	infill[0] = '\0'; 
	if (width > precision)
	{
		width -= precision;
		i = 0;
		infill = ft_handle_width_flag(infill, width);
	}
	if (printf_props -> flags -> minus)
		result = ft_strjoin(str, infill);
	else
		result = ft_strjoin(infill, str);
	i = 0;
	while (result[i] != '\0')
	{
		size += write(1, &result[i], 1);
		i++;
	}
	free(infill);
	free(result);
	free(str);
	return (size);
}

char	*ft_handle_width_flag(char *infill, int width)
{
	char	*temp; 
	int		i;

	i = 0;
	while (i < width)
	{
		temp = ft_strjoin(infill, "");
		free(infill);
		infill = ft_strjoin(temp, " ");
		free(temp); 
		i++;
	}
	return (infill);
}
