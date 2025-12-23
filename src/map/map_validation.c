/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:20:36 by shirakim          #+#    #+#             */
/*   Updated: 2025/12/23 09:54:44 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	validate_borders(t_map *data)
{
	if (!validate_top_bottom_borders(data))
		return (0);
	if (!validate_sides_borders(data))
		return (0);
	return (1);
}

static int	validate_player(t_map *data)
{
	int	i;
	int	j;
	int	player_count;
	int	row_len;

	player_count = 0;
	i = -1;
	while (++i < data->height)
	{
		row_len = ft_strlen(data->map[i]);
		j = -1;
		while (++j < row_len)
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
					|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				player_count++;
				data->player_x = j;
				data->player_y = i;
				data->player_dir = data->map[i][j];
			}
		}
	}
	return (check_player_count(player_count));
}

static int	validate_characters(t_map *data)
{
	int	i;
	int	j;
	int	row_len;

	i = 0;
	while (i < data->height)
	{
		row_len = ft_strlen(data->map[i]);
		j = 0;
		while (j < row_len)
		{
			if (!(data->map[i][j] == '0' || data->map[i][j] == '1'
						|| data->map[i][j] == 'N' || data->map[i][j] == 'S'
						|| data->map[i][j] == 'E' || data->map[i][j] == 'W'
						|| data->map[i][j] == ' '))
			{
				ft_putendl_fd("Error: Invalid character in map", 2);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_map(t_map *data)
{
	if (!validate_borders(data))
	{
		ft_putendl_fd("Error: Map borders are not closed", 2);
		return (1);
	}
	if (!validate_player(data))
		return (1);
	if (!validate_characters(data))
		return (1);
	if (!validate_walkable_spaces(data))
		return (1);
	if (!validate_map_space(data))
		return (1);
	return (0);
}

int	validate_map_space(t_map *data)
{
	int	i;
	int	j;
	int	row_len;

	i = 0;
	while (i < data->height)
	{
		row_len = ft_strlen(data->map[i]);
		j = 0;
		while (j < row_len)
		{
			if (is_walkable_space(data->map[i][j]))
			{
				if (!check_all_neighbors(data, i, j, row_len))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
