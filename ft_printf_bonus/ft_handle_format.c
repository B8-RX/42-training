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

t_printf	*ft_handle_format(t_printf **printf_props, char *format)
{
	int			len;
	va_list		*args;
	char		*output;

	args = &((*printf_props) -> args);
	len = 0;
	if (ft_strchr("csdiupxX", *format))
		(*printf_props) -> specifier = *format;
	if (*format == 'c')
		(*printf_props) -> format_len += ft_print_char(printf_props, va_arg(*args, int));
	else if (*format == 's')
	{
		output = ft_strjoin((char *)va_arg(*args, void *), "");
		(*printf_props) -> format_len += ft_print_str(*printf_props, output, len);
	}
	else if (*format == 'd' || *format == 'i')
	{
		output = ft_itoa(*printf_props, va_arg(*args, int));
		(*printf_props) -> format_len += ft_print_str(*printf_props, output, len);
	}
	else if (*format == 'u')
	{
		output = ft_itoa(*printf_props, va_arg(*args, unsigned int));
		(*printf_props) -> format_len += ft_print_str(*printf_props, output, len);
	}
	else if (*format == 'p')
		(*printf_props) -> format_len += ft_print_hexa(va_arg(*args, unsigned long), len, *format, BASE_LOW);
	else if (*format == 'x')
		(*printf_props) -> format_len += ft_print_hexa(va_arg(*args, unsigned int), len, *format, BASE_LOW);
	else if (*format == 'X')
		(*printf_props) -> format_len += ft_print_hexa(va_arg(*args, unsigned int), len, *format, BASE_UP);
	else if (*format == '%')	
		(*printf_props) -> format_len += write(1, "%", 1);
	else if (ft_strchr(".0123456789#- +", *format))
	{
		if (!ft_check_special_flags(printf_props, format))
			return (NULL);
		return (ft_handle_format(printf_props, &format[(*printf_props) -> flags_len]));
	}
	
	return (*printf_props);
}
