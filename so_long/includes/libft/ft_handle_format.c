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

#include "libft.h"

t_printf	*ft_format_processing(t_printf **printf_props, const char *format)
{
	ft_save_specifier_if_found(*printf_props, *format);
	if (*format == 'c')
		ft_print_char(*printf_props, va_arg((*printf_props)->args, int));
	else if (*format == 's')
		ft_handle_s_specifier(*printf_props);
	else if (*format == 'd' || *format == 'i')
		ft_print_str(*printf_props,
			ft_itoa_printf(*printf_props, va_arg((*printf_props)->args, int)));
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
		return (ft_handle_flags(*printf_props, format));
	return (*printf_props);
}

t_printf	*ft_handle_flags(t_printf *printf_props, const char *format)
{	
	int	i;

	i = 0;
	while (format[i] && !ft_strchr("csdiupxX", format[i]))
	{
		if (format[i] == '-')
			i += ft_handle_minus_flag(printf_props, format[i - 1]);
		if (format[i] == '+')
			i += ft_handle_plus_flag(printf_props, format[i - 1]);
		if (format[i] == '.')
			i += ft_handle_period_flag(printf_props);
		if (format[i] >= '0' && format[i] <= '9')
			i += ft_handle_num_flag(printf_props, format, i);
		if (format[i] == ' ' && ++i)
			printf_props->flags->blank = 1;
		if (format[i] == '#')
			i += ft_handle_sharp_flag(printf_props, format, i);
		if (format[i] == '%'
			|| !ft_strchr("csdiupxX.0123456789# -+", format[i]))
			return (ft_handle_err_format(printf_props, format, i));
	}
	return (ft_verify_flags(printf_props, format, i));
}

int	ft_handle_sharp_flag(t_printf *printf_props, const char *format, int i)
{
	if (!ft_strchr("% ", format[i - 1]))
		printf_props->error_format = 1;
	printf_props->flags->sharp = 1;
	return (1);
}

t_printf	*ft_verify_flags(t_printf *printf_props, const char *format, int i)
{
	int	precision;

	printf_props->flags_len = i;
	precision = printf_props->flags->precision;
	if (printf_props->error_format
		&& printf_props->flags->sharp
		&& ft_strchr("sc", format[i]))
		printf_props->error_format = 0;
	if (printf_props->error_format)
		return (ft_handle_err_format(printf_props, format, i));
	if ((printf_props->flags->minus || precision) && printf_props->flags->zero)
		printf_props->flags->zero = 0;
	if (printf_props->flags->period && !(precision > 0))
	{
		if (printf_props->flags->width == 0 && format[i] == 'c')
			return (ft_format_processing(&printf_props, &format[i]));
		printf_props->flags->precision = -1;
	}
	return (ft_format_processing(&printf_props, &format[i]));
}

void	*ft_handle_err_format(t_printf *printf_props, const char *format, int i)
{
	char		*error_format;

	printf_props->error_format = 1;
	printf_props->flags_len = i;
	if (format[printf_props->flags_len] == '%')
	{
		printf_props->format_len = write(1, "%", 1);
		return (NULL);
	}
	error_format = ft_substr(format, 0, printf_props->flags_len + 1);
	ft_print_str(printf_props,
		ft_append_char_to_str(error_format, '%', 1));
	free(error_format);
	error_format = NULL;
	return (NULL);
}
