/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infill_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 02:14:14 by ssghioua          #+#    #+#             */
/*   Updated: 2024/02/17 02:14:16 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lib/ft_printf.h"

char	*ft_set_infill(t_printf *props, char *str)
{
	char	*infill;
	int		error_format;
	int		str_len;

	str_len = (int)ft_strlen(str);
	error_format = props->error_format;
	infill = ft_strjoin("", "");
	if (props->flags->precision > str_len && ft_strchr("sc", props->specifier))
		props->flags->precision = str_len;
	infill = ft_populate_infill(props, infill, str);
	if ((props->specifier == 'p' || props->flags->sharp)
		&& ((props->flags->minus && props->flags->width > str_len)
			|| props->flags->minus)
		&& !error_format)
		infill = ft_append_prefix_hexa(props, infill);
	if (props->flags->blank && ft_strchr("sdi", props->specifier))
		infill = ft_append_blank(props, infill);
	return (infill);
}

char	*ft_populate_infill(t_printf *props, char *infill, char *str)
{
	int		precision;
	int		str_len;

	precision = props->flags->precision;
	if (props->flags->period && ft_strchr("diuxX", props->specifier))
		str = ft_infill_precision(props, str);
	str_len = (int)ft_strlen(str);
	if (props->flags->width > str_len)
		infill = ft_infill_width(props, infill, str_len);
	return (ft_justify_infill(props, infill, str));
}

char	*ft_justify_infill(t_printf *props, char *infill, char *str)
{
	char	*new;

	if (props->flags->minus)
		new = ft_justify_infill_right(props, str, infill);
	else
		new = ft_justify_infill_left(props, str, infill);
	return (new);
}

char	*ft_infill_width(t_printf *props, char *infill, int input_len)
{
	char	*temp;
	int		i;

	if (!props->error_format && (props->specifier == 'p'
			|| (props->flags->sharp && ft_strchr("xX", props->specifier))))
		input_len += 2;
	if (props->flags->plus || props->negative_nbr)
		props->flags->width -= 1;
	props->flags->width -= input_len;
	i = 0;
	while (i < props->flags->width)
	{
		temp = ft_strjoin(infill, "");
		free(infill);
		if (!props->error_format && props->flags->precision != -1
			&& props->flags->zero
			&& ft_strchr("diuxXp", props->specifier))
			infill = ft_strjoin("0", temp);
		else
			infill = ft_strjoin(" ", temp);
		free(temp);
		i++;
	}
	return (infill);
}

char	*ft_infill_precision(t_printf *props, char *str_input)
{
	int		prefix;
	int		precision;
	int		width;
	char	*infill;
	char	*res;

	prefix = 0;
	precision = props->flags->precision;
	width = props->flags->width;
	if (props->flags->plus || props->negative_nbr)
		prefix = 1;
	if (precision)
		infill = ft_bzero(precision - (int)ft_strlen(str_input));
	else
		infill = ft_strjoin("", "");
	if (prefix && ((width > precision) || !width))
	{
		infill = ft_append_parity(props, infill);
		props->negative_nbr = 0;
	}
	res = ft_strjoin(infill, str_input);
	free(infill);
	free(str_input);
	return (res);
}
