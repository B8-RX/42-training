/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 04:08:27 by ssghioua          #+#    #+#             */
/*   Updated: 2023/11/27 04:24:54 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_childs(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			j++;
		}
		else
			while (s[i] == c)
				i++;
	}
	return (j);
}

int	ft_check_child_index(const char *s, char c)
{
	int	i;
	int	s_len;

	i = 0;
	s_len = ft_strlen(s);
	while (s_len && s[i] == c)
	{
		i++;
		s_len--;
	}
	return (i);
}

int	ft_check_child_len(const char *s, char c)
{
	int	i;
	int	s_len;

	i = 0;
	s_len = ft_strlen(s);
	while (s_len && s[i] != c)
	{
		i++;
		s_len--;
	}
	return (i);
}

void	*ft_memory_error(char **parent, int index)
{
	while (index + 1 > 0)
	{
		free(parent[index]);
		index--;
	}
	free(parent);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char		**parent;
	int			nb_childs;
	int			child_len;
	int			parent_index;

	parent = NULL;
	if (!s)
		return ((NULL));
	nb_childs = ft_count_childs(s, c);
	parent = (char **) malloc(sizeof(char *) * (nb_childs + 1));
	if (!parent)
		return (parent);
	parent_index = -1;
	while (*s && ++parent_index < nb_childs)
	{
		s += ft_check_child_index(s, c);
		child_len = ft_check_child_len(s, c);
		parent[parent_index] = malloc(child_len * sizeof(char) + 1);
		if (!parent[parent_index])
			return (ft_memory_error(parent, parent_index));
		ft_strlcpy(parent[parent_index], s, child_len + 1);
		s += child_len;
	}
	parent[nb_childs] = 0;
	return (parent);
}
