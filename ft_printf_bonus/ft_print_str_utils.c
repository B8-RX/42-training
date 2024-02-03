/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 02:01:02 by ssghioua          #+#    #+#             */
/*   Updated: 2024/02/03 02:01:05 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_justify_right(t_printf *printf_props, char *str, char *infill)
{
	char	*new;

	if (printf_props -> negative_nbr && printf_props -> flags -> zero)
		new = ft_handle_minus(str, infill);
	else if (ft_strchr("di", printf_props -> specifier)
		&& printf_props -> flags -> plus && printf_props -> flags -> zero)
		new = ft_handle_plus(str, infill);
	else
	{
		new = ft_strjoin(infill, str);
		free(str);
	}
	free(infill);
	return (new);
}

char	*ft_justify_left(char *str, char *infill)
{
	char	*new;

	new = ft_strjoin(str, infill);
	free(str);
	free(infill);
	return (new);
}

char	*ft_handle_minus(char *str, char *infill)
{
	char	*new;

	new = ft_substr(str, 1, ft_strlen(str) - 1);
	free(str);
	str = ft_strjoin(infill, new);
	free(new);
	new = ft_strjoin("-", str);
	free(str);
	return (new);
}

char	*ft_handle_plus(char *str, char *infill)
{
	char	*new;

	new = ft_substr(str, 1, ft_strlen(str) - 1);
	free(str);
	str = ft_strjoin(infill, new);
	free(new);
	new = ft_strjoin("+", str);
	free(str);
	return (new);
}

char	*ft_handle_precision(t_printf *printf_props, char *str)
{
	char	*temp;
	int		precision;

	precision = printf_props -> flags -> precision;
	if (precision && ft_strchr("sc", printf_props -> specifier))
	{	
		temp = ft_substr(str, 0, precision);
		free(str);
		str = ft_strjoin(temp, "");
		free(temp);
	}
	return (str);
}
