/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:29:41 by dgargant          #+#    #+#             */
/*   Updated: 2025/11/28 22:00:00 by assistant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "../libft/inc/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "../MLX42-master/include/MLX42/MLX42.h"

/* Window sizes and constants */
# define W_WIDTH 1080
# define W_HEIGHT 720
# define SPRITE_SIZE 32
# define EXIT_ERR "Error: Map validation failed"
# define PI 3.141592653
# define BLOCK 16
# define BLOCK2 64
# define T_WIDTH 64
# define T_HEIGHT 64

typedef struct s_player
{
    double      x;
    double      y;
    double      s_pos_x;
    double      s_pos_y;
    double      direction;
    double      end_x;
    double      end_y;
    double      p_ang;
    double      angle;
    int         fov;
    int         c_player;
    int         speed;
}               t_player;

typedef struct s_color
{
    int r;
    int g;
    int b;
}               t_color;

/* Texture paths parsed from configuration (.cub) */
typedef struct s_texture_paths
{
    char    *north;
    char    *south;
    char    *west;
    char    *east;
}               t_texture_paths;

/* Loaded textures for rendering (MLX textures) */
typedef struct s_textures
{
    mlx_texture_t    *wall_north;
    mlx_texture_t    *wall_south;
    mlx_texture_t    *wall_east;
    mlx_texture_t    *wall_west;
    mlx_texture_t    *t_print;
}               t_textures;

typedef struct s_map
{
    int                 player_x;
    int                 player_y;
    char                player_dir;    /* N, S, E, or W */
    int                 width;
    int                 height;
    char                *text;         /* input file path */
    char                **map;         /* actual map content */
    t_texture_paths     textures;      /* texture file paths */
    t_color             floor;         /* floor RGB color */
    t_color             ceiling;       /* ceiling RGB color */
    int                 got_textures; /* flags for required elements */
    int                 got_colors;
    int                 got_map;
}               t_map;

typedef struct s_check
{
    int     **maps;
    int     x;
    int     y;
    int     coins_left;
    int     exit_x;;
    int     exit_y;
    int     exitparse;
}               t_check;

typedef struct s_game
{
    mlx_t           *mlx;
    t_map           *map;
    t_player        *player;
    t_textures      *textures; /* loaded textures */
    mlx_image_t     *img;
    int             side;
    int             tex_x;
    int             tex_y;
    double          tex_pos;
}               t_game;

/* Map parsing functions */
char	*get_next_line(int fd);
int     load_map(t_map *data);
int     initialize_map_data(t_map *data);
int     read_file_elements(t_map *data);
int     load_map_content(t_map *data);
void    mapa_memory(t_map *data);
void    free_textures(t_map *data);
int     is_config_line(char *line);
char    *skip_config_lines(int fd);
int     load_map_lines(t_map *data, int fd, char *first_line);
int     process_line_for_elements(t_map *data, char *line, int *map_started);
int     validate_elements_after_read(t_map *data);
void    free_map_array(t_map *data);
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
int     validate_top_bottom_borders(t_map *data);
int     validate_sides_borders(t_map *data);
int     check_player_count(int player_count);

/* Game initialization functions */
t_game *init_game(t_map *map);

/* utils */
int     get_rgba(int r, int g, int b, int a);
void    ft_error(void);

/* init */
t_textures  *init_textures(void);
t_game      *init_game(t_map *map);
void        *ft_memset(void *b, int c, size_t len);
void        ft_move_hook(void *param);
void        get_map(t_game *game);

/* Init player */
void        find_player(t_game *game);
t_player    *init_player(int rgb);

/* Draw */
int         check_direction(t_game *game, int sx, int sy, int dir);
int         calculate_direction(t_game *game, float angle, int dir);
void        draw_h_line(t_game *game, float height, int start_x);
void        draw_line(t_game *game, float angle, int start_x);
void        render_view(t_game *game);
void        draw_square(t_game *game, int x, int y, int size);
void        draw_map(t_game  *game);
void        draw_background(t_game *game);

/* Draw utils */
bool        is_touching(t_game *game, float px, float py);
double      fix_distance(t_game *game, double x2, double y2);
double      distance(double x, double y);
int         get_pixel_from_image(t_game *game, int x, int y, int side);

/* Movement */
void        try_move(t_game *game, float x, float y);
void        forward_backward_movement(t_game *game, float cos_angle,
                float sin_angle);
void        left_right_movement(t_game *game);
void        handle_rotation(t_game *game);
void        move_player(t_game *game);

#endif