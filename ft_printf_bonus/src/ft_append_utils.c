/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 02:27:19 by ssghioua          #+#    #+#             */
/*   Updated: 2024/02/17 02:27:20 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lib/ft_printf.h"

char	*ft_append_blank(t_printf *props, char *src)
{
	char	*new;

	if (!props->negative_nbr)
	{
		new = ft_strjoin(" ", src);
		free(src);
		return (new);
	}
	return (src);
}

char	*ft_append_parity(t_printf *props, char *str)
{
	char	*new;

	if (props->flags->plus || props->negative_nbr)
	{
		if (props->negative_nbr)
			new = ft_strjoin("-", str);
		else
			new = ft_strjoin("+", str);
		free(str);
		str = NULL;
	}
	if (!(props->flags->plus || props->negative_nbr))
		return (str);
	return (new);
}

char	*ft_append_prefix_hexa(t_printf *printf_props, char *str)
{
	char	*temp;
	int		valid_hexa;
	int		error;

	valid_hexa = 0;
	error = printf_props->error_format;
	if ((*str == 0 && ft_strlen(str) > 1) || *str != '0')
		valid_hexa = 1;
	if (ft_strchr("pxX", printf_props->specifier) && valid_hexa && !error)
	{
		if (printf_props->specifier == 'X')
			temp = ft_strjoin("0X", str);
		else
			temp = ft_strjoin("0x", str);
		free(str);
		str = ft_strjoin(temp, "");
		free(temp);
	}
	return (str);
}

char	*ft_append_char_to_str(char *str, char c, int position)
{
	char	*new;
	int		i;

	if (!str || (!c && c != 0))
		return (NULL);
	new = malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!new)
		return (NULL);
	i = -1;
	if (position == 1)
	{
		new[i + 1] = c;
		while (str[++i])
			new[i + 1] = str[i];
		new[i + 1] = '\0';
	}	
	else
	{
		while (str[++i])
			new[i] = str[i];
		new[i] = c;
		new[i + 1] = '\0';
	}
	return (new);
}

char	*ft_bzero(int size)
{
	int		i;
	char	*temp;
	char	*infill;

	i = 0;
	infill = ft_strjoin("", "");
	while (i < size)
	{
		temp = ft_strjoin(infill, "");
		free(infill);
		infill = ft_strjoin("0", temp);
		free(temp);
		i++;
	}
	return (infill);
}
