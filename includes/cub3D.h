/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:29:41 by dgargant          #+#    #+#             */
/*   Updated: 2025/10/16 12:31:54 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#define PI 3.141592653
#define BLOCK 64
#define BLOCK2 64
# include "../MLX42-master/include/MLX42/MLX42.h"
//# include "../MLX42-master/include/MLX42/MLX42_Int.h"

#	define W_WIDTH 1920
#	define W_HEIGHT 1080

typedef struct s_player
{
	// initial position
	double		s_pos_x;
	double		s_pos_y;
	
	double		p_ang;
	//double		ang_x;
	//double		ang_y;
	
	//bariable temporal (color de player)
	int			c_player;
}	t_player;

typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}	t_rgb;


typedef struct s_textures
{
    char    *north;
    char    *south;
    char    *west;
    char    *east;
}   t_textures;

typedef struct s_map
{
	int			player_x;
	int			player_y;
	char		player_dir;    // N, S, E, or W
	int			width;
	int			height;
	char        *text;        // input file path
	t_textures  textures;     // texture paths
	t_rgb		floor;        // floor RGB color
	t_rgb		ceilling;     // ceiling RGB color
	int         got_textures; // flags for required elements
	int         got_colors;
	int         got_map;
	int         config_parsed; // flag to indicate config section is done
	char		**map;
}	t_map;


typedef struct s_game
{
	mlx_t			*mlx;

	
	t_map			*map;
	t_player		*player;
	mlx_image_t		*img;
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

/* Game initialization functions */
void    init_variables(t_map *map, char *filename);

#endif