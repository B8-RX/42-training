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
	int			flags;
	va_list		*args;

	args = &((*printf_props) -> args);
	len = 0;
	flags = 0;
	if (*format == 'c')
		(*printf_props) -> step += write(1, &*format, 1);
	else if (*format == 's')
	{
		if ((*printf_props) -> flags -> precision || (*printf_props) -> flags -> width)
			flags = 1;	
		(*printf_props) -> step += ft_print_str(*printf_props, (char *)va_arg(*args, void *), len, flags);
	}
	else if (*format == 'd' || *format == 'i')
		(*printf_props) -> step += ft_print_nbr(va_arg(*args, int), len);
	else if (*format == 'u')
		(*printf_props) -> step += ft_print_unsigned(va_arg(*args, unsigned int), len);
	else if (*format == 'p')
		(*printf_props) -> step += ft_print_hexa(va_arg(*args, unsigned long), len, *format, BASE_LOW);
	else if (*format == 'x')
		(*printf_props) -> step += ft_print_hexa(va_arg(*args, unsigned int), len, *format, BASE_LOW);
	else if (*format == 'X')
		(*printf_props) -> step += ft_print_hexa(va_arg(*args, unsigned int), len, *format, BASE_UP);
	else if (*format == '%')	
		(*printf_props) -> step += write(1, "%", 1);
	else if (ft_strchr(".0123456789#- +", *format))
	{
		*printf_props = ft_check_special_flags(printf_props, format);
		return (ft_handle_format(printf_props, &format[(*printf_props) -> flags_len]));
	}
	return (*printf_props);
}
