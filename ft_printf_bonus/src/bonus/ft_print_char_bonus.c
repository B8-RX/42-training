/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 00:00:34 by ssghioua          #+#    #+#             */
/*   Updated: 2024/01/26 00:00:36 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/ft_printf.h"

int	ft_print_char_bonus(t_printf *printf_props, char c)
{
	char	*temp;

	temp = NULL;
	if (printf_props -> flags->width > 1)
	{
		if (c == 0)
		{
			printf_props -> format_len += write(1, &c, 1);
			printf_props -> flags -> width -= 1;
			temp = ft_update_str(printf_props, ft_strjoin("", ""));
		}
		else
			temp = ft_append_char_to_str("", c, 1);
		return (ft_print_str_bonus(printf_props, temp));
	}	
	else
	{
		printf_props -> format_len += write(1, &c, 1);
		return (printf_props -> format_len);
	}
}

void	*ft_print_percent_sign(t_printf *printf_props)
{
	printf_props -> specifier = '%';
	ft_print_char_bonus(printf_props, '%');
	return (printf_props);
}
