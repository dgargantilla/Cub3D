/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_practical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:24:11 by shirakim          #+#    #+#             */
/*   Updated: 2025/12/09 23:55:45 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3D.h"
#include "../libft/inc/libft.h"


t_check	*do_check(int height, int width)
{
	int		i;
	t_check	*check;

	check = malloc(sizeof(t_check));
	check->maps = malloc(height * sizeof(int *));
	i = 0;
	while (i < height)
	{
		check->maps[i] = ft_calloc(width, sizeof(int));
		i++;
	}
	check->coins_left = 0;
	check->exitparse = 0;
	return (check);
}

void	find_position(t_check *check, t_map *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			if (data->map[i][j] == 'P')
				ext(data, i, j);
			else if (data->map[i][j] == 'C')
				check->coins_left++;
			else if (data->map[i][j] == 'E')
			{
				check->exit_x = i;
				check->exit_y = j;
				check->exitparse = 1;
			}
			j++;
		}
		i++;
	}
}

void	flood_fill(int x, int y, t_check *check, t_map *data)
{
	check->maps[x][y] = 1;
	if (data->map[x][y] == 'C')
	{
		check->coins_left--;
	}
	if (is_valid(x, y - 1, check, data))
		flood_fill(x, y - 1, check, data);
	if (is_valid(x, y + 1, check, data))
		flood_fill(x, y + 1, check, data);
	if (is_valid(x - 1, y, check, data))
		flood_fill(x - 1, y, check, data);
	if (is_valid(x + 1, y, check, data))
		flood_fill(x + 1, y, check, data);
}

void	free_check(t_check *check, int height)
{
	int i;

	if (!check)
		return;
	if (check->maps)
	{
		i = 0;
		while (i < height)
		{
			if (check->maps[i])
				free(check->maps[i]);
			i++;
		}
		free(check->maps);
	}
	free(check);
}