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

int	ft_print_str(t_printf *printf_props, char *str, int size)
{
	int	precision;
	int	width;
	int	i;

	precision = printf_props -> flags -> precision;
	width = printf_props -> flags -> width;
	i = 0;
	if (!str)
		return (ft_print_str(printf_props, "(null)", size));
	if (printf_props -> flags_len && !printf_props -> updated)
	{
		if (precision)
			str = ft_substr(str, 0, precision);
		else
			str = ft_substr(str, 0, ft_strlen(str));
		str = ft_update_str(printf_props, str);
		return (ft_print_str(printf_props, str, size));
	}
	else
		while (str[i] != '\0')
			size += write(1, &str[i++], 1);
	if (printf_props -> updated)
		free(str);
	return (size);
}

char	*ft_update_str(t_printf *printf_props, char *str)
{
	char	*new_str;
	char	*infill;
	int		width;
	int		precision;
	int		i;

	precision = printf_props -> flags -> precision;
	width = printf_props -> flags -> width;
	infill = malloc(sizeof(char));
	infill[0] = '\0';
	if (width > precision)
	{
		width -= precision;
		i = 0;
		infill = ft_infill_str(infill, width);
	}
	printf_props -> updated = 1;
	if (printf_props -> flags -> minus)
		new_str = ft_strjoin(str, infill);
	else
		new_str = ft_strjoin(infill, str);
	free(infill);
	free(str);
	return (new_str);
}

char	*ft_infill_str(char *infill, int width)
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
