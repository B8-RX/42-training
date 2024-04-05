/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 01:26:18 by ssghioua          #+#    #+#             */
/*   Updated: 2024/04/05 01:26:20 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./push_swap.h"

char	**ft_split(char *str, char splitter)
{	

	char	**parent_array;  
	int		total_words;
	int		i;
	int		index_child;

	total_words = ft_count_words(str, splitter);
	parent_array = malloc(total_words * sizeof(char*) + sizeof(void*));
	if (!parent_array)
		return (NULL);
	parent_array[total_words] = NULL;
	i = 0;
	index_child = 0;
	while (str[i] != '\0' && total_words > 0)
	{		
		i+= ft_count_spaces(str + i);
		if (!ft_count_value_len(str + i))
			return (ft_print_error(), NULL);
		parent_array[index_child] = malloc (ft_count_value_len(str + i) + 1);
		if (!parent_array[index_child])
			return (ft_free_parent_array(parent_array));
		i += ft_push_value(parent_array[index_child], str + i, splitter);
		index_child++;
		total_words--;
	}
	return (parent_array);
}

int	ft_push_value(char *parent_array, char *value, char spliter)
{
	int	index_child_value;
	int	i;

	i = 0;
	index_child_value = 0;
	while ( value[i] && value[i] != spliter)
	{
		parent_array[index_child_value] = value[i];
		i++;
		index_child_value++;
	}
	parent_array[index_child_value] = '\0';
	return (i);
}

void	*ft_free_parent_array(char **parent_array)
{

	int	index_child;

	printf("ERROR MALLOC\n");
	index_child = 0;
	while (parent_array[index_child])
	{
		free(parent_array[index_child]);
		index_child++;
	}
	free(parent_array);
	return (NULL);
}

int	ft_count_words(char *str, char splitter)
{
	int		i;
	int		words;
	int		blank;
	
	i = -1;
	blank = 0;

	// if (!str)
		// return ft_print_error(); ?
	
	if (*str && *str == splitter)
		words = 0;
	else
		words = 1;
	while (str[++i] != '\0')
	{
		while (str[i + blank] == splitter)
			blank++;
		if (blank > 1)
			i+= blank - 1;
		if (blank && str[i] && str[i + 1] != '\0')
			words++;
		blank = 0;
	}
	return words;
}
