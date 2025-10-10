/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:29:41 by dgargant          #+#    #+#             */
/*   Updated: 2025/10/10 09:45:54 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#define PI 3,141592653
#define BLOCK 64
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


typedef struct s_map
{
	
	int			player_x;
	int			player_y;
	t_rgb		*floor;
	t_rgb		*ceilling;
	
	char		**map;	
}	t_map;


typedef struct s_game
{
	mlx_t			*mlx;

	
	t_map			*map;
	t_player		*player;
	mlx_image_t		*img;
}	t_game;


#endif