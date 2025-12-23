/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 23:20:49 by shirakim          #+#    #+#             */
/*   Updated: 2025/12/23 14:42:35 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_textures(t_map *data)
{
	if (data->textures.north)
		free(data->textures.north);
	if (data->textures.south)
		free(data->textures.south);
	if (data->textures.west)
		free(data->textures.west);
	if (data->textures.east)
		free(data->textures.east);
	data->textures.north = NULL;
	data->textures.south = NULL;
	data->textures.west = NULL;
	data->textures.east = NULL;
}

void	initialize_map_utils(t_map *data)
{
	data->width = 0;
	data->height = 0;
	data->player_x = -1;
	data->player_y = -1;
	data->player_dir = 0;
	data->got_textures = 0;
	data->got_colors = 0;
	data->got_map = 0;
}

int	initialize_map_data(t_map *data)
{
	int	i;

	i = 0;
	if (data->map)
	{
		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
	free_textures(data);
	initialize_map_utils(data);
	data->map = NULL;
	data->textures.north = NULL;
	data->textures.south = NULL;
	data->textures.west = NULL;
	data->textures.east = NULL;
	return (0);
}

void	mapa_memory(t_map *data)
{
	int	i;

	i = 0;
	data->map = malloc(sizeof(char *) * (data->height + 1));
	if (!data->map)
		return ;
	while (i < data->height)
	{
		data->map[i] = NULL;
		i++;
	}
	data->map[data->height] = NULL;
}
