/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:02:33 by dgargant          #+#    #+#             */
/*   Updated: 2025/11/26 14:22:01 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*void draw_raycast(t_game *game, double start_x, int rgb, int i)
{
	double cos_ang = cos(start_x);
	double sin_ang = sin(start_x);
	double ray_y = game->player->s_pos_y;
	double ray_x = game->player->s_pos_x;
	while (!touch(ray_y, ray_x, game))
	{
		ray_x += cos_ang;
		ray_y += sin_ang;	
	}
	//write(1, "aqui peta", 12);
	double dist = fix_distance(game, ray_x, ray_y);
	if (dist == 0)
		dist = 0.1;
	double height = (BLOCK2 / dist) * (W_WIDTH / 2);
	double start_y = (W_HEIGHT - height) / 2;
	if (start_y <= 0)
		start_y = 1;
	double end = start_y + height;
	if (end >= W_HEIGHT)
		end = W_HEIGHT - 1;
	while (start_y < end)
	{
		mlx_put_pixel(game->img, i, start_y, rgb);
		start_y++;
	}
}

void raycast(t_game *game)
{
	int rgb;
	
	rgb = get_rgba(0, 0, 255, 255);
	double	fraction = PI / 3 / W_WIDTH;
	double	start_x = game->player->p_ang - PI / 6;
	int i = 0;
	while (i < W_WIDTH)
	{
		game->tex_x = start_x * T_WIDTH;
		draw_raycast(game, start_x, rgb, i);
		start_x += fraction;
		i++;
	}
}*/

int	check_direction(t_game *game, int sx, int sy, int dir)
{
	int	end_x;
	int	end_y;

	end_x = game->player->end_x;
	end_y = game->player->end_y;
	if (is_touching(game, end_x - sx, end_y)
		|| is_touching(game, end_x - sx, end_y - sy))
	{
		game->tex_x = (int)end_x % game->textures->wall_north->width;
		dir = 1;
		if (sy == 1)
			dir = 2;
	}
	else if (is_touching(game, end_x, end_y - sy)
		|| is_touching(game, end_x, end_y))
	{
		game->tex_x = (int)end_y % game->textures->wall_north->width;
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
	if (game->side == 1)
		game->textures->t_print = game->textures->wall_north;
	else if (game->side == 2)
		game->textures->t_print = game->textures->wall_south;
	else if (game->side == 3)
		game->textures->t_print = game->textures->wall_east;
	else if (game->side == 4)
		game->textures->t_print = game->textures->wall_west;
	else
		return ;
	tex_y = 0;
	step = game->textures->t_print->height / height;
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
