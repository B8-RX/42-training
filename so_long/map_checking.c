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
#include <stdio.h>

void	verify_map(t_game **game)
{
	t_map	*map_data;
	Pair	player_position;

	map_data = (*game) -> map_data;
	check_map_size(*game);
	is_map_square(*game);
	is_valid_walls(*game);
	is_valid_fill(*game);
	is_valid_player_path(*game);
	player_position = get_position(&map_data, 'P');
	(*game) -> map_data -> player_pos = (Pair) {player_position.x, player_position.y, -1};
	return ;
}

void	check_map_size(t_game *game)
{
	size_t	map_width;
	size_t	map_height;

	map_width = game -> map_data -> total_cols * 128;
	map_height = game -> map_data -> total_rows * 128;
	if (map_width >= (unsigned int)game -> screen_width ||
		map_height >= (unsigned int)game -> screen_height)
		return (handle_errors(game, "error_size"));
	if (game -> map_data -> total_cols  < 3 ||
		game -> map_data -> total_rows  < 3)
		return (handle_errors(game, "error_size"));
	return ;
}

void	is_map_square(t_game *game)
{
	size_t	first_row_len;
	char	**matrix;
	int		i;

	i = 0;
	matrix = game->map_data -> matrix;
	first_row_len = ft_strlen(matrix[i++]);
	while (matrix[i])
	{
		if (ft_strlen(matrix[i]) != first_row_len)
			return (handle_errors(game, "not_square"));
		i++;
	}
	return ;
}

void	is_valid_walls(t_game *game)
{
	size_t	col;
	size_t	row;
	size_t	total_cols;
	char	**matrix;

	matrix = game->map_data -> matrix;
	col = -1;
	row = 0;
	while (matrix[row])
	{
		total_cols = ft_strlen(matrix[row]);
		if (row == 0 || row == ((game->map_data -> total_rows) - 1))
			while (col < total_cols)
			{
				if (matrix[row][col] != '1')
					return (handle_errors(game, "error_borders"));
				col++;
			}
		else
			if (matrix[row][col] != '1' || matrix[row][total_cols - 1] != '1')
				return (handle_errors(game, "error_borders"));
		col = 0;
		row++;
	}
	return ;
}

void	is_valid_fill(t_game *game)
{
	size_t	col;
	size_t	row;
	size_t	total_cols;
	char	**matrix;

	col = 1;
	row = 0;
	matrix = game->map_data -> matrix;
	while (matrix[row])
	{
		total_cols = ft_strlen(matrix[row]);
		if (row > 0 && row < (game->map_data-> total_rows - 1))
			while (col < total_cols - 1)
			{
				if (!ft_strchr("0PCE1", matrix[row][col]) || is_duplicate(&game->map_data, matrix[row][col]))
				return (handle_errors(game, "error_infill"));
				col++;
			}
		col = 1;
		row++;
	}
	if (game->map_data -> collectibles == 0 || game->map_data -> player != 1 || game->map_data -> exit != 1)
		return (handle_errors(game, "error_infill"));
	return ;
}
