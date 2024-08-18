/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:46:37 by ssghioua          #+#    #+#             */
/*   Updated: 2024/07/17 09:46:39 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc < 2)
		return (ERROR);
	if (check_file(argv[1])== ERROR || init_game(&game) == ERROR)
		exit(ERROR);
	if (init_map(&game, argv[1]) == ERROR)
	{
		ft_putendl_fd("ERROR MAP INITIALIZATION", 2);
		free_game(game);
		exit(ERROR);
	}	
	game -> mlx = mlx_init();
	if (game -> mlx == NULL)
	{
		ft_putendl_fd("ERROR SERVER INITIALIZATION", 2);
		free_game(game);
		exit(ERROR);
	}
	mlx_get_screen_size(game -> mlx, &(game -> screen_width), &(game -> screen_height));
	game -> mlx_win = mlx_new_window(game -> mlx, game -> map_data -> total_cols * 128, game -> map_data -> total_rows * 128, "test window");
	if (!game -> mlx_win)
	{
		ft_putendl_fd("ERROR WINDOW INITIALIZATION", 2);
		free_game(game);
		exit(ERROR);
	}
	if (verify_map(&game) == ERROR || init_images(game) == ERROR)
	{
		free_game(game);
		exit(ERROR);
	}
	mlx_hook(game -> mlx_win, 2, 1L<<0, &key_events, game);
	mlx_hook(game -> mlx_win, 17, 1L<<17, &on_close, game);
	mlx_loop_hook(game -> mlx, &display_game, game);
	mlx_loop(game -> mlx);
	if (game)
		free_game(game);
	return (SUCCESS);
}
