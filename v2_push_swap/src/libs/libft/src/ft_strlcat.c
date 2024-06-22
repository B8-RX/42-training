/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:57:35 by ssghioua          #+#    #+#             */
/*   Updated: 2023/11/23 04:25:10 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dst;

	if (!dst && size == 0)
		return (0);
	len_dst = ft_strlen(dst);
	if (size && len_dst < size - 1)
	{
		i = 0;
		while (src[i] && (len_dst + i < size - 1))
		{
			dst[len_dst + i] = src[i];
			i++;
		}
		dst[len_dst + i] = '\0';
	}
	if (len_dst >= size)
		return (size + ft_strlen(src));
	else
		return (len_dst + ft_strlen(src));
}
