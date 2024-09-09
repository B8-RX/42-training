/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:29:42 by ssghioua          #+#    #+#             */
/*   Updated: 2023/11/23 04:29:48 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	if (!s1 && len == 0)
		return (NULL);
	if (ft_strlen(s2) == 0)
		return ((char *)s1);
	i = 0;
	while (s1[i] && len > i)
	{
		j = 0;
		while (s2[j] && s1[i + j] == s2[j] && i + j <= len - 1)
			j++;
		if (j == ft_strlen(s2))
			return ((char *)(s1 + i));
		i++;
	}
	return (NULL);
}
