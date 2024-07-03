/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:03:35 by ssghioua          #+#    #+#             */
/*   Updated: 2023/12/30 16:03:36 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_stash	*ft_init_stash(t_stash **stash, int fd)
{
	t_stash	*new;

	new = malloc(sizeof(t_stash));
	if (!new)
		return (NULL);
	new->fd_node = malloc(sizeof(t_fd_node));
	if (!new->fd_node)
		return (free(new), NULL);
	new->fd_node->fd = fd;
	new->fd_node->buffer = malloc(1);
	if (!(new->fd_node->buffer))
		return (free(new->fd_node), free(new), NULL);
	*(new->fd_node->buffer) = '\0';
	new->next = NULL;
	*stash = new;
	return (*stash);
}

t_stash	*ft_handle_fd(t_stash **stash, int fd)
{
	t_stash	*current;

	if (!*stash)
		return (NULL);
	current = *stash;
	while (current != NULL)
	{
		if (current->fd_node->fd == fd)
			return (current);
		current = current->next;
	}
	return (ft_create_fd_node(stash, fd));
}

void	ft_release_stash(t_stash **stash, int fd)
{
	t_stash	*last;
	t_stash	*current;

	current = *stash;
	last = *stash;
	if (current->fd_node->fd == fd)
	{
		*stash = current->next;
		return (free(current->fd_node->buffer),
			free(current->fd_node), free(current));
	}
	while (current != NULL)
	{
		if (current->fd_node->fd == fd)
		{
			last->next = current->next;
			return (free(current->fd_node->buffer),
				free(current->fd_node), free(current));
		}
		current = current->next;
		if (last->next->fd_node->fd != fd)
			last = current;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
		i++;
	j = 0;
	while (s2[j] != '\0')
		j++;
	new = (char *)malloc((i + j + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		new[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		new[i++] = s2[j];
	new[i] = '\0';
	return (new);
}

char	*ft_strchr(char *s, int c)
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
