/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:00:24 by ssghioua          #+#    #+#             */
/*   Updated: 2023/11/23 05:35:24 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*res;
	unsigned char	*source;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	res = (unsigned char *)dest;
	source = (unsigned char *)src;
	while (n > 0)
	{
		res[i] = source[i];
		i++;
		n--;
	}
	return (res);
}
