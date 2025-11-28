/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:47:22 by dgargant          #+#    #+#             */
/*   Updated: 2025/11/26 14:28:11 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <ctype.h>
#include <errno.h>

static int str_to_hex(const char *hex)
{
	if (!hex)
		return (-1);
	if (hex[0] == '#')
		hex++;
	return ((int)strtol(hex, NULL, 16));
}

static int is_ext(const char *path, const char *ext)
{
	const char *p = strrchr(path, '.');
	if (!p)
		return (0);
	return (ft_strncmp(p, ext, ft_strlen(ext)) == 0);
}

/* Very small XPM3 parser: supports only ASCII keys and hex colors (#RRGGBB) */
static mlx_texture_t *load_xpm3_as_texture(const char *path)
{
	FILE *f;
	char buf[1024];
	char *s;
	int width = 0, height = 0, ncolors = 0, cpp = 0;
	int i, j;

	f = fopen(path, "r");
	if (!f)
		return (NULL);
	/* read lines until first quoted line */
	while (fgets(buf, sizeof(buf), f))
	{
		s = strchr(buf, '"');
		if (s)
		{
			char *e = strchr(s + 1, '"');
			if (!e) continue;
			char temp[1024];
			int len = (int)(e - s - 1);
			if (len >= (int)sizeof(temp)) errno = EINVAL;
			memcpy(temp, s + 1, len);
			temp[len] = '\0';
			/* parse header */
			if (sscanf(temp, "%d %d %d %d", &width, &height, &ncolors, &cpp) == 4)
			{
				break;
			}
		}
	}
	if (width <= 0 || height <= 0 || ncolors <= 0 || cpp <= 0)
	{
		fclose(f);
		return (NULL);
	}

	/* read color table */
	typedef struct s_color_map { char key[8]; int rgba; } t_color_map;
	t_color_map *colmap = malloc(sizeof(t_color_map) * ncolors);
	if (!colmap) { fclose(f); return (NULL); }
	for (i = 0; i < ncolors; i++)
	{
		if (!fgets(buf, sizeof(buf), f)) { free(colmap); fclose(f); return (NULL); }
		s = strchr(buf, '"');
		if (!s) { free(colmap); fclose(f); return (NULL); }
		char *e = strchr(s + 1, '"');
		if (!e) { free(colmap); fclose(f); return (NULL); }
		int len = (int)(e - s - 1);
		char tmp[256];
		memcpy(tmp, s + 1, len);
		tmp[len] = '\0';
		/* key = first cpp chars */
		if (len < cpp + 3) { free(colmap); fclose(f); return (NULL); }
		memset(colmap[i].key, 0, sizeof(colmap[i].key));
		memcpy(colmap[i].key, tmp, cpp);
		/* find '#' color */
		char *hash = strchr(tmp, '#');
		if (!hash)
		{
			/* check for 'None' transparent */
			if (strstr(tmp, "None") || strstr(tmp, "none"))
				colmap[i].rgba = (0 << 24) | (0 << 16) | (0 << 8) | 0; /* fully transparent */
			else
				colmap[i].rgba = 0x00FF00FF; /* magenta placeholder */
		}
		else
		{
			int val = str_to_hex(hash);
			int r = (val >> 16) & 0xFF;
			int g = (val >> 8) & 0xFF;
			int b = (val) & 0xFF;
			colmap[i].rgba = (r << 24) | (g << 16) | (b << 8) | 0xFF;
		}
	}

	/* allocate texture */
	mlx_texture_t *texture = malloc(sizeof(mlx_texture_t));
	if (!texture) { free(colmap); fclose(f); return (NULL); }
	texture->width = width;
	texture->height = height;
	texture->bytes_per_pixel = 4;
	texture->pixels = malloc(width * height * 4);
	if (!texture->pixels) { free(colmap); free(texture); fclose(f); return (NULL); }

	/* read pixels */
	for (j = 0; j < height; j++)
	{
		if (!fgets(buf, sizeof(buf), f)) { free(colmap); free(texture->pixels); free(texture); fclose(f); return (NULL); }
		s = strchr(buf, '"');
		if (!s) { j--; continue; }
		char *e = strchr(s + 1, '"');
		if (!e) { free(colmap); free(texture->pixels); free(texture); fclose(f); return (NULL); }
		int len = (int)(e - s - 1);
		char *line = malloc(len + 1);
		memcpy(line, s + 1, len);
		line[len] = '\0';
		/* parse line by cpp groups */
		for (i = 0; i < width; i++)
		{
			char key[8];
			memcpy(key, &line[i * cpp], cpp);
			key[cpp] = '\0';
			int rgba = 0xFF00FFFF;
			for (int k = 0; k < ncolors; k++)
			{
				if (strncmp(colmap[k].key, key, cpp) == 0)
				{
					rgba = colmap[k].rgba;
					break;
				}
			}
			/* write pixel in rgba order - note MLX uses RGBA bytes; we stored r in highest byte above */
			uint8_t r = (rgba >> 24) & 0xFF;
			uint8_t g_ = (rgba >> 16) & 0xFF;
			uint8_t b_ = (rgba >> 8) & 0xFF;
			uint8_t a = rgba & 0xFF;
			uint8_t *p = &texture->pixels[(j * width + i) * 4];
			p[0] = r; p[1] = g_; p[2] = b_; p[3] = a;
		}
		free(line);
	}

	free(colmap);
	fclose(f);
	return (texture);
}

