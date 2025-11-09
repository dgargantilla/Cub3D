/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:05:00 by shirakim          #+#    #+#             */
/*   Updated: 2025/09/14 15:05:00 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
#include "../libft/inc/libft.h"
#include <fcntl.h>
#include <unistd.h>

int	handle_texture(char *line, t_textures *textures, char *identifier)
{
	char	**split;
	int		fd;
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, "\n");
	if (!trimmed_line)
		return (0);
	
	split = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	
	if (!split || !split[1] || split[2])
	{
		if (split)
			ft_free_matrix(&split);
		return (0);
	}
	
	fd = open(split[1], O_RDONLY);
	if (fd == -1)
	{
		ft_free_matrix(&split);
		return (0);
	}
	close(fd);
	if (ft_strncmp(identifier, "NO", 2) == 0)
		textures->north = ft_strdup(split[1]);
	else if (ft_strncmp(identifier, "SO", 2) == 0)
		textures->south = ft_strdup(split[1]);
	else if (ft_strncmp(identifier, "WE", 2) == 0)
		textures->west = ft_strdup(split[1]);
	else if (ft_strncmp(identifier, "EA", 2) == 0)
		textures->east = ft_strdup(split[1]);
	ft_free_matrix(&split);
	return (1);
}

int	parse_rgb(char *rgb_str, int *r, int *g, int *b)
{
	char	**split;

	split = ft_split(rgb_str, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
	{
		if (split)
			ft_free_matrix(&split);
		return (0);
	}
	*r = ft_atoi(split[0]);
	*g = ft_atoi(split[1]);
	*b = ft_atoi(split[2]);
	ft_free_matrix(&split);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (0);
	return (1);
}

int	handle_color(char *line, t_map *game_map, char *identifier)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = ft_split(line, ' ');
	if (!split || !split[1] || split[2])
	{
		if (split)
			ft_free_matrix(&split);
		return (0);
	}
	if (!parse_rgb(split[1], &r, &g, &b))
	{
		ft_free_matrix(&split);
		return (0);
	}
	if (ft_strncmp(identifier, "F", 1) == 0)
	{
		game_map->floor.r = r;
		game_map->floor.g = g;
		game_map->floor.b = b;
	}
	else if (ft_strncmp(identifier, "C", 1) == 0)
	{
		game_map->ceilling.r = r;
		game_map->ceilling.g = g;
		game_map->ceilling.b = b;
	}
	ft_free_matrix(&split);
	return (1);
}

int	parse_line_element(t_map *data, char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t");
	if (!trimmed)
		return (1);
	
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
	{
		if (handle_texture(trimmed, &data->textures, "NO"))
			data->got_textures++;
	}
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
	{
		if (handle_texture(trimmed, &data->textures, "SO"))
			data->got_textures++;
	}
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
	{
		if (handle_texture(trimmed, &data->textures, "WE"))
			data->got_textures++;
	}
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
	{
		if (handle_texture(trimmed, &data->textures, "EA"))
			data->got_textures++;
	}
	else if (ft_strncmp(trimmed, "F ", 2) == 0)
	{
		if (handle_color(trimmed, data, "F"))
			data->got_colors++;
	}
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
	{
		if (handle_color(trimmed, data, "C"))
			data->got_colors++;
	}
	else if (trimmed[0] != '\0')
	{
		free(trimmed);
		return (2); // Map section started
	}
	free(trimmed);
	return (0); // Success, continue parsing config
}