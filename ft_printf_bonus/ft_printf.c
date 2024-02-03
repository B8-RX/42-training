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
	t_printf	*printf_properties;
	int			count;
	int			i;

	printf_properties = malloc(sizeof(t_printf));
	if (!printf_properties)
		return (0);
	va_start(printf_properties -> args, format);
	count = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i += ft_handle_percent(printf_properties, format + i);
			if (printf_properties -> error && !ft_strchr(
					"scdiupxX%.0123456789# -+", format[i + 1]) && count++)
				break ;
			count += printf_properties -> format_len;
		}
		else
			count += write(1, &format[i++], 1);
	}
	ft_end_process(printf_properties);
	return (count);
}

void	ft_end_process(t_printf *printf_props)
{
	va_end(printf_props -> args);
	free(printf_props);
	printf_props = NULL;
}

int	ft_handle_percent(t_printf *printf_props, char *format)
{
	int	i;

	i = 0;
	if (!ft_strchr("scdiupxX%.0123456789# -+", format[i + 1]))
	{
		write(1, &format[i], 1);
		printf_props -> error = 1;
		return (0);
	}
	if (!ft_init_printf_props(printf_props))
	{
		printf_props -> error = 1;
		return (0);
	}	
	ft_handle_format(&printf_props, &format[++i]);
	if (!ft_strchr("scdiupxX%", format[i]))
		i += printf_props -> flags_len;
	i++;
	free(printf_props -> flags);
	printf_props -> flags = NULL;
	return (i);
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
	printf_props -> error = 0;
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

t_printf	*ft_check_special_flags(t_printf **printf_props, char *format)
{	
	int	i;
	int	j;
	int	multiple;

	i = 0;
	while (!ft_strchr("csdiupxX", format[i]))
	{
		if (format[i] == '%')
		{
			write(1, "%", 1);
			(*printf_props)->flags_len = 1;
			return (*printf_props);
		}
		if (format[i] == '-')
		{
			if (format[i - 1] != '%'
				&& (((*printf_props)->flags->width
						|| (*printf_props)->flags->precision)
					|| (*printf_props)->flags -> minus))
				(*printf_props)->error = 1;
			else
				(*printf_props)->flags -> minus = 1;
			i++;
		}
		if (format[i] == '+')
		{
			if (format[i - 1] != '%'
				&& format[i - 1] != '-'
				&& format[i - 1] != '0')
				(*printf_props)->error = 1;
			else
				(*printf_props)->flags -> plus = 1;
			i++;
		}
		if (format[i] == '.')
		{
			if ((*printf_props)->flags -> period)
				(*printf_props)->error = 1;
			else
				(*printf_props)->flags -> period = 1;
			i++;
		}
		if (format[i] > '0' && format[i] <= '9')
		{
			j = 0;
			while (format[i + j] > '0' && format[i + j] <= '9')
				j++;
			if ((*printf_props)->flags -> period)
				(*printf_props)->flags -> precision = ft_atoi(ft_substr(format + i, 0, j));
			else
				(*printf_props)->flags -> width = ft_atoi(ft_substr(format + i, 0, j));
			i += j;
		}
		if (format[i] == '0')
		{
			j = 0;
			multiple = 1;
			while (format[i + j] == '0')
				j++;
			if (format[i - 1] == '%' || format[i - 1] == '+')
				(*printf_props)->flags -> zero = 1;
			i += j;
			while (j--)
				multiple *= 10;
			if ((*printf_props)->flags -> precision)
				(*printf_props)->flags -> precision *= multiple;
			else if ((*printf_props)->flags -> width)
				(*printf_props)->flags -> width *= multiple;
		}
		if (format[i] == ' ')
		{
			(*printf_props)->flags -> blank = 1;
			i++;
		}
		if (format[i] == '#')
		{
			(*printf_props)->flags -> hashtag = 1;
			i++;
		}
	}
	(*printf_props)->flags_len = i;
	if ((*printf_props)->error)
		return (ft_handle_error_format(*printf_props, format));
	if (((*printf_props)->flags -> minus || (*printf_props)->flags -> precision)
		&& (*printf_props)->flags -> zero)
		(*printf_props)->flags -> zero = 0;
	return (ft_handle_format(printf_props, &format[(*printf_props)->flags_len]));
}
