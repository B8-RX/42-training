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

#include "ft_printf.h"

int	ft_print_str(char *str, int size, int flags)
{
	if (!str)
		return (ft_print_str("(null)", size, flags));
	while (*str != '\0')
	{
		size += write(1, &*str, 1);
		str++;
	}
	return (size);
}
