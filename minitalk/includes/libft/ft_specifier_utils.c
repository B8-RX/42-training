/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 07:12:27 by ssghioua          #+#    #+#             */
/*   Updated: 2024/02/06 07:12:29 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_handle_s_specifier(t_printf *printf_props)
{
	char	*output;
	int		width;
	int		period;
	int		precision;

	width = printf_props->flags->width;
	period = printf_props->flags->period;
	precision = printf_props->flags->precision;
	output = (char *)va_arg(printf_props->args, void *);
	if (output == NULL)
	{
		if ((!width && !precision && period)
			|| (!width && precision && precision < (int)ft_strlen("(null)"))
			|| (width && period && precision < (int)ft_strlen("(null)")))
			ft_print_str(printf_props, ft_strjoin("", ""));
		else
			ft_print_str(printf_props, ft_strjoin("(null)", ""));
	}
	else
		ft_print_str(printf_props, ft_strjoin(output, ""));
}
