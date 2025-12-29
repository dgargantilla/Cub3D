/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 23:32:43 by shirakim          #+#    #+#             */
/*   Updated: 2025/12/29 12:51:49 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	is_config_line(char *line)
{
	int	idx;

	if (!line)
		return (0);
	idx = 0;
	while (line[idx] == ' ' || line[idx] == '\t')
		idx++;
	return (ft_strncmp(line + idx, "NO ", 3) == 0
		|| ft_strncmp(line + idx, "SO ", 3) == 0
		|| ft_strncmp(line + idx, "WE ", 3) == 0
		|| ft_strncmp(line + idx, "EA ", 3) == 0
		|| ft_strncmp(line + idx, "F ", 2) == 0
		|| ft_strncmp(line + idx, "C ", 2) == 0
		|| ft_strlen(line + idx) == 0);
}

char	*process_config_line(char *line)
{
	int	len;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

char	*skip_config_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		line = process_config_line(line);
		if (!is_config_line(line))
			return (line);
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}

int	load_map_lines(t_map *data, int fd, char *first_line)
{
	char	*line;
	int		i;

	i = 0;
	line = first_line;
	while (line && i < data->height)
	{
		data->map[i++] = ft_strdup(line);
		if (!data->map[i - 1])
			return (free(line), close(fd), 1);
		free(line);
		line = process_config_line(get_next_line(fd));
	}
	free(line);
	get_next_line(-1);
	close(fd);
	data->map[i] = NULL;
	data->height = i;
	return (0);
}

int	load_map_content(t_map *data)
{
	int		fd;
	char	*first_line;

	fd = open(data->text, O_RDONLY);
	if (fd == -1)
		return (1);
	first_line = skip_config_lines(fd);
	if (!first_line)
	{
		close(fd);
		return (1);
	}
	return (load_map_lines(data, fd, first_line));
}
