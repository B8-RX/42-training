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

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	if (!game)
		return ;
	if (game -> mlx)
		free(game -> mlx);
	if (game -> mlx_win)
		free(game -> mlx_win);
	if (game -> map_data)
	{
		if (game -> map_data -> matrix)
		{
			while(game -> map_data -> matrix[i])
				free(game -> map_data -> matrix[i++]);
			free(game -> map_data -> matrix);
		}
		free(game -> map_data);	
	}
	free(game);
}
