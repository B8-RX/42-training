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
				free(map_data -> matrix[i++]);
			free(map_data -> matrix);
		}
		free(map_data);	
	}
}

void	free_game(t_game *game)
{
	mlx_destroy_window(game -> mlx, game -> mlx_win);
	mlx_destroy_image(game, game -> img_data.img);
	mlx_destroy_display(game -> mlx);
	free_map(game -> map_data);
	free(game -> mlx);
}
