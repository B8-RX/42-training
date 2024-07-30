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


bool	can_move(t_game *game, int keycode)
{
	char	**matrix;
	Pair	pos;
	bool	can_move;
	size_t	total_fish;
	size_t	catched_fish;
	bool	catch_all_fish;

	total_fish = game -> map_data -> collectibles;
	catched_fish = game -> map_data -> collected;
	catch_all_fish = (total_fish == catched_fish);
	pos = game -> map_data -> player_pos; 
	matrix = game -> map_data -> matrix;
	can_move = false;
	if (keycode == KEY_UP)
	{
		if (pos.y > 0 && (ft_strchr("0C", matrix[pos.y - 1][pos.x]) || (catch_all_fish && matrix[pos.y - 1][pos.x] == 'E')))
			can_move = true;
	}
	else if (keycode == KEY_DOWN)
	{
		if (pos.y < game -> map_data -> total_rows - 1 && (ft_strchr("0C", matrix[pos.y + 1][pos.x]) || (catch_all_fish && matrix[pos.y + 1][pos.x] == 'E')))
			can_move = true;
	}
	else if (keycode == KEY_LEFT)
	{
		if (pos.x > 0 && (ft_strchr("0C", matrix[pos.y][pos.x - 1]) || (catch_all_fish && matrix[pos.y][pos.x - 1] == 'E')))
			can_move = true;
	}
	else if (keycode == KEY_RIGHT)
	{	
		if (pos.x < game -> map_data -> total_cols - 1 && (ft_strchr("0C", matrix[pos.y][pos.x + 1]) || (catch_all_fish && matrix[pos.y][pos.x + 1] == 'E')))
			can_move = true;
	}
	return (can_move);
}

void	update_matrix(t_game *game, Pair previous_pos)
{
	size_t	pos_x;
	size_t	pos_y;
	size_t	collectibles;
	char	**matrix;

	matrix = game -> map_data -> matrix;	
	pos_x = game -> map_data -> player_pos.x;
	pos_y = game -> map_data -> player_pos.y;
	collectibles = game -> map_data -> collectibles;
	if (matrix[pos_y][pos_x] == 'C')
		game -> map_data -> collected += 1;
	else if (matrix[pos_y][pos_x] == 'E' && game -> map_data -> collected == collectibles)
	{
		game -> map_data -> exit = 1;
		on_destroy(game);
	}
	if (matrix[pos_y][pos_x] != 'P')
	{
		matrix[previous_pos.y][previous_pos.x] = '0';
		matrix[pos_y][pos_x] = 'P';
	}
	game -> map_data -> matrix = matrix;
}

void	execute_move(t_game *game, int keycode)
{
	Pair	previous_pos;
	size_t	player_pos_x;
	size_t	player_pos_y;

	player_pos_x = game -> map_data -> player_pos.x;
	player_pos_y = game -> map_data -> player_pos.y;
	previous_pos = (Pair) {player_pos_x, player_pos_y, -1};
	if (keycode == KEY_UP)
		game -> map_data -> player_pos.y -= 1;
	else if (keycode == KEY_DOWN)
		game -> map_data -> player_pos.y += 1;
	else if (keycode == KEY_LEFT)
		game -> map_data -> player_pos.x -= 1;
	else if (keycode == KEY_RIGHT)
		game -> map_data -> player_pos.x += 1;
	update_matrix(game, previous_pos);
}

int	key_events(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		on_destroy(game);
	game -> img_data.boat_direction = keycode;
	if (can_move(game, keycode))
		execute_move(game, keycode);
	return (0);
}

void	on_destroy(t_game *game)
{
	// int	i;
	//
	// if (game -> img_data.rock_y_top)
	// 	mlx_destroy_image(game, game -> img_data.rock_y_top);
	// if (game -> img_data.rock_y_top_left)
	// 	mlx_destroy_image(game, game -> img_data.rock_y_top_left);
	// if (game -> img_data.rock_y_top_right)
	// 	mlx_destroy_image(game, game -> img_data.rock_y_top_right);
	// if (game -> img_data.rock_y_bottom)
	// 	mlx_destroy_image(game, game -> img_data.rock_y_bottom);
	// if (game -> img_data.rock_y_bottom_left)
	// 	mlx_destroy_image(game, game -> img_data.rock_y_bottom_left);
	// if (game -> img_data.rock_y_bottom_right)
	// 	mlx_destroy_image(game, game -> img_data.rock_y_bottom_right);
	// if (game -> img_data.rock_x_left)
	// 	mlx_destroy_image(game, game -> img_data.rock_x_left);
	// if (game -> img_data.rock_x_right)
	// 	mlx_destroy_image(game, game -> img_data.rock_x_right);
	// if (game -> img_data.rock_obstacles)
	// 	mlx_destroy_image(game, game -> img_data.rock_obstacles);
	// if (game->img_data.sea)
	// 	mlx_destroy_image(game->mlx, game->img_data.sea);
	// if (game->img_data.boat_up)
	// 	mlx_destroy_image(game->mlx, game->img_data.boat_up);
	// if (game->img_data.boat_down)
	// 	mlx_destroy_image(game->mlx, game->img_data.boat_down);
	// if (game->img_data.boat_left)
	// 	mlx_destroy_image(game->mlx, game->img_data.boat_left);
	// if (game->img_data.boat_right)
	// 	mlx_destroy_image(game->mlx, game->img_data.boat_right);
	// if (game->img_data.placeholder)
	// 	mlx_destroy_image(game->mlx, game->img_data.placeholder);
	// if (*(game->img_data.fish_img))
	// {
	// 	i = 0;
	// 	while (game -> img_data.fish_img[i])
	// 		mlx_destroy_image(game->mlx, game->img_data.fish_img[i++]);
	// }
	// if (game->img_data.exit_img)
	// 	mlx_destroy_image(game->mlx, game->img_data.exit_img);
	if (game -> mlx_win && game)
	{
		mlx_clear_window(game -> mlx, game -> mlx_win);
		mlx_destroy_window(game -> mlx, game -> mlx_win);
		// free(game -> mlx);
	}
	// free_game(game);
	// return (0);
	exit(0);
}

// int	on_key_up(int keycode, t_game *game)
// {
// 	printf("key released. KEYCODE: %d\n", keycode);
// 	if (keycode == 65307)
// 		mlx_destroy_window(game -> mlx, game -> mlx_win);
// 	return (0);
// }
//
// int	on_key_down(int keycode, t_game *game)
// {
// 	printf("key pressed. KEYCODE: %d\n", keycode);
// 	(void)game;
// 	return (0);
// }

// int	on_click_down(int button, int x, int y, t_game *game)
// {
// 	printf("click pressed. button: %d\n", button);
// 	printf("x: %d\n", x);
// 	printf("y: %d\n", y);
// 	(void)game;
// 	return (0);
// }
//
// int	on_click_up(int button, int x, int y, t_game *game)
// {
// 	printf("click release button: %d\n", button);
// 	printf("x: %d\n", x);
// 	printf("y: %d\n", y);
// 	(void)game;
// 	return (0);
// }
//
// int	on_mouse_move(int x, int y, t_game *game)
// {
// 	printf("x: %d\n", x);
// 	printf("y: %d\n", y);
// 	(void)game;
// 	return (0);
// }
