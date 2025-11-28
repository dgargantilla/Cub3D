/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:03:31 by dgargant          #+#    #+#             */
/*   Updated: 2025/11/28 19:56:48 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*bool touch(float py, float px, t_game *game)
{
	int x = px / BLOCK2;
	int y = py / BLOCK2;
	if(game->map->map[y][x] == '1')
		return (true);
	return (false);
}*/

bool	is_touching(t_game *game, float px, float py)
{
	const int		x = px / BLOCK2;
	const int		y = py / BLOCK2;

	if (x < 0 || y < 0 || x >= game->map->width || y >= game->map->height)
		return (true);
	else if (game->map->map[y][x] == '1')
		return (true);
	return (false);
}

void	draw_background(t_game *game)
{
	int	x;
	int	y;
	int	rgb;
	int	rgb2;

	x = 0;
	y = 0;
	rgb = get_rgba(0, 0, 0, 255);
	rgb2 = get_rgba(50, 255, 255, 50);
	while (y <= W_HEIGHT)
	{
		x = 0;
		while (x <= W_WIDTH)
		{
			if (y < (W_HEIGHT / 2))
				mlx_put_pixel(game->img, x, y, rgb);
			else
				mlx_put_pixel(game->img, x, y, rgb2);
			x++;
		}
		y++;
	}
}

double	distance(double x, double y)
{
	return (sqrt((x * x) + (y * y)));
}

/*double	distance(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}*/

/*double	view_lane_distance(t_game *game,float x1, float y1, float angle)
{
	//float	x2;
	//float	y2;
	float	player_angle;
	float	raw_distance;
	double	adjusted_distance;

	//x2 = 0;
	//y2 = 0;
	player_angle = 0;
	raw_distance = 0;
	adjusted_distance = 0;
	//x2 = game->player->s_pos_x;
	//y2 = game->player->s_pos_x;
	player_angle = game->player->p_ang;
	//raw_distance = distance(x1, y1, x2, y2);
	raw_distance = distance(x1, y1);
	adjusted_distance = raw_distance * cos(player_angle - angle);
	return (adjusted_distance);
}*/

int	get_pixel_from_image(t_game *game, int x, int y, int side)
{
	uint8_t		*pixel;
	int			i;

	i = 0;
	if (side == 1)
		game->textures->t_print = game->textures->wall_north;
	else if (side == 2)
		game->textures->t_print = game->textures->wall_south;
	else if (side == 3)
		game->textures->t_print = game->textures->wall_east;
	else if (side == 4)
		game->textures->t_print = game->textures->wall_west;
	else
		return (0);
	if (!game->textures || !game->textures->t_print)
		return (get_rgba(255, 0, 255, 255));
	i = (y * BLOCK2 + x) * game->textures->t_print->bytes_per_pixel;
	pixel = &game->textures->t_print->pixels[i];
	return ((pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3]);
}

double	fix_distance(t_game *game, double x2, double y2)
{
	double	delta_x;
	double	delta_y;
	double	angle;
	double	fix_dist;

	delta_x = x2 - game->player->s_pos_x;
	delta_y = y2 - game->player->s_pos_y;
	angle = atan2(delta_y, delta_x) - game->player->p_ang;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}
