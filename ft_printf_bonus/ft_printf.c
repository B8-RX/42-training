/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:05:22 by ssghioua          #+#    #+#             */
/*   Updated: 2024/01/16 11:05:26 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(char *format, ...)
{
	t_printf	*printf_properties;
	int			count;
	int			i;

	printf_properties = malloc(sizeof(t_printf));
	if (!printf_properties)
		return (0);
	va_start(printf_properties -> args, format);
	count = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			if (!ft_strchr("scdiupxX%.0123456789# -+", format[i + 1]))
			{
				count += write(1, &format[i], 1);	
				return (count);
			}
			printf_properties = ft_init_printf_props(printf_properties);
			ft_handle_format(&printf_properties, &format[++i]);
			count += printf_properties -> step;
			if (!ft_strchr("scdiupxX%", format[i]))
				i += printf_properties -> flags_len;
			i++;
			free(printf_properties -> flags);
			printf_properties -> flags = NULL;
			}
		else 
		{
			count += write(1, &format[i], 1);
			i++;
		}
	}
	va_end(printf_properties -> args);
	free(printf_properties);
	printf_properties = NULL;
	return (count);
}

t_printf	*ft_init_printf_props(t_printf *printf_props)
{
	printf_props -> flags = malloc(sizeof(t_flags));
	if (!printf_props -> flags)
	{
		free(printf_props);
		return (0);
	}
	printf_props -> step = 0;
	printf_props -> flags_len = 0;
	printf_props -> flags -> period = 0;
	printf_props -> flags -> precision = 0;
	printf_props -> flags -> blank = 0;
	printf_props -> flags -> zero = 0;
	printf_props -> flags -> hashtag = 0;
	printf_props -> flags -> plus = 0;
	printf_props -> flags -> minus = 0;
	printf_props -> flags -> width = 0;
	return (printf_props);
}
t_printf	*ft_check_special_flags(t_printf **printf_props, char *format)
{	
	int			i;
	int			j;

	i = 0;
	while (!ft_strchr("csdiupxX", format[i]))
	{
		if (format[i] == '-')
		{
			(*printf_props) -> flags -> minus = 1;
			i++;
		}
		if (format[i] == '.')
		{
			(*printf_props) -> flags -> period = 1;
			i++;
		}
		if (format[i] > '0' && format[i] <= '9')
		{
			j = 0;
			while (format[i + j] > '0' && format[i + j] <= '9')
				j++;
			if ((*printf_props) -> flags -> period)
				(*printf_props) -> flags -> precision = ft_atoi(ft_substr(format + i, 0, j));
			else
				(*printf_props) -> flags -> width = ft_atoi(ft_substr(format + i, 0, j));
			i += j;
		}
		if (format[i] == ' ')
		{
			(*printf_props) -> flags -> blank = 1;
			i++;
		}
		if (format[i] == '0')
		{
			j = 0;
			(*printf_props) -> flags -> zero = 1;
			while (format[i + j] == '0')
				j++;
			i += j;
		}
		if (format[i] == '#')
		{
			(*printf_props) -> flags -> hashtag = 1;
			i++;
		}
		if (format[i] == '+')
		{
			(*printf_props) -> flags -> plus = 1;
			i++;
		}
		(*printf_props) -> flags_len = i;
	}
	return (*printf_props);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*(s + i))
	{
		if (*(unsigned char *)(s + i) == (unsigned char)c)
			return ((char *)(s + i));
		i++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	return (NULL);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
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

size_t	ft_strlcpy(char *dst, char *src, size_t size)
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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
		j++;
	new = (char *)malloc((i + j + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = -1;
	while (s2[++j])
		new[i++] = s2[j];
	new[i] = '\0';
	return (new);
}
