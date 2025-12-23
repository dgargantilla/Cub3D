/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:00:00 by shirakim          #+#    #+#             */
/*   Updated: 2025/12/22 13:01:38 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	is_valid_neighbor(char c)
{
	return (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

int	is_walkable_space(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	check_horizontal_neighbors(t_map *data, int i, int j, int row_len)
{
	char	neighbor;

	if (j > 0)
	{
		neighbor = data->map[i][j - 1];
		if (!is_valid_neighbor(neighbor))
		{
			ft_putendl_fd("Error: Walkable space has invalid neighbor", 2);
			return (0);
		}
	}
	if (j < row_len - 1)
	{
		neighbor = data->map[i][j + 1];
		if (!is_valid_neighbor(neighbor))
		{
			ft_putendl_fd("Error: Walkable space has invalid neighbor", 2);
			return (0);
		}
	}
	return (1);
}

int	check_vertical_neighbor(t_map *data, int i, int j, int direction)
{
	int		neighbor_row;
	int		neighbor_len;
	char	neighbor;

	if (direction == -1 && i > 0)
		neighbor_row = i - 1;
	else if (direction == 1 && i < data->height - 1)
		neighbor_row = i + 1;
	else
		return (1);
	neighbor_len = ft_strlen(data->map[neighbor_row]);
	if (j >= neighbor_len)
	{
		ft_putendl_fd("Error: Walkable space extends beyond valid map", 2);
		return (0);
	}
	neighbor = data->map[neighbor_row][j];
	if (!is_valid_neighbor(neighbor))
	{
		ft_putendl_fd("Error: Walkable space has invalid neighbor", 2);
		return (0);
	}
	return (1);
}

int	check_all_neighbors(t_map *data, int i, int j, int row_len)
{
	if (!check_horizontal_neighbors(data, i, j, row_len))
		return (0);
	if (!check_vertical_neighbor(data, i, j, -1))
		return (0);
	if (!check_vertical_neighbor(data, i, j, 1))
		return (0);
	return (1);
}
