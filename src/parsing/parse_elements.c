/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:48:19 by shirakim          #+#    #+#             */
/*   Updated: 2025/12/23 09:55:13 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_duplicate_texture(t_map *data, const char *id)
{
	if (ft_strncmp(id, "NO", 2) == 0 && data->textures.north)
		ft_putendl_fd("Error: Duplicate NO element", 2);
	else if (ft_strncmp(id, "SO", 2) == 0 && data->textures.south)
		ft_putendl_fd("Error: Duplicate SO element", 2);
	else if (ft_strncmp(id, "WE", 2) == 0 && data->textures.west)
		ft_putendl_fd("Error: Duplicate WE element", 2);
	else if (ft_strncmp(id, "EA", 2) == 0 && data->textures.east)
		ft_putendl_fd("Error: Duplicate EA element", 2);
	else
		return (0);
	return (1);
}

int	validate_line_continuation(char *start)
{
	while (*start && (*start == ' ' || *start == '\t'))
		start++;
	while (*start && *start != ' ' && *start != '\t')
		start++;
	while (*start && (*start == ' ' || *start == '\t'))
		start++;
	if (*start != '\0')
	{
		ft_putendl_fd("Error: Multiple elements on same line", 2);
		return (1);
	}
	return (0);
}

static int	parse_line_result(t_map *data, char *line)
{
	int	result;

	result = route_texture_element(data, line);
	if (result >= 0)
	{
		if (result == 0 && ft_strncmp(line, "NO ", 3) == 0)
			data->got_textures |= 1;
		else if (result == 0 && ft_strncmp(line, "SO ", 3) == 0)
			data->got_textures |= 2;
		else if (result == 0 && ft_strncmp(line, "WE ", 3) == 0)
			data->got_textures |= 4;
		else if (result == 0 && ft_strncmp(line, "EA ", 3) == 0)
			data->got_textures |= 8;
		return (result);
	}
	return (-1);
}

int	parse_line_element(t_map *data, char *line)
{
	int	result;

	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (*line == '\0' || *line == '\n')
		return (0);
	result = parse_line_result(data, line);
	if (result >= 0)
		return (result);
	result = route_color_element(data, line);
	if (result >= 0)
		return (result);
	if (*line == '1' || *line == '0')
		return (2);
	if (*line == ' ')
	{
		while (*line == ' ')
			line++;
		if (*line == '1' || *line == '0')
			return (2);
	}
	ft_putendl_fd("Error: Invalid element in configuration file", 2);
	return (1);
}
