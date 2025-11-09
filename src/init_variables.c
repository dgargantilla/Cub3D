/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:00:00 by shirakim          #+#    #+#             */
/*   Updated: 2025/09/14 16:00:00 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
#include "../libft/inc/libft.h"

void	init_variables(t_map *map, char *filename)
{
	// Initialize all structure members to default values
	map->player_x = 0;
	map->player_y = 0;
	map->player_dir = '\0';
	map->width = 0;
	map->height = 0;
	map->text = ft_strdup(filename);
	map->textures.north = NULL;
	map->textures.south = NULL;
	map->textures.west = NULL;
	map->textures.east = NULL;
	map->floor.r = 0;
	map->floor.g = 0;
	map->floor.b = 0;
	map->ceilling.r = 0;
	map->ceilling.g = 0;
	map->ceilling.b = 0;
	map->got_textures = 0;
	map->got_colors = 0;
	map->got_map = 0;
	map->config_parsed = 0;
	map->map = NULL;
}