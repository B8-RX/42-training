/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:16:08 by ssghioua          #+#    #+#             */
/*   Updated: 2024/01/18 21:16:09 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str(t_printf *props, char *str)
{
	int		i;
	char	*new;
	int		error;

	i = 0;
	error = props->error_format;
	if (!props->updated && (*str || props->flags->width))
	{
		new = ft_update_str(props, str);
		return (ft_print_str(props, new));
	}
	if (ft_strchr("csdiupxX%", props->specifier) || error || *str == '%')
		while (str[i] != '\0')
			props->format_len += write(1, &str[i++], 1);
	free(str);
	return (props->format_len);
}

char	*ft_update_str(t_printf *props, char *str)
{
	char	*new;

	props->updated = 1;
	new = NULL;
	if (props->flags_len || ft_strchr("pxX", props->specifier))
		new = ft_flags_processing(props, str);
	else if (props->negative_nbr)
		new = ft_append_parity(props, str);
	else
		return (str);
	return (new);
}

char	*ft_flags_processing(t_printf *props, char *str)
{
	char	*infill;
	int		precision;
	int		width;

	width = props->flags->width;
	precision = props->flags->precision;
	if (width && props->flags->zero
		&& props->flags->period
		&& props->negative_nbr
		&& ft_atoi_printf(ft_strjoin(str, "")) == 0
		&& ft_strlen(str) == 1)
		props->error_format = 1;
	if (*str && props->flags->period)
		if (precision < (int)ft_strlen(str)
			&& (ft_strchr("sc", props->specifier)
				|| ((ft_atoi_printf(ft_strjoin(str, "")) == 0)
					&& ft_strlen(str) == 1)))
			str = ft_slice_str(props, str);
	infill = ft_set_infill(props, str);
	return (infill);
}
