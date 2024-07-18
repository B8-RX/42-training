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

	if (!init_map(game, map_path))
		return (-1);
	map_data = (*game) -> map_data;
	if (check_map_size(*game) == -1)
		return (-1);
	if (!is_map_square(map_data))
	{
		ft_putendl_fd("ERROR MAP NOT SQUARE", 2);
		return (-1);
	}
	else
		printf("VALID SQUARE\n");
	if (!is_valid_walls(map_data))
	{
		ft_putendl_fd("ERROR MAP HAVE NOT WALL ON EVERY SIDES", 2);
		return (-1);
	}
	else
		printf("VALID WALLS\n");
	if (!is_valid_fill(&map_data))
	{
		ft_putendl_fd("ERROR MAP HAVE NOT VALID FIELD (PE01C)", 2);
		return (-1);
	}
	else
		printf("VALID INFILL\n");
	if (!is_valid_player_path(&map_data))
	{
		ft_putendl_fd("ERROR PLAYER HAVE NOT ACCESS TO EVERY ITEMS", 2);
		return (-1);
	}
	else
		printf("VALID PLAYER PATH\n");
	return (1);
}

int	check_map_size(t_game *game)
{
	if (game -> map_data -> total_cols * 128 > (unsigned int)game -> screen_width ||
		game -> map_data -> total_rows * 128 > (unsigned int)game -> screen_height)
	{
		ft_putendl_fd("ERROR MAP TOO BIG", 2);
		return (-1);
	}
	printf("TOTAL SIZE IMG x_axe: %zu\n", game -> map_data-> total_cols * 128);
	printf("TOTAL SIZE IMG y_axe: %zu\n", game -> map_data-> total_rows * 128);
	if (game -> map_data -> total_cols  < 3 ||
		game -> map_data -> total_rows  < 3)
	{
		ft_putendl_fd("ERROR MAP TOO SMALL", 2);
		return (-1);
	}
	return (0);
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
			return (false);
		i++;
	}
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
					return (false);
				col++;
			}
		else
			if (matrix[row][col] != '1' || matrix[row][total_cols - 1] != '1')
				return (false);
		col = 0;
		row++;
	}
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
				if (!ft_strchr("0PCE1", matrix[row][col]))
					return (false);
				if (is_duplicate_items(map_data, matrix[row][col]))
					return (false);
				col++;
			}
		col = 1;
		row++;
	}
	if ((*map_data) -> collectibles == 0 || (*map_data) -> player != 1 || (*map_data) -> exit != 1)
		return (false);
	return (true);
}
