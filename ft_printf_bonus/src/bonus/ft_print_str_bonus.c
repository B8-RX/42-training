/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:16:08 by ssghioua          #+#    #+#             */
/*   Updated: 2024/01/18 21:16:09 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/ft_printf.h"

int	ft_print_str_bonus(t_printf *printf_props, char *str)
{
	int		i;
	char	*new;

	i = 0;
	if (!str)
		return (ft_print_str_bonus(printf_props, ft_strjoin("(null)", "")));
	if (printf_props -> flags_len
		&& !printf_props -> updated
		&& !printf_props -> error_format)
	{
		new = ft_update_str(printf_props, str);
		return (ft_print_str_bonus(printf_props, new));
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
	if (*str && (precision == -1 || (precision
				&& ft_strchr("sc", printf_props->specifier))))
		str = ft_slice_str(printf_props, str);
	if (width > precision || precision)
	{
		if (width > precision)
			infill = ft_generate_infill(printf_props, infill, str, width);
		else
			infill = ft_generate_infill(printf_props, infill, str, precision);
	}
	if (printf_props -> flags -> minus)
		new = ft_justify_infill_right(printf_props, str, infill);
	else
		new = ft_justify_infill_left(printf_props, str, infill);
	if (printf_props -> flags -> plus || printf_props -> negative_nbr)
		new = ft_append_sign(printf_props, new);
	return (new);
}

char	*ft_generate_infill(t_printf *props, char *fill, char *str, int len)
{
	char	*temp;
	int		width;
	int		i;
	int		str_len;

	i = 0;
	width = len;
	str_len = (int)ft_strlen(str);
	if (props->flags->plus || (props->negative_nbr && !props->flags->precision))
		width--;
	width -= str_len;
	while (i < width)
	{
		temp = ft_strjoin(fill, "");
		free(fill);
		if (!ft_strchr("sc", props->specifier)
			&& (props->flags->zero
				|| (props->flags->precision && props->negative_nbr)))
			fill = ft_strjoin(temp, "0");
		else
			fill = ft_strjoin(temp, " ");
		free(temp);
		i++;
	}
	return (fill);
}
