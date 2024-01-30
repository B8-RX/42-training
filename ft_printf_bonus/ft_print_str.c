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
	int		precision;
	int		i;
	char	*new;

	precision = printf_props -> flags -> precision;
	i = 0;
	if (!str)
		return (ft_print_str(printf_props, "(null)", size));
	if (printf_props -> flags_len && !printf_props -> updated)
	{
		if (precision)
			new = ft_substr(str, 0, precision);
		else
			new = ft_substr(str, 0, ft_strlen(str));
		free(str);
		new = ft_update_str(printf_props, new);
	
		return (ft_print_str(printf_props, new, size));	
	}
	if (ft_strchr("csdiupxX", printf_props -> specifier))
		while (str[i] != '\0')
			size += write(1, &str[i++], 1);
	return (free(str), size);
}

char	*ft_update_str(t_printf *printf_props, char *str)
{
	char	*new_str;
	char	*infill;
	int		width;
	int		precision;

	precision = printf_props -> flags -> precision;
	width = printf_props -> flags -> width;
	infill = malloc(sizeof(char));
	infill[0] = '\0';
	if (width > precision)
	{
		width -= ft_strlen(str);
		infill = ft_infill_str(printf_props, infill, width);
	}
	if (printf_props -> flags -> minus)
		new_str = ft_strjoin(str, infill);
	else
	{
		if (printf_props -> negative_nbr && printf_props -> flags -> zero)
		{
			new_str = ft_substr(str, 1, ft_strlen(str) - 1);
			free(str);
			str = ft_strjoin(infill, new_str);
			free(new_str);
			new_str = ft_strjoin("-", str);
		}
		else if (ft_strchr( "di",printf_props -> specifier)
			&& printf_props -> flags -> plus && printf_props -> flags -> zero)
		{
			new_str = ft_substr(str, 1, ft_strlen(str) - 1);
			free(str);
			str = ft_strjoin(infill, new_str);
			free(new_str);
			new_str = ft_strjoin("+", str);
		}
		else
			new_str = ft_strjoin(infill, str);
	}

	printf_props -> updated = 1;
	return (free(infill), free(str), new_str);
}

char	*ft_infill_str(t_printf *printf_props, char *infill, int width)
{
	char	*temp;
	int		i;

	i = 0;
	while (i < width)
	{
		temp = ft_strjoin(infill, "");
		free(infill);
		if (!ft_strchr("cs", printf_props -> specifier)
			&& printf_props -> flags -> zero)
			infill = ft_strjoin(temp, "0");
		else
			infill = ft_strjoin(temp, " ");
		free(temp);
		i++;
	}
	return (infill);
}
