/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 03:07:03 by ssghioua          #+#    #+#             */
/*   Updated: 2024/01/29 03:07:07 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


char *ft_append_char_str(char *str, char c, int position)
{
	char	*new;
	int		i;

	if (!str || !c)
		return (NULL);
	new = malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!new)
		return (NULL);
	i = -1;
	if (position == 1)
	{
		new[i + 1] = c;
		while(str[++i])
			new[i + 1] = str[i];
		new[i + 1] = '\0';
	}	
	else
	{
		while(str[++i])
			new[i] = str[i];
		new[i] = c;
		new[i + 1] = '\0';
	}
	return (new);
}

char	*ft_fill_ul_str(t_printf *printf_props, unsigned long nb, char *res)
{
	char	*base;
	char	*temp;

	base = printf_props -> base;
	while (nb >= ft_strlen(base))
	{
		temp = ft_append_char_str(res, base[nb % ft_strlen(base)], 1);
		free(res);
		res = ft_strjoin(temp, "");
		free(temp);
		nb /= ft_strlen(base);
	}
	temp = ft_append_char_str(res, base[nb % ft_strlen(base)], 1);
	free(res);
	res = ft_strjoin(temp, "");
	free(temp);
	if (printf_props -> specifier == 'p')
	{
		temp = ft_strjoin("0x", res);
		free(res);
		res = ft_strjoin(temp, "");
		free(temp);
	}
	return (res);
}

char	*ft_ultoa(t_printf *printf_props, unsigned long n)
{
	char	*res;
	
	if (n == 0)
		return (ft_strjoin("0", ""));
	res = ft_strjoin("", "");
	return (ft_fill_ul_str(printf_props, n, res));
}
