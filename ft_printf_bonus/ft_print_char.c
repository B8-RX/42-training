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
	int size;
	int	width;
	int	minus;

	width = (*printf_props) -> flags -> width;
	minus = (*printf_props) -> flags -> minus;
	size = 0;
	size += write(1, &c, 1);
	return (size);
}
