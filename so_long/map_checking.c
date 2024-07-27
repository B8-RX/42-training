/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:14:40 by ssghioua          #+#    #+#             */
/*   Updated: 2024/07/17 09:14:43 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

int verify_map(t_game **game, char *map_path)
{
	t_map	*map_data;

	if (init_map(game, map_path) == ERROR)
		return (ERROR);
	map_data = (*game) -> map_data;
	if (check_map_size(*game) == ERROR
		|| is_map_square(map_data) == false
		|| is_valid_walls(map_data) == false
		|| is_valid_fill(&map_data) == false
		|| is_valid_player_path(&map_data) == false)
		return (ERROR);
	return (SUCCESS);
}

int	check_map_size(t_game *game)
{
	if (game -> map_data -> total_cols * 128 >= (unsigned int)game -> screen_width - 128 ||
		game -> map_data -> total_rows * 128 >= (unsigned int)game -> screen_height - 128)
	{
		ft_putendl_fd("ERROR MAP TOO BIG", 2);
		return (ERROR);
	}
	printf("TOTAL SIZE IMG x_axe: %zu\n", game -> map_data-> total_cols * 128);
	printf("TOTAL SIZE IMG y_axe: %zu\n", game -> map_data-> total_rows * 128);
	if (game -> map_data -> total_cols  < 3 ||
		game -> map_data -> total_rows  < 3)
	{
		ft_putendl_fd("ERROR MAP TOO SMALL", 2);
		return (ERROR);
	}
	return (SUCCESS);
}

bool	is_map_square(t_map *map_data)
{
	size_t	first_row_len;
	char	**matrix;
	int		i;

	i = 0;
	matrix = map_data -> matrix;
	first_row_len = ft_strlen(matrix[i++]);
	while (matrix[i])
	{
		if (ft_strlen(matrix[i]) != first_row_len)
		{
			ft_putendl_fd("ERROR MAP NOT SQUARE", 2);
			return (false);
		}
		i++;
	}
	printf("VALID SQUARE\n");
	return (true);
}

bool	is_valid_walls(t_map *map_data)
{
	size_t	col;
	size_t	row;
	size_t	total_cols;
	char	**matrix;

	matrix = map_data -> matrix;
	col = -1;
	row = 0;
	while (matrix[row])
	{
		total_cols = ft_strlen(matrix[row]);
		if (row == 0 || row == ((map_data -> total_rows) - 1))
			while (col < total_cols)
			{
				if (matrix[row][col] != '1')
				{
					ft_putendl_fd("ERROR MAP HAVE NOT WALL ON EVERY SIDES", 2);
					return (false);
				}
				col++;
			}
		else
			if (matrix[row][col] != '1' || matrix[row][total_cols - 1] != '1')
			{
					ft_putendl_fd("ERROR MAP HAVE NOT WALL ON EVERY SIDES", 2);
					return (false);
			}
		col = 0;
		row++;
	}
	printf("VALID WALLS\n");
	return (true);
}

bool	is_valid_fill(t_map **map_data)
{
	size_t	col;
	size_t	row;
	size_t	total_cols;
	char	**matrix;

	col = 1;
	row = 0;
	matrix = (*map_data) -> matrix;
	while (matrix[row])
	{
		total_cols = ft_strlen(matrix[row]);
		if (row > 0 && row < ((*map_data) -> total_rows - 1))
			while (col < total_cols - 1)
			{
				if (!ft_strchr("0PCE1", matrix[row][col]) || is_duplicate_items(map_data, matrix[row][col]))
				{
					ft_putendl_fd("ERROR MAP HAVE NOT VALID FIELD (PE01C) or duplicate items", 2);
					return (false);
				}
				col++;
			}
		col = 1;
		row++;
	}
	if ((*map_data) -> collectibles == 0 || (*map_data) -> player != 1 || (*map_data) -> exit != 1)
		return (false);
	printf("VALID INFILL\n");
	return (true);
}
