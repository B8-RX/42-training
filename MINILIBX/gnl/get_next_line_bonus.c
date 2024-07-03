/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:03:21 by ssghioua          #+#    #+#             */
/*   Updated: 2023/12/30 16:03:24 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_stash	*stash;
	t_fd_node		*curr_fd_node;
	char			*line;
	int				i;

	if (fd < 0 || !BUFFER_SIZE || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash && !ft_init_stash(&stash, fd))
		return (NULL);
	curr_fd_node = ft_handle_fd(&stash, fd)->fd_node;
	if (!curr_fd_node)
		return (NULL);
	if (!ft_read_file(&stash, fd))
		return (NULL);
	line = ft_get_line(curr_fd_node);
	i = 0;
	while (line[i])
		i++;
	curr_fd_node = ft_update_fd_node(curr_fd_node, "", i);
	return (line);
}

t_stash	*ft_create_fd_node(t_stash **stash, int fd)
{
	t_stash	*current;
	t_stash	*updated_stash;

	updated_stash = *stash;
	current = malloc(sizeof(t_stash));
	if (!current)
		return (NULL);
	current->fd_node = malloc(sizeof(t_fd_node));
	if (!current->fd_node)
		return (free(current), NULL);
	while (updated_stash->next != NULL)
		updated_stash = updated_stash->next;
	current->fd_node->fd = fd;
	current->fd_node->buffer = malloc(1);
	if (!(current->fd_node->buffer))
		return (free(current->fd_node), NULL);
	*(current->fd_node->buffer) = '\0';
	current->next = NULL;
	updated_stash->next = current;
	return (updated_stash->next);
}

t_stash	*ft_read_file(t_stash **stash, int fd)
{
	ssize_t		read_bytes;
	char		*temp_buffer;
	t_fd_node	*curr_fd_node;

	curr_fd_node = ft_handle_fd(stash, fd)->fd_node;
	temp_buffer = malloc(BUFFER_SIZE + 1);
	if (!temp_buffer)
		return (NULL);
	temp_buffer[0] = '\0';
	read_bytes = 1;
	while (read_bytes && !ft_strchr(temp_buffer, '\n'))
	{
		read_bytes = read(fd, temp_buffer, BUFFER_SIZE);
		if ((read_bytes == 0
				&& *(curr_fd_node->buffer) == '\0') || read_bytes == -1)
			return (ft_release_stash(stash, fd), free(temp_buffer), NULL);
		temp_buffer[read_bytes] = '\0';
		curr_fd_node = ft_update_fd_node(curr_fd_node, temp_buffer, 0);
	}
	return (free(temp_buffer), *stash);
}

t_fd_node	*ft_update_fd_node(t_fd_node *fd_node, char *buff, int len)
{
	char	*old_buffer;
	char	*updated_buffer;

	old_buffer = fd_node->buffer;
	updated_buffer = ft_strjoin(old_buffer + len, buff);
	free(fd_node->buffer);
	fd_node->buffer = NULL;
	fd_node->buffer = ft_strjoin(updated_buffer, "");
	free(updated_buffer);
	updated_buffer = NULL;
	return (fd_node);
}

char	*ft_get_line(t_fd_node *fd_node)
{
	char	*line;
	char	*buffer_line_feed;
	int		buffer_len;
	int		line_len;
	int		i;

	i = 0;
	while ((fd_node->buffer)[i])
		i++;
	buffer_len = i;
	buffer_line_feed = ft_strchr(fd_node->buffer, '\n');
	i = 0;
	while (buffer_line_feed && buffer_line_feed[i])
		i++;
	line_len = buffer_len - i;
	if (buffer_line_feed)
		line_len++;
	line = malloc(line_len + 1);
	i = -1;
	while (++i < line_len)
		line[i] = (fd_node->buffer)[i];
	line[i] = '\0';
	return (line);
}
