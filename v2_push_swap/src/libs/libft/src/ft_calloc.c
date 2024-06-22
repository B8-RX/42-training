/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:04:13 by ssghioua          #+#    #+#             */
/*   Updated: 2023/11/21 01:50:22 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	*ft_calloc(size_t nbitems, size_t size)
{
	void	*res;
	size_t	total_size;

	if (size != 0 && nbitems > (size_t)(-1) / size)
		return (NULL);
	total_size = nbitems * size;
	res = (void *)malloc(total_size);
	if (res == NULL)
		return (res);
	ft_bzero(res, total_size);
	return (res);
}
