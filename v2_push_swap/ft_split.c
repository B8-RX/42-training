/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 01:26:18 by ssghioua          #+#    #+#             */
/*   Updated: 2024/05/16 18:02:54 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/push_swap.h"

char	**split(char *str, const char splitter)
{

	char	**array;  
	int		child;
	int		words;

	words = count_words(str, splitter);
	array = malloc(words * sizeof(char*) + sizeof(void*));
	if (!array)
		return (NULL);
	array[words] = NULL;
	child = 0;
	while (*str != '\0')
	{	
		str += count_spaces(str);
		if (*str != '\0')
		{
			array[child] = malloc(get_len_value(str) + 1);
			if (!array[child])
				return (free_array_str(array));
			str += append_child(array[child], str, splitter);
			child++;
		}
	}
	return (array);
}

int	append_child(char *child, const char *value, const char splitter)
{
	int	i;

	i = 0;
	while (value[i] && value[i] != splitter)
	{
		child[i] = value[i];
		i++;
	}
	child[i] = '\0';
	return (i);
}

int	count_words(const char *str, const char splitter)
{
	int		i;
	int		words;
	
	i = 0;
	words = 0;
	while (str[i] != '\0')
	{
		while (str[i] == splitter)
			i++;
		if (str[i])
		{
			while (str[i] && str[i] != splitter)
				i++;
			words++;
		}
	}
	return words;
}
