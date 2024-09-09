/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:13:18 by ssghioua          #+#    #+#             */
/*   Updated: 2023/11/23 05:39:25 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_first_indx(const char *s1, const char *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	return (i);
}

size_t	ft_last_indx(const char *s1, const char *set)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	while (len - 1 > i && ft_strchr(set, s1[(len - 1) - i]))
		i++;
	return (len - i);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char		*newstr;
	size_t		first_indx;
	size_t		last_indx;

	if (!s1 || !set)
		return (NULL);
	first_indx = ft_first_indx(s1, set);
	last_indx = ft_last_indx(s1, set);
	if (first_indx >= last_indx)
		return (ft_strdup(""));
	newstr = (char *) malloc((last_indx - first_indx) + 1);
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s1 + first_indx, last_indx - first_indx + 1);
	return (newstr);
}
