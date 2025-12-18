/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:47:22 by dgargant          #+#    #+#             */
/*   Updated: 2025/12/18 15:17:34 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_textures	*init_textures(t_game *game)
{
	t_textures	*texture;
	const char	*tnorth;
	const char	*tsouth;
	const char	*teast;
	const char	*twest;

	tnorth = game->map->textures.north;
	tsouth = game->map->textures.south;
	teast = game->map->textures.east;
	twest = game->map->textures.west;
	texture = malloc(sizeof(t_textures));
	if (texture == NULL)
		return (NULL);
	texture->wall_north = NULL;
	texture->wall_south = NULL;
	texture->wall_east = NULL;
	texture->wall_west = NULL;
	texture->wall_north = mlx_load_png(tsouth);
	texture->wall_south = mlx_load_png(tnorth);
	texture->wall_east = mlx_load_png(twest);
	texture->wall_west = mlx_load_png(teast);
	return (texture);
}
