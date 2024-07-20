/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:10:19 by ssghioua          #+#    #+#             */
/*   Updated: 2024/07/17 09:10:26 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"


int	key_events(int keycode, t_game *game)
{
	printf("KEY PRESS: CODE: %d\n", keycode);
	if (keycode == 65307)
		on_destroy(game);
	return (0);
}

int	on_key_up(int keycode, t_game *game)
{
	printf("key released. KEYCODE: %d\n", keycode);
	if (keycode == 65307)
		mlx_destroy_window(game -> mlx, game -> mlx_win);
	return (0);
}

int	on_key_down(int keycode, t_game *game)
{
	printf("key pressed. KEYCODE: %d\n", keycode);
	(void)game;
	return (0);
}

int	on_click_down(int button, int x, int y, t_game *game)
{
	printf("click pressed. button: %d\n", button);
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	(void)game;
	return (0);
}

int	on_click_up(int button, int x, int y, t_game *game)
{
	printf("click release button: %d\n", button);
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	(void)game;
	return (0);
}

int	on_mouse_move(int x, int y, t_game *game)
{
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	(void)game;
	return (0);
}

int	on_destroy(t_game *game)
{
	if (game -> img_data.wall_x)
		mlx_destroy_image(game, game -> img_data.wall_x);
	if (game -> img_data.wall_y)
		mlx_destroy_image(game, game -> img_data.wall_y);
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
	if (game->img_data.fish)
		mlx_destroy_image(game->mlx, game->img_data.fish);
	if (game->img_data.exit)
		mlx_destroy_image(game->mlx, game->img_data.exit);
	if (game -> mlx_win)
		mlx_destroy_window(game -> mlx, game -> mlx_win);
	if (game -> mlx)
		mlx_destroy_display(game -> mlx);
	free_game(game);
	return (0);
}
