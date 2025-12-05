/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:47:22 by dgargant          #+#    #+#             */
/*   Updated: 2025/12/05 14:49:07 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


/*void	texture_error(t_game *game)
{
	if (game->textures->wall_north)
		mlx_delete_texture(game->textures->wall_north);
	if (game->textures->wall_south)
		mlx_destroy_image(game->textures->wall_south);
	if (game->textures->wall_east)
		mlx_destroy_image(game->textures->wall_east);
	if (game->textures->wall_west)
		mlx_destroy_image(game->textures->wall_west);
	free(game->mlx);
	write(1, "Texture error\n", 15);
	exit(1);
}*/

t_textures	*init_textures(void)
{
	t_textures	*texture;

	texture = malloc(sizeof(t_textures));
	if (texture == NULL)
		return (NULL);
	texture->wall_north = NULL;
	texture->wall_south = NULL;
	texture->wall_east = NULL;
	texture->wall_west = NULL;
	texture->wall_north = mlx_load_png("./assets/pixel-red-brick-wall1.png");
	texture->wall_south = mlx_load_png("./assets/pngegg.png");
	texture->wall_east = mlx_load_png("./assets/gato12.png");
	texture->wall_west = mlx_load_png("./assets/gato21.png");
	return (texture);
}