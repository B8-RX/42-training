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

#include "ft_printf.h"

int	ft_handle_minus_flag(t_printf *printf_props, char prev_char)
{
	int	width;
	int	precision;
	int	minus;

	width = printf_props -> flags -> width;
	precision = printf_props -> flags -> precision;
	minus = printf_props -> flags -> minus;
	if (prev_char != '%' && (width || precision || minus))
		printf_props -> error_format = 1;
	else
		printf_props -> flags -> minus = 1;
	return (1);
}

int	ft_handle_plus_flag(t_printf *printf_props, char prev_char)
{
	if (!ft_strchr("%- 0#", prev_char))
		printf_props -> error_format = 1;
	else
		printf_props -> flags -> plus = 1;
	return (1);
}

int	ft_handle_period_flag(t_printf *printf_props)
{
	if (printf_props -> flags -> period)
		printf_props -> error_format = 1;
	else
		printf_props -> flags -> period = 1;
	return (1);
}

int	ft_handle_num_flag(t_printf *printf_props, char *format, int i)
{
	int	j;

	j = 0;
	while (format[i + j] > '0' && format[i + j] <= '9')
		j++;
	if (printf_props -> flags -> period)
		printf_props->flags->precision = ft_atoi(ft_substr(format + i, 0, j));
	else
		printf_props -> flags -> width = ft_atoi(ft_substr(format + i, 0, j));
	return (j);
}

int	ft_handle_zero_flag(t_printf *printf_props, char *format, int i)
{
	int	j;
	int	multiple;

	j = 0;
	multiple = 1;
	while (format[i + j] == '0')
		j++;
	if (ft_strchr("%+", format[i - 1]))
		printf_props -> flags -> zero = 1;
	i = j;
	while (j--)
		multiple *= 10;
	if (printf_props -> flags -> precision)
		printf_props -> flags -> precision *= multiple;
	else if (printf_props ->flags -> width)
		printf_props -> flags -> width *= multiple;
	return (i);
}
