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
		return (1);
	if (check_extension(argv[1])== -1)
	{
		ft_putendl_fd("ERROR EXTENSION", 2);
		exit(1);
	}
	if (init_game(&game) == -1)
	{
		ft_putendl_fd("ERROR GAME INITIALIZATION", 2);
		exit (1);
	}
	game -> mlx = mlx_init();
	if (!game -> mlx)
	{
		ft_putendl_fd("ERROR SERVER INITIALIZATION", 2);
		free(game);
		exit(1);
	}
	mlx_get_screen_size(game -> mlx, &(game -> screen_width), &(game -> screen_height));
	printf("SCREEN WIDTH = %d\nSCREEN HEIGHT = %d\n", game -> screen_width, game -> screen_height);
	if (verify_map(&game, argv[1]) == -1)
	{
		mlx_destroy_display(game -> mlx);
		free_map(game -> map_data);
		free(game);
		exit(1);
	}
	game -> mlx_win = mlx_new_window(game -> mlx, game -> map_data -> total_cols * 128, game -> map_data -> total_rows * 128, "test window");
	if (!game -> mlx_win)
	{
		ft_putendl_fd("ERROR WINDOW INITIALIZATION", 2);
		mlx_destroy_display(game -> mlx);
		free_map(game -> map_data);
		free(game);
		exit(1);
	}
	mlx_loop_hook(game -> mlx, display_game, game);
	mlx_key_hook(game -> mlx_win, key_events, game);
	// mlx_hook(game -> mlx_win, 2, 1L<<0, on_key_down, game);
	// mlx_hook(game -> mlx_win, 3, 1L<<1, on_key_up, game);
	// mlx_hook(game -> mlx_win, 4, 1L<<2, on_click_down, game);
	// mlx_hook(game -> mlx_win, 5, 1L<<3, on_click_up, game);
	mlx_hook(game -> mlx_win, 6, 1L<<6, on_mouse_move, game);
	mlx_hook(game -> mlx_win, 17, 0, on_destroy, game);
	mlx_loop(game -> mlx);
	return (0);
}
