/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walkable_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:15:00 by shirakim          #+#    #+#             */
/*   Updated: 2025/12/23 09:45:31 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_walkable_left(t_map *data, int i, int j)
{
	if (j == 0 || data->map[i][j - 1] == ' ')
	{
		ft_putendl_fd("Error: Walkable space has void on left", 2);
		return (0);
	}
	return (1);
}

int	check_walkable_right(t_map *data, int i, int j, int row_len)
{
	if (j >= row_len - 1 || data->map[i][j + 1] == ' ')
	{
		ft_putendl_fd("Error: Walkable space has void on right", 2);
		return (0);
	}
	return (1);
}

int	check_walkable_vertical(t_map *data, int i, int j)
{
	if (i == 0 || i >= data->height - 1)
	{
		ft_putendl_fd("Error: Walkable space at top/bottom edge", 2);
		return (0);
	}
	if (j >= (int)ft_strlen(data->map[i - 1])
		|| data->map[i - 1][j] == ' ')
	{
		ft_putendl_fd("Error: Walkable space has void above", 2);
		return (0);
	}
	if (j >= (int)ft_strlen(data->map[i + 1])
		|| data->map[i + 1][j] == ' ')
	{
		ft_putendl_fd("Error: Walkable space has void below", 2);
		return (0);
	}
	return (1);
}

int	is_walkable_char(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	check_walkable_position(t_map *data, int i, int j, int row_len)
{
	if (!check_walkable_left(data, i, j))
		return (0);
	if (!check_walkable_right(data, i, j, row_len))
		return (0);
	if (!check_walkable_vertical(data, i, j))
		return (0);
	return (1);
}
