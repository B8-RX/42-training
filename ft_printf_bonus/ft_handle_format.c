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
	ft_init_specifier(*printf_props, *format);
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
	else
		return (ft_check_special_flags(printf_props, format));
	return (*printf_props);
}

void	ft_init_specifier(t_printf *printf_props, char format)
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

void	*ft_handle_error_format(t_printf *printf_props, char *format)
{
	char		*error_format;

	error_format = ft_substr(format, 0, printf_props->flags_len + 1);
	ft_print_str(printf_props, ft_append_char_str(error_format, '%', 1));
	free(error_format);
	return (NULL);
}
