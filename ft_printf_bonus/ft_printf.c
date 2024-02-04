/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:05:22 by ssghioua          #+#    #+#             */
/*   Updated: 2024/01/16 11:05:26 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(char *format, ...)
{
	t_printf	*printf_props;
	int			i;

	printf_props = malloc(sizeof(t_printf));
	if (!printf_props)
		return (0);
	va_start(printf_props -> args, format);
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i += ft_verify_format(printf_props, &format[i]);
			if (printf_props -> error_init)
				break ;
			printf_props -> total_len += printf_props -> format_len;
		}
		else
			printf_props -> total_len += write(1, &format[i++], 1);
	}
	i = printf_props -> total_len;
	ft_end_process(printf_props);
	return (i);
}

void	ft_end_process(t_printf *printf_props)
{
	va_end(printf_props -> args);
	free(printf_props);
	printf_props = NULL;
}

t_printf	*ft_init_printf_props(t_printf *printf_props)
{
	printf_props -> flags = malloc(sizeof(t_flags));
	if (!printf_props -> flags)
		return (NULL);
	printf_props -> specifier = '0';
	printf_props -> format_len = 0;
	printf_props -> flags_len = 0;
	printf_props -> updated = 0;
	printf_props -> base = NULL;
	printf_props -> error_format = 0;
	printf_props -> error_init = 0;
	printf_props -> negative_nbr = 0;
	printf_props -> flags -> period = 0;
	printf_props -> flags -> precision = 0;
	printf_props -> flags -> blank = 0;
	printf_props -> flags -> zero = 0;
	printf_props -> flags -> hashtag = 0;
	printf_props -> flags -> plus = 0;
	printf_props -> flags -> minus = 0;
	printf_props -> flags -> width = 0;
	return (printf_props);
}

void	*ft_handle_error_format(t_printf *printf_props, char *format)
{
	char		*error_format;

	printf_props -> error_format = 1;
	error_format = ft_substr(format, 0, printf_props->flags_len + 1);
	ft_print_str(printf_props, ft_append_char_to_str(error_format, '%', 1));
	free(error_format);
	return (NULL);
}
