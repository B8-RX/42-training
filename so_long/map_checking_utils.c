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

bool	is_visited_cell(Pair queue[], size_t pos_x, size_t pos_y)
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
			break;
		}	
		i++;
	}
	if (is_visited)
		return (true);
	return (false);
}

bool	is_target_or_path(t_map	*map_data, size_t pos_x, size_t pos_y, char target)
{
	char	**matrix;
	char	curr_item;
	
	if (!map_data)
		return (false);
	matrix = map_data -> matrix;
	curr_item = matrix[pos_y][pos_x];
	if (pos_y > 0 && pos_y < (map_data -> total_rows) && pos_x > 0 && pos_x < (map_data -> total_cols) && (curr_item == '0' || curr_item == target || curr_item == 'E'))
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

int	check_file(char *file_name)
{
	int		i;
	int		dot;
	char	**ext;
	int		valid_ext;
	int		fd;

	i = 0;
	dot = 0;
	valid_ext = 0;
	while (file_name[i])
	{
		if (file_name[i] == '.' && file_name[i + 1] != '/')
			dot++;
		i++;
	}
	ext = ft_split(file_name, '.');
	if (ext && ft_strncmp(EXT, ext[dot], ft_strlen(EXT)) == 0)
		valid_ext = 1;
	if (!valid_ext)
	{
		ft_putendl_fd_nl("ERROR EXTENSION: SUPPORT ONLY [.ber] FILE AND GET [.", 2);
		ft_putendl_fd_nl(ext[dot], 2);
		ft_putendl_fd("]", 2);
		free_double_array(ext);
		return (ERROR);
	}	
	free_double_array(ext);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (ft_putendl_fd("FILE NOT FOUND", 2), ERROR);
	else
		close(fd);
	return (SUCCESS);
}
