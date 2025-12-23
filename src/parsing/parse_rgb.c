/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:00:00 by shirakim          #+#    #+#             */
/*   Updated: 2025/12/22 09:44:38 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	is_valid_rgb(int r, int g, int b)
{
	return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}

void	free_parts(char **parts)
{
	int	i;

	i = 0;
	while (parts[i])
		free(parts[i++]);
	free(parts);
}

int	parse_rgb_values(char **parts, t_color *color)
{
	color->r = ft_atoi(parts[0]);
	color->g = ft_atoi(parts[1]);
	color->b = ft_atoi(parts[2]);
	if (!is_valid_rgb(color->r, color->g, color->b))
	{
		ft_putendl_fd("Error: RGB values must be 0-255", 2);
		return (1);
	}
	return (0);
}

int	parse_rgb(char *str, t_color *color)
{
	char	**parts;
	int		count;

	parts = ft_split(str, ',');
	if (!parts)
		return (1);
	count = 0;
	while (parts[count])
		count++;
	if (count != 3)
	{
		free_parts(parts);
		ft_putendl_fd("Error: Invalid RGB format (should be R,G,B)", 2);
		return (1);
	}
	if (parse_rgb_values(parts, color))
	{
		free_parts(parts);
		return (1);
	}
	free_parts(parts);
	return (0);
}

int	parse_color_element(t_map *data, char *line, char id)
{
	if (id == 'F')
	{
		if (data->got_colors & 1)
		{
			ft_putendl_fd("Error: Duplicate F element", 2);
			return (1);
		}
		if (parse_rgb(line + 2, &data->floor))
			return (1);
		data->got_colors |= 1;
	}
	else if (id == 'C')
	{
		if (data->got_colors & 2)
		{
			ft_putendl_fd("Error: Duplicate C element", 2);
			return (1);
		}
		if (parse_rgb(line + 2, &data->ceiling))
			return (1);
		data->got_colors |= 2;
	}
	return (0);
}
