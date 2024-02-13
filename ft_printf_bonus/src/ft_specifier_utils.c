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

#include "./lib/ft_printf.h"

void	ft_handle_s_specifier(t_printf *printf_props)
{
	char	*output;

	output = (char *)va_arg(printf_props->args, void *);
	if (output == NULL)
	{
		printf_props->updated = 1;
		if ((printf_props->flags_len >= 1) && !printf_props->flags->precision)
			ft_print_str(printf_props, ft_strjoin("", ""));
		else
			ft_print_str(printf_props, ft_strjoin("(null)", ""));
	}
	else
		ft_print_str(printf_props, ft_strjoin(output, ""));
}
