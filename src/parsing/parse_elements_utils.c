/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:48:19 by shirakim          #+#    #+#             */
/*   Updated: 2025/12/22 12:18:35 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	parse_texture_element(t_map *data, char *line, const char *id)
{
	if (check_duplicate_texture(data, id))
		return (1);
	if (validate_line_continuation(line + 3))
		return (1);
	if (ft_strncmp(id, "NO", 2) == 0)
		return (handle_texture(data, line + 3, &data->textures.north));
	if (ft_strncmp(id, "SO", 2) == 0)
		return (handle_texture(data, line + 3, &data->textures.south));
	if (ft_strncmp(id, "WE", 2) == 0)
		return (handle_texture(data, line + 3, &data->textures.west));
	return (handle_texture(data, line + 3, &data->textures.east));
}

int	route_texture_element(t_map *data, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (parse_texture_element(data, line, "NO"));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (parse_texture_element(data, line, "SO"));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (parse_texture_element(data, line, "WE"));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture_element(data, line, "EA"));
	return (-1);
}

int	route_color_element(t_map *data, char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color_element(data, line, 'F'));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color_element(data, line, 'C'));
	return (-1);
}
