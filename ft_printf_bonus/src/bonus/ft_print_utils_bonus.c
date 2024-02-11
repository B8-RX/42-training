/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 02:01:02 by ssghioua          #+#    #+#             */
/*   Updated: 2024/02/03 02:01:05 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/ft_printf.h"

char	*ft_justify_infill_left(t_printf *props, char *str, char *infill)
{
	char	*new;

	new = ft_strjoin(infill, str);
	free(str);
	free(infill);
	props->updated = 1;
	return (new);
}

char	*ft_justify_infill_right(t_printf *props, char *str, char *infill)
{
	char	*new;

	new = ft_strjoin(str, infill);
	free(str);
	free(infill);
	props->updated = 1;
	return (new);
}

char	*ft_slice_str(t_printf *props, char *str)
{
	char	*temp;
	int		precision;

	precision = props->flags->precision;
	if (precision == -1)
		temp = ft_substr(str, ft_strlen(str) - 1, ft_strlen(str) - 1);
	else
		temp = ft_substr(str, 0, precision);
	free(str);
	str = ft_strjoin(temp, "");
	free(temp);
	return (str);
}

char	*ft_append_prefix(t_printf *props, char *str)
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
	if (props->flags->blank && !props->negative_nbr)
	{
		if (str)
		{
			new = ft_strjoin(str, "");
			free(str);
		}
		str = ft_strjoin(" ", new);
		free(new);
		new = ft_strjoin(str, "");
		free(str);
	}
	return (new);
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
