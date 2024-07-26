/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 02:31:05 by ssghioua          #+#    #+#             */
/*   Updated: 2023/12/16 02:31:08 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read_file(int fd, char *stash)
{
	char		*buff;
	ssize_t		read_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	buff[0] = '\0';
	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr(buff, '\n'))
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if ((read_bytes <= 0 && !*stash) || read_bytes == -1)
		{
			free(buff);
			free(stash);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		stash = ft_update_stash(stash, buff, 0);
		if (!stash)
		{
			free(buff);
			return (NULL);
		}
	}
	free(buff);
	return (stash);
}

char	*ft_update_stash(char *stash, char *buff, size_t size)
{
	char	*new;

	new = ft_strjoin(stash + size, buff);
	if (stash)
		free(stash);
	stash = NULL;
	return (new);
}

char	*ft_get_line(char *stash)
{
	char	*new;
	size_t	len;

	if (ft_strchr(stash, '\n'))
		len = ft_strlen(stash) - ft_strlen(ft_strchr(stash, '\n')) + 1;
	else
		len = ft_strlen(stash);
	new = ft_substr(stash, 0, len);
	if (!new)
	{
		free(stash);
		return (NULL);
	}
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || !BUFFER_SIZE || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strjoin("", "");
	stash = ft_read_file(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_get_line(stash);
	if (!line)
	{
		free(stash);
		return (NULL);
	}
	stash = ft_update_stash(stash, "", ft_strlen(line));
	return (line);
}
