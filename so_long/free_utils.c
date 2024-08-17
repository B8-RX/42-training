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

#include "./so_long.h"

void	free_map(t_map *map_data)
{
	int	i;

	i = 0;
	if (map_data)
	{
		if (map_data -> matrix)
		{
			while(map_data -> matrix[i])
			{
				free(map_data -> matrix[i]);
				map_data -> matrix[i++] = NULL;
			}
			free(map_data -> matrix);
			map_data -> matrix = NULL;
		}
	}
	free(map_data);	
}
void	free_img_ptr(t_game	*game)
{
	int	i;

	if (game -> img_data.rock_y_top)
		mlx_destroy_image(game->mlx, game -> img_data.rock_y_top);
	if (game -> img_data.rock_y_top_left)
		mlx_destroy_image(game->mlx, game -> img_data.rock_y_top_left);
	if (game -> img_data.rock_y_top_right)
		mlx_destroy_image(game->mlx, game -> img_data.rock_y_top_right);
	if (game -> img_data.rock_y_bottom)
		mlx_destroy_image(game->mlx, game -> img_data.rock_y_bottom);
	if (game -> img_data.rock_y_bottom_left)
		mlx_destroy_image(game->mlx, game -> img_data.rock_y_bottom_left);
	if (game -> img_data.rock_y_bottom_right)
		mlx_destroy_image(game->mlx, game -> img_data.rock_y_bottom_right);
	if (game -> img_data.rock_x_left)
		mlx_destroy_image(game->mlx, game -> img_data.rock_x_left);
	if (game -> img_data.rock_x_right)
		mlx_destroy_image(game->mlx, game -> img_data.rock_x_right);
	if (game -> img_data.rock_obstacles)
		mlx_destroy_image(game->mlx, game -> img_data.rock_obstacles);
	if (game->img_data.sea)
		mlx_destroy_image(game->mlx, game->img_data.sea);
	if (game->img_data.boat_up)
		mlx_destroy_image(game->mlx, game->img_data.boat_up);
	if (game->img_data.boat_down)
		mlx_destroy_image(game->mlx, game->img_data.boat_down);
	if (game->img_data.boat_left)
		mlx_destroy_image(game->mlx, game->img_data.boat_left);
	if (game->img_data.boat_right)
		mlx_destroy_image(game->mlx, game->img_data.boat_right);
	if (game->img_data.placeholder)
		mlx_destroy_image(game->mlx, game->img_data.placeholder);
	if (game->img_data.exit_img)
	{
		mlx_destroy_image(game->mlx, game->img_data.exit_img);
		game -> img_data.exit_img = NULL;
	}
	i = 0;
	if (*(game->img_data.fish_img))
		while (game -> img_data.fish_img[i])
			mlx_destroy_image(game->mlx, game->img_data.fish_img[i++]);
}

void	free_game(t_game *game)
{
	if (game -> map_data)
		free_map(game -> map_data);
	free_img_ptr(game);
	on_destroy(game);
	free(game);
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
	if (game -> mlx_win && game)
	{
		mlx_destroy_window(game -> mlx, game -> mlx_win);
		mlx_destroy_display(game -> mlx);
		free(game -> mlx);
	}
}
