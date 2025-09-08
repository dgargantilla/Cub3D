/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:29:41 by dgargant          #+#    #+#             */
/*   Updated: 2025/09/08 11:45:25 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
# include "../MLX42-master/include/MLX42/MLX42.h"
//# include "../MLX42-master/include/MLX42/MLX42_Int.h"

#	define W_WIDTH 1920
#	define W_HEIGHT 1080

typedef struct s_player
{
	// initial position
	int			s_pos_x;
	int			s_pos_y;
}	t_player;


typedef struct s_map
{
	int			player_x;
	int			player_y;
	
	char		**map;	
}	t_map;


typedef struct s_game
{
	mlx_t			*mlx;

	
	t_map			*map;
	t_player		*player;
}	t_game;


#endif