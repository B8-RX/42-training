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
	int			total_len;

	total_len = 0;
	printf_props = malloc(sizeof(t_printf));
	if (!printf_props)
		return (0);
	if (!ft_init_printf_props(printf_props))
		return (ft_end_process(printf_props));
	va_start(printf_props -> args, format);
	i = 0;
	while (printf_props -> flags && format[i] != '\0')
	{
		if (printf_props -> flags && format[i] == '%')
		{
			i += ft_verify_format(printf_props, &format[i]);
			total_len += printf_props -> format_len;
			ft_init_printf_props(printf_props);
		}
		else
			total_len += write(1, &format[i++], 1);
	}
	ft_end_process(printf_props);
	return (total_len);
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

int	ft_verify_format(t_printf *printf_props, char *format)
{
	int	i;

	i = 0;
	if (!ft_strchr("scdiupxX%.0123456789# -+", format[i + 1]))
	{
		write(1, &format[i++], 1);
		printf_props -> error_format = 1;
		printf_props -> format_len = 1;
	}
	else
	{
		ft_format_processing(&printf_props, &format[++i]);
		if (!ft_strchr("scdiupxX%", format[i]))
			i += printf_props -> flags_len;
		i++;
	}
	free(printf_props -> flags);
	printf_props -> flags = NULL;
	return (i);
}

int	ft_end_process(t_printf *printf_props)
{
	if (printf_props -> flags)
		va_end(printf_props -> args);
	free(printf_props -> flags);
	printf_props -> flags = NULL;
	free(printf_props);
	printf_props = NULL;
	return (0);
}