/* Create a small placeholder texture (T_WIDTH x T_HEIGHT) with given color */
static mlx_texture_t *create_placeholder(int w, int h, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	mlx_texture_t *texture = malloc(sizeof(mlx_texture_t));
	if (!texture)
		return (NULL);
	texture->width = w;
	texture->height = h;
	texture->bytes_per_pixel = 4;
	texture->pixels = malloc(w * h * 4);
	if (!texture->pixels)
	{
		free(texture);
		return (NULL);
	}
	for (int i = 0; i < w * h; i++)
	{
		texture->pixels[i * 4 + 0] = r;
		texture->pixels[i * 4 + 1] = g;
		texture->pixels[i * 4 + 2] = b;
		texture->pixels[i * 4 + 3] = a;
	}
	return (texture);
}

static mlx_texture_t *create_solid_texture(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	mlx_texture_t *texture = malloc(sizeof(mlx_texture_t));
	if (!texture) return NULL;
	texture->width = 1;
	texture->height = 1;
	texture->bytes_per_pixel = 4;
	texture->pixels = malloc(4);
	if (!texture->pixels) { free(texture); return NULL; }
	texture->pixels[0] = r;
	texture->pixels[1] = g;
	texture->pixels[2] = b;
	texture->pixels[3] = a;
	return texture;
}

/*void	texture_error(t_game *game)
{
	if (game->textures->wall_north)
		mlx_delete_texture(game->textures->wall_north);
	if (game->textures->wall_south)
		mlx_destroy_image(game->textures->wall_south);
	if (game->textures->wall_east)
		mlx_destroy_image(game->textures->wall_east);
	if (game->textures->wall_west)
		mlx_destroy_image(game->textures->wall_west);
	free(game->mlx);
	write(1, "Texture error\n", 15);
	exit(1);
}*/

t_textures	*init_textures(t_map *map)
{
	t_textures	*texture;

	texture = malloc(sizeof(t_textures));
	if (texture == NULL)
		return (NULL);
	texture->wall_north = NULL;
	texture->wall_south = NULL;
	texture->wall_east = NULL;
	texture->wall_west = NULL;
	/* Load textures from the parsed map file paths if available */
	if (map && map->textures.north)
	{
		printf("Loading north texture: %s\n", map->textures.north);
		if (is_ext(map->textures.north, ".png"))
			texture->wall_north = mlx_load_png(map->textures.north);
		else if (is_ext(map->textures.north, ".xpm"))
			texture->wall_north = load_xpm3_as_texture(map->textures.north);
		if (!texture->wall_north)
		{
			printf("Warning: failed to load north texture '%s', using placeholder\n", map->textures.north);
			texture->wall_north = create_placeholder(T_WIDTH, T_HEIGHT, 255, 0, 255, 255);
		}
	}
	if (map && map->textures.south)
	{
		printf("Loading south texture: %s\n", map->textures.south);
		if (is_ext(map->textures.south, ".png"))
			texture->wall_south = mlx_load_png(map->textures.south);
		else if (is_ext(map->textures.south, ".xpm"))
			texture->wall_south = load_xpm3_as_texture(map->textures.south);
		if (!texture->wall_south)
		{
			printf("Warning: failed to load south texture '%s', using placeholder\n", map->textures.south);
			texture->wall_south = create_placeholder(T_WIDTH, T_HEIGHT, 255, 0, 255, 255);
		}
	}
	if (map && map->textures.east)
	{
		printf("Loading east texture: %s\n", map->textures.east);
		if (is_ext(map->textures.east, ".png"))
			texture->wall_east = mlx_load_png(map->textures.east);
		else if (is_ext(map->textures.east, ".xpm"))
			texture->wall_east = load_xpm3_as_texture(map->textures.east);
		if (!texture->wall_east)
		{
			printf("Warning: failed to load east texture '%s', using placeholder\n", map->textures.east);
			texture->wall_east = create_placeholder(T_WIDTH, T_HEIGHT, 255, 0, 255, 255);
		}
	}
	if (map && map->textures.west)
	{
		printf("Loading west texture: %s\n", map->textures.west);
		if (is_ext(map->textures.west, ".png"))
			texture->wall_west = mlx_load_png(map->textures.west);
		else if (is_ext(map->textures.west, ".xpm"))
			texture->wall_west = load_xpm3_as_texture(map->textures.west);
		if (!texture->wall_west)
		{
			printf("Warning: failed to load west texture '%s', using placeholder\n", map->textures.west);
			texture->wall_west = create_placeholder(T_WIDTH, T_HEIGHT, 255, 0, 255, 255);
		}
	}
	/* provide fallbacks for missing textures (create solid color textures) */
	if (!texture->wall_north)
		texture->wall_north = create_solid_texture(255, 0, 255, 255);
	if (!texture->wall_south)
		texture->wall_south = create_solid_texture(255, 128, 0, 255);
	if (!texture->wall_east)
		texture->wall_east = create_solid_texture(0, 255, 0, 255);
	if (!texture->wall_west)
		texture->wall_west = create_solid_texture(0, 0, 255, 255);
	return (texture);
}
