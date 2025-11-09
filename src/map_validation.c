/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:00:00 by shirakim          #+#    #+#             */
/*   Updated: 2025/09/14 15:00:00 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
#include "../libft/inc/libft.h"

int	validate_borders(char **map, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
					return (0);
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' '
					|| map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_player(char **map, int height, int width, t_map *game_map)
{
	int	player_count;
	int	i;
	int	j;

	player_count = 0;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				player_count++;
				game_map->player_x = j;
				game_map->player_y = i;
				game_map->player_dir = map[i][j];
			}
			j++;
		}
		i++;
	}
	return (player_count == 1);
}

int	validate_characters(char **map, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' '
				&& map[i][j] != 'N' && map[i][j] != 'S'
				&& map[i][j] != 'E' && map[i][j] != 'W' && map[i][j] != '\0')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_map(t_map *data)
{
	int i;
	
	if (!data)
		return (0);
	if (!data->map)
		return (0);
	if (data->height <= 0 || data->width <= 0)
		return (0);
	
	// Check if all map rows are valid
	for (i = 0; i < data->height; i++)
	{
		if (!data->map[i])
			return (0);
	}
	
	if (!validate_characters(data->map, data->height, data->width))
		return (0);
	if (!validate_player(data->map, data->height, data->width, data))
		return (0);
	if (!validate_borders(data->map, data->height, data->width))
		return (0);
	return (1);
}