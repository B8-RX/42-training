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

#include "ft_printf.h"

int	ft_print_char(t_printf **printf_props, char c)
{
	char	*res;

	res = malloc(sizeof(char) + 1);
	res[0] = c;
	res[1] = '\0';
	
	return (ft_print_str(*printf_props, res));
}
