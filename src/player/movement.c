/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:01:45 by dgargant          #+#    #+#             */
/*   Updated: 2025/12/26 12:10:19 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	try_move(t_game *game, float x, float y)
{
	game->player->s_pos_x += x;
	game->player->s_pos_y += y;
	if (is_touching(game, game->player->s_pos_x, game->player->s_pos_y))
	{
		game->player->s_pos_x -= x;
		game->player->s_pos_y -= y;
	}
}

void	forward_backward_movement(t_game *game, float cos_angle,
	float sin_angle)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_S)
		|| mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		{
			cos_angle = -cos_angle;
			sin_angle = -sin_angle;
		}
		try_move(game, 0, game->player->speed * sin_angle);
		try_move(game, game->player->speed * cos_angle, 0);
	}
}

void	left_right_movement(t_game *game)
{
	float	left_angle;
	float	right_angle;

	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		left_angle = game->player->p_ang - PI / 2;
		try_move(game, 0, game->player->speed * sin(left_angle));
		try_move(game, game->player->speed * cos(left_angle), 0);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		right_angle = game->player->p_ang + PI / 2;
		try_move(game, 0, game->player->speed * sin(right_angle));
		try_move(game, game->player->speed * cos(right_angle), 0);
	}
}

void	handle_rotation(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->player->p_ang -= 0.05;
		if (game->player->p_ang < 0)
			game->player->p_ang += 2 * PI;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->player->p_ang += 0.05;
		if (game->player->p_ang > 2 * PI)
			game->player->p_ang -= 2 * PI;
	}
}

void	move_player(t_game *game)
{
	float		cos_angle;
	float		sin_angle;
	double		x;
	double		y;

	cos_angle = cos(game->player->p_ang);
	sin_angle = sin(game->player->p_ang);
	draw_background(game);
	forward_backward_movement(game, cos_angle, sin_angle);
	left_right_movement(game);
	handle_rotation(game);
	render_view(game);
	draw_map(game);
	x = (game->player->s_pos_x / BLOCK2) * BLOCK;
	y = (game->player->s_pos_y / BLOCK2) * BLOCK;
	if (game->map->width <= 30 && game->map->height <= 15)
		draw_square(game, x, y, BLOCK / 4);
	game->player->x = game->player->s_pos_x / BLOCK2;
	game->player->y = game->player->s_pos_y / BLOCK2;
	game->player->direction = game->player->p_ang * (180 / PI);
	if (game->player->direction > 180)
		game->player->direction -= 360;
}
