/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:29:41 by dgargant          #+#    #+#             */
/*   Updated: 2025/10/10 23:09:11 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../libft/inc/libft.h"
#include <unistd.h>
#include <fcntl.h>
# include "../MLX42-master/include/MLX42/MLX42.h"
//# include "../MLX42-master/include/MLX42/MLX42_Int.h"

#	define W_WIDTH 1920
#	define W_HEIGHT 1080
#	define SPRITE_SIZE 32
#	define EXIT_ERR "Error: Map validation failed"

typedef struct s_player
{
	// initial position
	int			s_pos_x;
	int			s_pos_y;
}	t_player;


typedef struct s_textures
{
    char    *north;
    char    *south;
    char    *west;
    char    *east;
}   t_textures;

typedef struct s_color
{
    int r;
    int g;
    int b;
}   t_color;

typedef struct s_map
{
    int         player_x;
    int         player_y;
    char        player_dir;    // N, S, E, or W
    int         width;
    int         height;
    char        *text;        // input file path
    char        **map;        // actual map content
    t_textures  textures;     // texture paths
    t_color     floor;        // floor RGB color
    t_color     ceiling;      // ceiling RGB color
    int         got_textures; // flags for required elements
    int         got_colors;
    int         got_map;
}   t_map;


typedef struct s_check
{
	int		**maps;
	int		x;
	int		y;
	int		coins_left;
}	t_check;

typedef struct s_game
{
	mlx_t			*mlx;

	
	t_map			*map;
	t_player		*player;
}	t_game;

/* Map parsing functions */
void    upload_map_content(t_map *map);
int     load_map(t_map *map);
void    mapa_dimention(t_map *data);
void    mapa_memory(t_map *data);
void    exit_game(t_map *data, int exit_code);

/* Element parsing functions */
int     parse_line_element(t_map *data, char *line);

/* Map validation functions */
int     validate_map(t_map *data);
t_check *do_check(int height, int width);
void    find_position(t_check *check, t_map *data);
void    flood_fill(int x, int y, t_check *check, t_map *data);
void    free_check(t_check *check, int height);
void    exit_error(char *message);
void    ft_check_borders(t_map *data);

/* Game initialization functions */
t_game *init_game(t_map *map);
void init_variables(t_map *map, char *filename);

#endif