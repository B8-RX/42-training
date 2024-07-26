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
		if (map_data -> str_map)
			free(map_data -> str_map);
		free(map_data);	
	}
}

void	free_game(t_game *game)
{
	if (game)
	{
		if (game -> map_data)
			free_map(game -> map_data);
		free(game);
	}
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
