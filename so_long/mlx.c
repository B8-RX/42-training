/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 21:13:34 by ssghioua          #+#    #+#             */
/*   Updated: 2024/08/24 21:13:36 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_server(t_game *game)
{
	game -> mlx = mlx_init();
	if (game -> mlx == NULL)
	{
		ft_putendl_fd("ERROR SERVER INITIALIZATION", 2);
		free_game(game);
		exit(ERROR);
	}
}

void	init_window(t_game *game)
{
	game->mlx_win = mlx_new_window(game->mlx, game->map_data->total_cols * 128,
			game->map_data->total_rows * 128, "test window");
	if (!game->mlx_win)
	{
		ft_putendl_fd("ERROR WINDOW INITIALIZATION", 2);
		free_game(game);
		exit(ERROR);
	}
	mlx_get_screen_size(game->mlx, &(game->screen_width),
		&(game->screen_height));
}

void	run_game(t_game *game)
{
	mlx_hook(game -> mlx_win, 2, 1L << 0, &key_events, game);
	mlx_hook(game -> mlx_win, 17, 1L << 17, &on_close, game);
	mlx_loop_hook(game -> mlx, &display_game, game);
	mlx_loop(game -> mlx);
}
