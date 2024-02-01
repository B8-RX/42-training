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

	args = &((*printf_props) -> args);
	len = 0;
	if (ft_strchr("csdiupxX", *format))
	{
		(*printf_props) -> specifier = *format;
		if (ft_strchr("px" ,*format))
			(*printf_props) -> base = BASE_LOW;
		if (*format == 'X')
			(*printf_props) -> base = BASE_UP;
	}
	if (*format == 'c')
		(*printf_props) -> format_len += ft_print_char(printf_props, va_arg(*args, int));
	else if (*format == 's')
		(*printf_props) -> format_len += ft_print_str(*printf_props, ft_strjoin((char *)va_arg(*args, void *), ""), len);
	else if (*format == 'd' || *format == 'i')
		(*printf_props) -> format_len += ft_print_str(*printf_props, ft_itoa(*printf_props, va_arg(*args, int)), len);
	else if (*format == 'u')
		(*printf_props) -> format_len += ft_print_str(*printf_props, ft_uitoa(va_arg(*args, unsigned int)), len);
	else if (*format == 'p')
		(*printf_props) -> format_len += ft_print_str(*printf_props, ft_ultoa(*printf_props, va_arg(*args, unsigned long)), len);
	else if (*format == 'x')
		(*printf_props) -> format_len += ft_print_str(*printf_props, ft_ultoa(*printf_props, va_arg(*args, unsigned int)), len);
	else if (*format == 'X')
		(*printf_props) -> format_len += ft_print_str(*printf_props, ft_ultoa(*printf_props, va_arg(*args, unsigned int)), len);
	else if (*format == '%')	
		(*printf_props) -> format_len += write(1, "%", 1);
	else if (ft_strchr(".0123456789#- +", *format))
	{
		if (!ft_check_special_flags(printf_props, format))
		{
			char	*error_format;

			error_format = ft_substr(format, 0, (*printf_props) -> flags_len + 1);
			(*printf_props) -> format_len += ft_print_str(*printf_props, ft_append_char_str(error_format, '%', 1), len);
			return (free(error_format), *printf_props);
		}
		return (ft_handle_format(printf_props, &format[(*printf_props) -> flags_len]));
	}
	
	return (*printf_props);
}
