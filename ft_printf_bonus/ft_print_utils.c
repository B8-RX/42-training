/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 02:01:02 by ssghioua          #+#    #+#             */
/*   Updated: 2024/02/03 02:01:05 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_justify_infill_left(t_printf *printf_props, char *str, char *infill)
{
	char	*new;

	if (printf_props -> negative_nbr && printf_props -> flags -> zero)
		new = ft_move_sign(printf_props, str, infill);
	else if (ft_strchr("di", printf_props -> specifier)
		&& printf_props -> flags -> plus && printf_props -> flags -> zero)
		new = ft_move_sign(printf_props, str, infill);
	else
	{
		new = ft_strjoin(infill, str);
		free(str);
	}
	free(infill);
	return (new);
}

char	*ft_justify_infill_right(char *str, char *infill)
{
	char	*new;

	new = ft_strjoin(str, infill);
	free(str);
	free(infill);
	return (new);
}

char	*ft_slice_str(t_printf *printf_props, char *str)
{
	char	*temp;
	int		precision;

	precision = printf_props -> flags -> precision;
	temp = ft_substr(str, 0, precision);
	free(str);
	str = ft_strjoin(temp, "");
	free(temp);
	return (str);
}

char	*ft_move_sign(t_printf *printf_props, char *str, char *infill)
{
	char	*new;

	new = ft_substr(str, 1, ft_strlen(str) - 1);
	free(str);
	str = ft_strjoin(infill, new);
	free(new);
	if (printf_props -> negative_nbr && printf_props -> flags -> zero)
		new = ft_strjoin("-", str);
	else
		new = ft_strjoin("+", str);
	free(str);
	return (new);
}

char	*ft_append_char_to_str(char *str, char c, int position)
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
