/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:27:40 by ssghioua          #+#    #+#             */
/*   Updated: 2023/11/23 03:42:35 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*source;
	unsigned char	*res;
	size_t			i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	source = (unsigned char *)src;
	res = (unsigned char *)dest;
	if (res > source)
		while (n-- > 0)
			res[n] = source[n];
	else
	{
		while (i < n)
		{
			res[i] = source[i];
			i++;
		}
	}
	return (res);
}
