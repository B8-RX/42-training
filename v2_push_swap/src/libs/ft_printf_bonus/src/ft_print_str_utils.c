/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 02:01:02 by ssghioua          #+#    #+#             */
/*   Updated: 2024/02/03 02:01:05 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lib/ft_printf.h"

char	*ft_justify_infill_left(t_printf *props, char *str, char *infill)
{
	char	*new;
	int		str_len;
	int		prefix_parity;
	int		prefix_hexa;

	str_len = (int)ft_strlen(str);
	prefix_parity = 0;
	prefix_hexa = 0;
	if (props->flags->plus || props->negative_nbr)
		prefix_parity = 1;
	if (props->specifier == 'p'
		|| (props->flags->sharp && !props->error_format))
		prefix_hexa = 1;
	if (prefix_parity || prefix_hexa)
	{
		if (props->flags->zero)
			infill = ft_append_parity(props, infill);
		else if (prefix_hexa)
			str = ft_append_prefix_hexa(props, str);
		else
			str = ft_append_parity(props, str);
	}
	new = ft_strjoin(infill, str);
	return (free(str), free(infill), new);
}

char	*ft_justify_infill_right(t_printf *props, char *str, char *infill)
{
	char	*new;

	new = ft_strjoin(str, infill);
	free(str);
	free(infill);
	if (props->negative_nbr || props->flags->plus)
		new = ft_append_parity(props, new);
	return (new);
}

char	*ft_slice_str(t_printf *props, char *str)
{
	char	*temp;
	int		precision;

	precision = props->flags->precision;
	if (precision == -1)
		temp = ft_strjoin("", "");
	else
		temp = ft_substr(str, 0, precision);
	free(str);
	str = ft_strjoin(temp, "");
	free(temp);
	return (str);
}
