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
	static char		*stash;
	static int		calls = 0;
	char			*line;

	calls++;
	if (fd < 0 || !BUFFER_SIZE || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strjoin("", "");
	stash = ft_read_file(fd, stash);
	if (!stash)
		return (NULL);
	if (calls == 1 && ft_strlen(stash) < 2)
		return (free(stash), NULL);
	line = ft_get_line(stash);
	if (!line)
	{
		free(stash);
		return (NULL);
	}
	stash = ft_update_stash(stash, "", ft_strlen(line));
	return (line);
}
/*static char	*	ft_strjoin2(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (join == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		join[i] = s1[i];
	j = -1;
	while (s2[++j])
		join[i++] = s2[j];
	join[i] = '\0';
	free((char *)s1);
	return (join);
}

static void	cleanup(char *line, char *keep)
{
	int	i;
	int	j;
	int	end;

	j = 0;
	i = 0;
	while (line[i] != '\n' && line[i])
		i++;
	end = i + 1;
	while (line[i++])
	{
		keep[j] = line[i];
		j++;
	}
	line[end] = '\0';
	keep[j] = '\0';
	return ;
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	keep[BUFFER_SIZE + 1] = {0};

	line = NULL;
	if (keep[0] != 0)
	{
		line = ft_strdup(keep);
		if (ft_strchr(line, '\n'))
			return (cleanup(line, keep), line);
	}
	ft_bzero(keep, BUFFER_SIZE + 1);
	while (read(fd, keep, BUFFER_SIZE) > 0)
	{
		if (!line)
			line = ft_strdup("");
		line = ft_strjoin2(line, keep);
		if (ft_strchr(line, '\n') || ft_strchr(line, '\0'))
			return (cleanup(line, keep), line);
		ft_bzero(keep, BUFFER_SIZE + 1);
	}
	return (line);
}*/
