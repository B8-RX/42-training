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

int	ft_print_str(t_printf *printf_props, char *str)
{
	int		i;
	char	*new;

	i = 0;
	if (!str)
		return (ft_print_str(printf_props, "(null)"));
	if (printf_props -> flags_len
		&& !printf_props -> updated
		&& !printf_props -> error_format)
	{
		new = ft_update_str(printf_props, str);
		return (ft_print_str(printf_props, new));
	}
	if (ft_strchr("csdiupxX%", printf_props -> specifier)
		|| printf_props -> error_format || *str == '%')
		while (str[i] != '\0')
			printf_props->format_len += write(1, &str[i++], 1);
	free(str);
	return (printf_props->format_len);
}

char	*ft_update_str(t_printf *printf_props, char *str)
{
	char	*new;
	char	*infill;
	int		width;
	int		precision;

	precision = printf_props->flags->precision;
	width = printf_props -> flags -> width;
	infill = ft_strjoin("", "");
	if (precision && ft_strchr("sc", printf_props->specifier))
		str = ft_slice_str(printf_props, str);
	if (width > precision)
		infill = ft_generate_infill(printf_props, infill, str);
	if (printf_props -> flags -> minus)
		new = ft_justify_infill_right(str, infill);
	else
		new = ft_justify_infill_left(printf_props, str, infill);
	printf_props -> updated = 1;
	return (new);
}

char	*ft_generate_infill(t_printf *printf_props, char *infill, char *str)
{
	char	*temp;
	int		i;
	int		width;

	i = 0;
	width = printf_props -> flags -> width;
	width -= ft_strlen(str);
	while (i < width)
	{
		temp = ft_strjoin(infill, "");
		free(infill);
		if (!ft_strchr("cs", printf_props->specifier)
			&& printf_props -> flags -> zero
			&& !printf_props -> flags -> precision)
			infill = ft_strjoin(temp, "0");
		else
			infill = ft_strjoin(temp, " ");
		free(temp);
		i++;
	}
	return (infill);
}
