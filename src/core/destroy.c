/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:53:22 by dgargant          #+#    #+#             */
/*   Updated: 2025/12/15 10:24:29 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	destroy_all(t_game *game)
{
	if (game->textures->wall_north)
		mlx_delete_texture(game->textures->wall_north);
	if (game->textures->wall_south)
		mlx_delete_texture(game->textures->wall_south);
	if (game->textures->wall_east)
		mlx_delete_texture(game->textures->wall_east);
	if (game->textures->wall_west)
		mlx_delete_texture(game->textures->wall_west);
	//mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
	free(game->textures);
	free(game->player);
	free(game->map->text);
	free(game->mlx);
	free(game);
	exit(1);
}
