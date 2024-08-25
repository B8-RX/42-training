/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:33:22 by ssghioua          #+#    #+#             */
/*   Updated: 2024/07/17 09:33:23 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_map *map_data)
{
	int	i;

	i = 0;
	if (map_data)
	{
		if (map_data->matrix)
		{
			while (map_data->matrix[i])
			{
				free(map_data->matrix[i]);
				map_data->matrix[i++] = NULL;
			}
			free(map_data->matrix);
			map_data->matrix = NULL;
		}
		free(map_data);
	}
}

void	free_img_ptr(t_game	*game)
{
	free_img_rock(game);
	free_img_boat(game);
	free_img_sea(game);
	free_img_exit(game);
	free_img_collectibles(game);
	if (game->img_data.placeholder)
		mlx_destroy_image(game->mlx, game->img_data.placeholder);
}

void	free_game(t_game *game)
{
	if (game)
	{
		if (game->map_data)
			free_map(game->map_data);
		free_img_ptr(game);
		on_destroy(game);
	}
	exit(SUCCESS);
}

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	if (array && *array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

void	on_destroy(t_game *game)
{
	if (game->mlx_win && game)
	{
		mlx_destroy_window(game->mlx, game->mlx_win);
	}
	if (game && game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game)
		free(game);
}
