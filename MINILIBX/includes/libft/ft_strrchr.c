/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:53:18 by ssghioua          #+#    #+#             */
/*   Updated: 2023/11/19 04:40:37 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	len_str;

	len_str = ft_strlen(str);
	while (len_str >= 0)
	{
		if (*(unsigned char *)(str + len_str) == (unsigned char)c)
			return ((char *)str + len_str);
		len_str--;
	}
	if (c == '\0')
		return ((char *)str + (ft_strlen(str) + 1));
	return ((void *)0);
}
