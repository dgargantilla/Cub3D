/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:10:17 by dgargant          #+#    #+#             */
/*   Updated: 2025/12/18 15:15:44 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_square(t_game *game, int x, int y, int size)
{
	int	i;
	int	rgb;

	i = 0;
	rgb = get_rgba(0, 0, 0, 255);
	while (i++ < size)
		mlx_put_pixel(game->img, x + i, y, rgb);
	i = 0;
	while (i++ < size)
		mlx_put_pixel(game->img, x, y + i, rgb);
	i = 0;
	while (i++ < size)
		mlx_put_pixel(game->img, x + size, y + i, rgb);
	i = 0;
	while (i++ < size)
		mlx_put_pixel(game->img, x + i, y + size, rgb);
}

void	draw_map(t_game	*game)
{
	char	**map;
	int		x;
	int		y;

	y = 0;
	x = 0;
	map = game->map->map;
	if (game->map->width > 50 || game->map->height > 50)
		return ;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(game, x * BLOCK, y * BLOCK, BLOCK);
			x++;
		}
		y++;
	}
}
