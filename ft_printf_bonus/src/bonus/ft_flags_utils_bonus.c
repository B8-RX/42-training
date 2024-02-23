/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 00:28:13 by ssghioua          #+#    #+#             */
/*   Updated: 2024/02/04 00:28:15 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/ft_printf.h"

int	ft_handle_minus_flag(t_printf *printf_props, char prev_char)
{
	int	width;
	int	precision;
	int	minus;

	width = printf_props->flags->width;
	precision = printf_props->flags->precision;
	minus = printf_props->flags->minus;
	if (prev_char != '%' && (width || precision))
		printf_props->error_format = 1;
	else
		printf_props->flags->minus = 1;
	return (1);
}

int	ft_handle_plus_flag(t_printf *printf_props, char prev_char)
{
	if (!ft_strchr("%-+ 0#", prev_char))
		printf_props->error_format = 1;
	else
		printf_props->flags->plus = 1;
	return (1);
}

int	ft_handle_period_flag(t_printf *printf_props)
{
	if (printf_props->flags->period)
		printf_props->error_format = 1;
	else
		printf_props->flags->period = 1;
	return (1);
}

int	ft_handle_num_flag(t_printf *printf_props, const char *format, int i)
{
	int	j;

	j = 0;
	while (format[i + j] >= '0' && format[i + j] <= '9')
	{
		if (format[i + j] == '0')
			j += ft_handle_zero_flag(printf_props, format, i + j);
		else
			j++;
	}
	if (printf_props->flags->period)
		printf_props->flags->precision = ft_atoi(ft_substr(format + i, 0, j));
	else
		printf_props->flags->width = ft_atoi(ft_substr(format + i, 0, j));
	return (j);
}

int	ft_handle_zero_flag(t_printf *printf_props, const char *format, int i)
{
	int	j;

	j = 0;
	if (!printf_props->flags->zero && ft_strchr("%+", format[i - 1]))
		printf_props->flags->zero = 1;
	while (format[i + j] == '0')
		j++;
	return (j);
}
