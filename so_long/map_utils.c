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

char	*to_string(t_game *game, char *map_path)
{
	char	*temp;
	char	*line;
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (ft_putendl_fd("ERROR OPEN FILE", 2), NULL);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), NULL);
	if (ft_strlen(line) == 1)
		return (free(line), close(fd), NULL);
	game -> map_data -> str_map = ft_strjoin("", "");
	if (!game -> map_data -> str_map)
		return (close(fd), NULL);
	while (line)
	{
		temp = ft_strjoin(game -> map_data -> str_map, line);
		if (!temp)
		{
			if (line)
				free(line);
			return (close(fd), NULL);
		}
		free(game -> map_data -> str_map);
		game -> map_data -> str_map = temp;
		free(line);
		line = get_next_line(fd);
	}
	if (!*(game -> map_data -> str_map))
		return (close(fd), NULL);
	if (close(fd) == -1)
		return (ft_putendl_fd("ERROR CLOSE FILE", 2), free(game -> map_data -> str_map), NULL);
	return (game -> map_data -> str_map);
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

