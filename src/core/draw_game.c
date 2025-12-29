/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:02:33 by dgargant          #+#    #+#             */
/*   Updated: 2025/12/29 14:39:00 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_direction(t_game *game, int sx, int sy, int dir)
{
	int	end_x;
	int	end_y;

	end_x = game->player->end_x;
	end_y = game->player->end_y;
	if (is_touching(game, end_x - sx, end_y)
		|| is_touching(game, end_x - sx, end_y - sy))
	{
		game->tex_x = (int)end_x % BLOCK2;
		dir = 1;
		if (sy == 1)
			dir = 2;
	}
	else if (is_touching(game, end_x, end_y - sy)
		|| is_touching(game, end_x, end_y))
	{
		game->tex_x = (int)end_y % BLOCK2;
		dir = 3;
		if (sx == 1)
			dir = 4;
	}
	return (dir);
}

int	calculate_direction(t_game *game, float angle, int dir)
{
	int	sx;
	int	sy;

	sx = -1;
	sy = -1;
	if (cos(angle) > 0)
		sx = 1;
	if (sin(angle) > 0)
		sy = 1;
	return (check_direction(game, sx, sy, dir));
}

void	draw_h_line(t_game *game, float height, int start_x)
{
	int		color;
	float	tex_y;
	int		end;
	int		start_y;
	float	step;

	color = 0;
	tex_y = 0;
	step = BLOCK2 / height;
	if (height > W_HEIGHT)
	{
		tex_y = (height - W_HEIGHT) * step / 2;
		height = W_HEIGHT;
	}
	start_y = (W_HEIGHT - height) / 2;
	end = start_y + height;
	while (start_y < end)
	{
		color = get_pixel_from_image(game, game->tex_x, tex_y, game->side);
		mlx_put_pixel(game->img, start_x, start_y, color);
		tex_y += step;
		start_y++;
	}
}

void	draw_line(t_game *game, float angle, int start_x)
{
	float	x;
	float	y;
	float	dist;
	float	line_height;

	x = game->player->s_pos_x;
	y = game->player->s_pos_y;
	while (!is_touching(game, x, y))
	{
		x += cos(angle);
		y += sin(angle);
	}
	game->player->end_x = x;
	game->player->end_y = y;
	game->side = calculate_direction(game, angle, 0);
	dist = fix_distance(game, x, y);
	line_height = (BLOCK2 / dist) * (W_WIDTH / 2);
	draw_h_line(game, line_height, start_x);
}

void	render_view(t_game *game)
{
	int		i;
	float	fov_in_radians;
	float	angle_offset;
	float	ray_angle;

	i = 0;
	fov_in_radians = game->player->fov * PI / 180;
	angle_offset = game->player->p_ang - fov_in_radians / 2.0;
	while (i < W_WIDTH)
	{
		ray_angle = angle_offset + ((float)i / W_WIDTH) * fov_in_radians;
		draw_line(game, ray_angle, i);
		i++;
	}
}
