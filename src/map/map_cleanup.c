/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 23:11:25 by shirakim          #+#    #+#             */
/*   Updated: 2025/12/23 14:42:34 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_map_array(t_map *data)
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
		free (data->map);
		data->map = NULL;
	}
	if (data->text)
	{
		free(data->text);
		data->text = NULL;
	}
}

void	exit_game(t_map *data, int exit_code)
{
	if (data)
	{
		free_map_array(data);
		free_textures(data);
	}
	exit(exit_code);
}
