/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:21:46 by ssghioua          #+#    #+#             */
/*   Updated: 2024/07/17 09:21:49 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

static void	append_next_line(t_game *game, int fd, char **line)
{
	char	*temp;

	temp = ft_strjoin(game -> map_data -> str_map, *line);
	if (!temp)
	{
		if (*line)
			free(*line);
		close(fd);
		return ;
	}
	free(game -> map_data -> str_map);
	game -> map_data -> str_map = temp;
	free(*line);
	*line = get_next_line(fd);
}

int	map_to_string(t_game *game, char *map_path)
{
	char	*line;
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (ft_putendl_fd("ERROR OPEN FILE", 2), ERROR);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), ERROR);
	if (ft_strlen(line) == 1)
		return (free(line), close(fd), ERROR);
	game -> map_data -> str_map = ft_strjoin("", "");
	while (line)
		append_next_line(game, fd, &line);
	if (!*(game -> map_data -> str_map))
		return (close(fd), ERROR);
	if (close(fd) == -1)
		return (ft_putendl_fd("ERROR CLOSE FILE", 2),
			free(game -> map_data -> str_map), ERROR);
	return (SUCCESS);
}

int	get_total_rows(t_map *map_data)
{
	size_t	row;
	char	**matrix;

	matrix = map_data -> matrix;
	row = 0;
	while (matrix[row])
		row++;
	return (row);
}
