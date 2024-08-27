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

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	t_printf	*printf_props;
	int			i;
	int			total_len;

	total_len = 0;
	printf_props = malloc(sizeof(t_printf));
	if (!printf_props || !format)
		return (ft_end_process(printf_props, format));
	va_start(printf_props->args, format);
	i = 0;
	printf_props->updated = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			if (!ft_init_printf_props(printf_props))
				return (ft_end_process(printf_props, format));
			i += ft_verify_format(printf_props, &format[i]);
			total_len += printf_props->format_len;
		}
		else
			total_len += write(1, &format[i++], 1);
	}
	ft_end_process(printf_props, format);
	return (total_len);
}

t_printf	*ft_init_printf_props(t_printf *printf_props)
{
	printf_props->flags = malloc(sizeof(t_flags));
	if (!printf_props->flags)
		return (NULL);
	printf_props->specifier = '0';
	printf_props->format_len = 0;
	printf_props->flags_len = 0;
	printf_props->updated = 0;
	printf_props->base = NULL;
	printf_props->error_format = 0;
	printf_props->negative_nbr = 0;
	printf_props->flags->period = 0;
	printf_props->flags->precision = 0;
	printf_props->flags->blank = 0;
	printf_props->flags->zero = 0;
	printf_props->flags->sharp = 0;
	printf_props->flags->plus = 0;
	printf_props->flags->minus = 0;
	printf_props->flags->width = 0;
	return (printf_props);
}

int	ft_verify_format(t_printf *printf_props, const char *format)
{
	int	i;

	i = 0;
	if (format[i + 1] == '%')
	{
		printf_props->specifier = '%';
		ft_print_percent_sign(printf_props);
		i += 2;
	}
	else if (!ft_strchr("scdiupxX.0123456789# -+", format[i + 1]))
	{
		write(1, &format[i++], 1);
		printf_props->error_format = 1;
		printf_props->format_len = 1;
	}
	else if (ft_strchr("scdiupxX.0123456789# -+", format[i + 1]))
	{
		ft_format_processing(&printf_props, &format[++i]);
		if (!ft_strchr("scdiupxX", format[i]))
			i += printf_props->flags_len;
		i++;
	}
	free(printf_props->flags);
	printf_props->flags = NULL;
	return (i);
}

void	ft_save_specifier_if_found(t_printf *printf_props, const char format)
{
	t_flags	*flags;

	flags = printf_props->flags;
	if (ft_strchr("csdiupxX", format))
		printf_props->specifier = format;
	if (ft_strchr("px", format))
		printf_props->base = BASE_LOW;
	else if (format == 'X')
		printf_props->base = BASE_UP;
	else if (ft_strchr("sc", printf_props->specifier))
	{
		if (flags->zero)
			flags->zero = 0;
		if (flags->period && printf_props->specifier == 'c')
		{
			flags->period = 0;
			flags->precision = 0;
		}
		if (printf_props->flags->blank)
			printf_props->flags->blank = 0;
	}
}

int	ft_end_process(t_printf *printf_props, const char *format)
{
	if (!format)
	{
		if (printf_props)
			free(printf_props);
		return (-1);
	}
	if (printf_props->updated)
	{
		free(printf_props->flags);
		printf_props->flags = NULL;
	}
	va_end(printf_props->args);
	free(printf_props);
	printf_props = NULL;
	return (0);
}
