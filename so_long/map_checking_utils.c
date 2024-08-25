/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:26:52 by ssghioua          #+#    #+#             */
/*   Updated: 2024/07/17 09:26:54 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

bool	is_duplicate(t_map **map_data, char item)
{
	t_map	*data;

	data = *map_data;
	if (item == 'P')
		data -> player += 1;
	if (item == 'E')
		data -> exit += 1;
	if (item == 'C')
		data -> collectibles += 1;
	if (data -> player > 1 || data -> exit > 1)
		return (true);
	return (false);
}

bool	is_visited_cell(t_pair queue[], size_t pos_x, size_t pos_y)
{
	int		i;
	int		is_visited;

	i = 0;
	is_visited = 0;
	while (queue[i].visited != -1)
	{
		if ((queue[i].y == pos_y && queue[i].x == pos_x))
		{
			is_visited = 1;
			break ;
		}	
		i++;
	}
	if (is_visited)
		return (true);
	return (false);
}

bool	is_target_or_path(t_map	*data, size_t pos_x, size_t pos_y, char target)
{
	char	**matrix;
	char	curr_item;

	if (!data)
		return (false);
	matrix = data -> matrix;
	curr_item = matrix[pos_y][pos_x];
	if (pos_y > 0 && pos_y < (data -> total_rows) && pos_x > 0
		&& pos_x < (data -> total_cols) && (curr_item == '0'
			|| curr_item == target || curr_item == 'E'))
		return (true);
	return (false);
}

void	update_position(size_t *pos_x, size_t *pos_y, char *direction)
{
	if (!pos_x || !pos_y || !direction)
		return ;
	if (ft_strncmp(direction, "down", ft_strlen(direction)) == 0)
		(*pos_y)++;
	else if (ft_strncmp(direction, "up", ft_strlen(direction)) == 0)
		(*pos_y)--;
	else if (ft_strncmp(direction, "right", ft_strlen(direction)) == 0)
		(*pos_x)++;
	else if (ft_strncmp(direction, "left", ft_strlen(direction)) == 0)
		(*pos_x)--;
}

void	check_file(t_game *game, char *file_name)
{
	int		i;
	int		fd;
	size_t	len;

	i = 0;
	len = ft_strlen(file_name) - 4;
	if (ft_strlen(file_name) < 5 || ft_strncmp(file_name + len, ".ber", 4))
		return (handle_errors(game, ERR_MAP_FORMAT));
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (handle_errors(game, ERR_MAP_NOT_FOUND));
	else
		close(fd);
	return ;
}
