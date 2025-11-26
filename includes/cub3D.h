/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:29:41 by dgargant          #+#    #+#             */
/*   Updated: 2025/11/26 14:59:29 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# define PI 3.141592653
# define BLOCK 16
# define BLOCK2 64
# include "../MLX42-master/include/MLX42/MLX42.h"
//# include "../MLX42-master/include/MLX42/MLX42_Int.h"

# define W_WIDTH 1080
# define W_HEIGHT 720
# define T_WIDTH 64
# define T_HEIGHT 64

typedef struct s_player
{
	// initial position
	double		x;
	double		y;
	double		s_pos_x;
	double		s_pos_y;
	double		direction;

	double		end_x;
	double		end_y;

	double		p_ang;
	double		angle;

	int			fov;
	int			c_player;
	int			speed;
}	t_player;

typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}	t_rgb;

typedef struct s_textures
{
	mlx_texture_t	*wall_north;
	mlx_texture_t	*wall_south;
	mlx_texture_t	*wall_east;
	mlx_texture_t	*wall_west;
	mlx_texture_t	*t_print;
}				t_textures;

typedef struct s_map
{
	int			player_x;
	int			player_y;
	int			width;
	int			height;
	t_rgb		*floor;
	t_rgb		*ceilling;

	char		**map;	
}	t_map;

typedef struct s_game
{
	mlx_t			*mlx;

	t_map			*map;
	t_player		*player;
	t_textures		*textures;
	mlx_image_t		*img;

	int				side;
	int				tex_x;
	int				tex_y;
	double			tex_pos;
}	t_game;

/*UTILS*/
int			get_rgba(int r, int g, int b, int a);

void		ft_error(void);

/*INIT*/
t_textures	*init_textures(void);

t_game		*init_game(t_map *map);

void		*ft_memset(void *b, int c, size_t len);

void		ft_move_hook(void *param);

void		get_map(t_game *game);

/*INIT_PLAYER*/

void		find_player(t_game *game);

t_player	*init_player(int rgb);

/*DRAW*/

int			check_direction(t_game *game, int sx, int sy, int dir);

int			calculate_direction(t_game *game, float angle, int dir);

void		draw_h_line(t_game *game, float height, int start_x);

void		draw_line(t_game *game, float angle, int start_x);

void		render_view(t_game *game);

void		draw_square(t_game *game, int x, int y, int size);

void		draw_map(t_game	*game);

void		draw_background(t_game *game);

/*DRAW_UTILS*/

bool		is_touching(t_game *game, float px, float py);

double		fix_distance(t_game *game, double x2, double y2);

double		distance(double x, double y);

int			get_pixel_from_image(t_game *game, int x, int y, int side);

/*MOVEMENT*/

void		try_move(t_game *game, float x, float y);

void		forward_backward_movement(t_game *game, float cos_angle,
				float sin_angle);	
void		left_right_movement(t_game *game);

void		handle_rotation(t_game *game);

void		move_player(t_game *game);

#endif