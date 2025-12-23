/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:22:40 by dgargant          #+#    #+#             */
/*   Updated: 2025/12/23 14:52:06 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_orientation(t_game *game, char c)
{
	if (c == 'N')
		game->player->p_ang = PI + (PI / 2);
	else if (c == 'S')
		game->player->p_ang = PI / 2;
	else if (c == 'E')
		game->player->p_ang = PI * 2;
	else
		game->player->p_ang = PI;
}

void	find_player(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (game->map->map[y] != NULL)
	{
		x = 0;
		while (x <= game->map->width)
		{
			c = game->map->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W' )
			{
				game->player->s_pos_y = (double)y * BLOCK2;
				game->player->s_pos_x = (double)x * BLOCK2;
				//return;
			}
			printf("%c",c);
			x++;
		}
		printf("\n");
		y++;
	}
}

t_player	*init_player(int rgb)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->end_x = 0;
	player->end_y = 0;
	player->fov = 60;
	player->speed = 2;
	player->p_ang = PI / 2;
	/*
		NORTH =  PI + (PI / 2)
		WEST = PI
		SOUTH = PI / 2
		EAST = PI * 2 
	*/
	player->c_player = rgb;
	return (player);
}
