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

char	*stringify(char *map_path)
{
	char	*map;
	char	*temp;
	char	*line;
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (printf("ERROR OPEN FILE\n"), NULL);
	else
		printf("FILE OPENED SUCCESSFULLY\n");
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	map = ft_strjoin("", "");
	while (line)
	{
		temp = ft_strdup(map);
		free(map);
		map = ft_strjoin(temp, line);
		free(temp);
		free(line);
		line = get_next_line(fd);
	}
	printf("%s", map);
	if (close(fd) == -1)
		return (printf("ERROR CLOSE FILE\n"), NULL);
	else
		printf("FILE CLOSED SUCCESSFULLY\n");
	return (map);
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

