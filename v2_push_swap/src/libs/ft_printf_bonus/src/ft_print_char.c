/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 00:00:34 by ssghioua          #+#    #+#             */
/*   Updated: 2024/01/26 00:00:36 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lib/ft_printf.h"

int	ft_print_char(t_printf *printf_props, char c)
{
	if (printf_props->flags->width > 1)
		return (ft_handle_char_with_flags(printf_props, c));
	printf_props->format_len += write(1, &c, 1);
	return (printf_props->format_len);
}

int	ft_handle_char_with_flags(t_printf *printf_props, char c)
{
	char	*temp;

	temp = NULL;
	if (c == 0)
	{
		printf_props->flags->width -= 1;
		temp = ft_update_str(printf_props, ft_strjoin("", ""));
		if (printf_props->flags->minus)
		{
			printf_props->format_len += write(1, &c, 1);
			ft_print_str(printf_props, temp);
		}
		else
		{
			ft_print_str(printf_props, temp);
			printf_props->format_len += write(1, &c, 1);
		}
		return (printf_props->format_len);
	}
	else
		temp = ft_append_char_to_str("", c, 1);
	return (ft_print_str(printf_props, temp));
}

void	*ft_print_percent_sign(t_printf *printf_props)
{
	printf_props->specifier = '%';
	ft_print_char(printf_props, '%');
	return (printf_props);
}
