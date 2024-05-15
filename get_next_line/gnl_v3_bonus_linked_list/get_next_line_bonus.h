/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:03:11 by ssghioua          #+#    #+#             */
/*   Updated: 2023/12/30 16:03:14 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 55 
# endif // !BUFFER_SIZE

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct fd_stash {
	int		fd;
	char	*buffer;
}	t_fd_node;

typedef struct s_stash {
	t_fd_node		*fd_node;
	struct s_stash	*next;
}	t_stash;

char		*get_next_line(int fd);
t_stash		*ft_init_stash(t_stash **stash, int fd);
t_stash		*ft_handle_fd(t_stash **stash, int fd);
t_stash		*ft_create_fd_node(t_stash **stash, int fd);
t_stash		*ft_read_file(t_stash **stash, int fd);
t_fd_node	*ft_update_fd_node(t_fd_node *fd_node,
			char *buff, int len);
void		ft_release_stash(t_stash **stash, int fd);
char		*ft_get_line(t_fd_node *fd_node);
char		*ft_substr(char *s, unsigned int start, size_t len);
char		*ft_strchr(char *s, int c);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlen(char *s);
size_t		ft_strlcpy(char *dst, char *src, size_t size);
size_t		ft_strlcat(char *dst, char *src, size_t size);

#endif // !GET_NEXT_LINE_H
