/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 21:34:56 by ssghioua          #+#    #+#             */
/*   Updated: 2024/01/19 21:34:58 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	*ft_format_processing(t_printf **printf_props, char *format)
{
	ft_save_specifier_if_found(*printf_props, *format);
	if (*format == 'c')
		ft_print_char(printf_props, va_arg((*printf_props)->args, int));
	else if (*format == 's')
		ft_print_str(*printf_props,
			ft_strjoin((char *)va_arg((*printf_props)->args, void *), ""));
	else if (*format == 'd' || *format == 'i')
		ft_print_str(*printf_props,
			ft_itoa(*printf_props, va_arg((*printf_props)->args, int)));
	else if (*format == 'u')
		ft_print_str(*printf_props,
			ft_uitoa(va_arg((*printf_props)->args, unsigned int)));
	else if (*format == 'p')
		ft_print_str(*printf_props, ft_ultoa(*printf_props,
				va_arg((*printf_props)->args, unsigned long)));
	else if (*format == 'x')
		ft_print_str(*printf_props, ft_ultoa(*printf_props,
				va_arg((*printf_props)->args, unsigned int)));
	else if (*format == 'X')
		ft_print_str(*printf_props, ft_ultoa(*printf_props,
				va_arg((*printf_props)->args, unsigned int)));
	else if (ft_strchr("%.0123456789# -+", *format))
		return (ft_handle_special_flags(printf_props, format));
	return (*printf_props);
}

void	ft_save_specifier_if_found(t_printf *printf_props, char format)
{
	if (ft_strchr("csdiupxX", format))
	{
		printf_props->specifier = format;
		if (ft_strchr("px", format))
			printf_props->base = BASE_LOW;
		if (format == 'X')
			printf_props->base = BASE_UP;
	}
}

t_printf	*ft_handle_special_flags(t_printf **printf_props, char *format)
{	
	int	i;

	i = 0;
	while (format[i] && !ft_strchr("csdiupxX", format[i]))
	{
		if (format[i] == '%')
			return (ft_print_percent_sign(printf_props));
		if (format[i] == '-')
			i += ft_handle_minus_flag(*printf_props, format[i - 1]);
		if (format[i] == '+')
			i += ft_handle_plus_flag(*printf_props, format[i - 1]);
		if (format[i] == '.')
			i += ft_handle_period_flag(*printf_props);
		if (format[i] > '0' && format[i] <= '9')
			i += ft_handle_num_flag(*printf_props, format, i);
		if (format[i] == '0')
			i += ft_handle_zero_flag(*printf_props, format, i);
		if (format[i] == ' ' && ++i)
			(*printf_props)->flags -> blank = 1;
		if (format[i] == '#' && ++i)
			(*printf_props)->flags -> hashtag = 1;
		if (!ft_strchr("csdiupxX%.0123456789# -+", format[i]))
			return (ft_handle_error_format(*printf_props, format));
	}
	return (ft_verify_flags(*printf_props, format, i));
}

int	ft_verify_format(t_printf *printf_props, char *format)
{
	int	i;

	i = 0;
	if (!ft_strchr("scdiupxX%.0123456789# -+", format[i + 1]))
	{
		write(1, &format[i++], 1);
		printf_props -> error_format = 1;
		printf_props -> total_len += 1;
		return (i);
	}
	if (!ft_init_printf_props(printf_props))
	{	
		printf_props -> error_init = 1;
		return (i);
	}	
	ft_format_processing(&printf_props, &format[++i]);
	if (!ft_strchr("scdiupxX%", format[i]))
		i += printf_props -> flags_len;
	i++;
	free(printf_props -> flags);
	printf_props -> flags = NULL;
	return (i);
}

t_printf	*ft_verify_flags(t_printf *printf_props, char *format, int i)
{
	int	minus;
	int	precision;
	int	zero;

	printf_props -> flags_len = i;
	minus = printf_props -> flags -> minus;
	precision = printf_props -> flags -> precision;
	zero = printf_props -> flags -> zero;
	if (printf_props -> error_format)
		return (ft_handle_error_format(printf_props, format));
	if ((minus || precision) && zero)
		zero = 0;
	return (ft_format_processing(&printf_props, &format[i]));
}
