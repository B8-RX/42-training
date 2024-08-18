/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 03:55:36 by ssghioua          #+#    #+#             */
/*   Updated: 2024/02/01 03:55:39 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*new;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcpy(new, s + start, len + 1);
	return (new);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int		len_src;
	size_t	i;

	i = 0;
	len_src = ft_strlen(src);
	if (!dst || !src)
		return (0);
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len_src);
}
