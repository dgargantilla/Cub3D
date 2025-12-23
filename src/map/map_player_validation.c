/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:15:00 by shirakim          #+#    #+#             */
/*   Updated: 2025/12/22 13:09:03 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	validate_top_bottom_borders(t_map *data)
{
	int	i;

	i = 0;
	while (i < data->height)
	{
		if (!validate_line_borders(data->map[i], ft_strlen(data->map[i])))
			return (0);
		i++;
	}
	return (1);
}

int	validate_sides_borders(t_map *data)
{
	(void)data;
	return (1);
}

int	validate_walkable_spaces(t_map *data)
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
			if (is_walkable_char(data->map[i][j]))
			{
				if (!check_walkable_position(data, i, j, row_len))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_player_count(int player_count)
{
	if (player_count == 0)
	{
		ft_putendl_fd("Error: No player (P) found in map", 2);
		return (0);
	}
	if (player_count > 1)
	{
		ft_putendl_fd("Error: Multiple players found in map", 2);
		return (0);
	}
	return (1);
}
