/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:47:22 by dgargant          #+#    #+#             */
/*   Updated: 2025/12/23 11:05:29 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


t_textures	*init_textures(t_game *game)
{
	t_textures	*texture;
	const char	*tNorth;
	const char	*tSouth;
	const char	*tEast;
	const char	*tWest;

	tNorth = game->map->textures.north;
	tSouth = game->map->textures.south;
	tEast = game->map->textures.east;
	tWest = game->map->textures.west;
	texture = malloc(sizeof(t_textures));
	if (texture == NULL)
		return (NULL);
	texture->wall_north = NULL;
	texture->wall_south = NULL;
	texture->wall_east = NULL;
	texture->wall_west = NULL;
	texture->wall_north = mlx_load_png(tSouth);
	texture->wall_south = mlx_load_png(tNorth);
	texture->wall_east = mlx_load_png(tWest);
	texture->wall_west = mlx_load_png(tEast);
	return (texture);
}


void check_mlx_textures(t_game *game)
{
	if (!game->textures->wall_north)
		destroy_all(game);
	if (!game->textures->wall_south)
		destroy_all(game);
	if (!game->textures->wall_east)
		destroy_all(game);
	if (!game->textures->wall_west)
		destroy_all(game);
}
