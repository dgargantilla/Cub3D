/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:48:19 by shirakim          #+#    #+#             */
/*   Updated: 2025/12/29 11:42:34 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	process_line_(t_map *data, char *line, int *map_started)
{
	int	result;
	int	len;
	int	i;

	result = parse_line_element(data, line);
	if (result == 1)
		return (1);
	else if (result == 2)
		*map_started = 1;
	if (*map_started)
	{
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
		len = ft_strlen(line);
		i = 0;
		while (i < len && line[i] == ' ')
			i++;
		if (i == len)
			return (0);
		if (len > data->width)
			data->width = len;
		data->height++;
	}
	return (0);
}

int	validate_elements_after_read(t_map *data)
{
	if ((data->got_textures != 15) || (data->got_colors != 3))
	{
		ft_putendl_fd("Error: Missing required elements", 2);
		return (1);
	}
	if (data->height == 0 || data->width == 0)
	{
		ft_putendl_fd("Error: No map found in file", 2);
		return (1);
	}
	if (data->width >= 150 || data->height >= 150)
	{
		ft_putendl_fd("Error: Map dimensions exceed limits", 2);
		return (1);
	}
	return (0);
}

int	read_lines_from_file(t_map *data)
{
	int		fd;
	char	*line;
	int		map_started;

	map_started = 0;
	fd = open(data->text, O_RDONLY);
	if (fd == -1)
		return (1);
	data->width = 0;
	data->height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (process_line_(data, line, &map_started) == 1)
		{
			free(line);
			close(fd);
			get_next_line(-1);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	read_file_elements(t_map *data)
{
	if (read_lines_from_file(data) != 0)
		return (1);
	return (validate_elements_after_read(data));
}
