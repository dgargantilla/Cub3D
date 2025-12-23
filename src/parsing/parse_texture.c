/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:00:00 by shirakim          #+#    #+#             */
/*   Updated: 2025/12/22 10:11:15 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	try_asset_path(char **texture_path, const char *prefix)
{
	char	*path;
	char	*basename;
	int		fd;

	basename = ft_strrchr(*texture_path, '/');
	if (basename)
		basename++;
	else
		basename = *texture_path;
	path = ft_strjoin(prefix, basename);
	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		free(*texture_path);
		*texture_path = ft_strdup(path);
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

int	try_texture_paths(char **texture_path)
{
	if (try_asset_path(texture_path, "assets/"))
		return (1);
	if (try_asset_path(texture_path, "textures/"))
		return (1);
	return (0);
}

int	check_texture_file(char **texture_path)
{
	int	fd;

	fd = open(*texture_path, O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		return (1);
	}
	if (try_texture_paths(texture_path))
		return (1);
	return (0);
}

int	prepare_texture_path(char *line, char **texture_path)
{
	char	*trimmed;

	while (*line && *line == ' ')
		line++;
	if (!*line)
	{
		ft_putendl_fd("Error: Missing texture path", 2);
		return (0);
	}
	if (*texture_path)
		free(*texture_path);
	trimmed = ft_strtrim(line, " \t\r\n");
	if (!trimmed)
		return (0);
	*texture_path = ft_strdup(trimmed);
	free(trimmed);
	return (*texture_path != NULL);
}

int	handle_texture(t_map *data, char *line, char **texture_path)
{
	(void)data;
	if (!prepare_texture_path(line, texture_path))
		return (1);
	if (!check_texture_file(texture_path))
	{
		ft_putendl_fd("Error: Cannot open texture file", 2);
		return (1);
	}
	return (0);
}
