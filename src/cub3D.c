/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:30:01 by dgargant          #+#    #+#             */
/*   Updated: 2025/10/10 23:09:10 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


void init_variables(t_map *map, char *filename)
{
    map->player_x = -1;
    map->player_y = -1;
    map->player_dir = 0;
    map->width = 0;
    map->height = 0;
    
    // Initialize texture pointers
    map->textures.north = NULL;
    map->textures.south = NULL;
    map->textures.west = NULL;
    map->textures.east = NULL;
    
    // Initialize state flags
    map->got_textures = 0;
    map->got_colors = 0;
    map->got_map = 0;
    
    // Allocate and copy filename
    map->text = malloc(sizeof(char) * (ft_strlen(filename) + 1));
    if (!map->text)
    {
        ft_putendl_fd("Error allocating memory for map filename", 2);
        exit(EXIT_FAILURE);
    }
    ft_strlcpy(map->text, filename, ft_strlen(filename) + 1);
    map->map = NULL;
}


static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}


int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;

	p = b;
	while (len-- > 0)
		*p++ = (unsigned char)c;
	return (b);
}

/*void draw_player(void *game)
{
	
}

t_player *init_player(int x, int y)
{
	t_player *player;

	player = malloc(sizeof(t_player));
	if (!player)
		return(NULL);
	player->s_pos_x = x;
	player->s_pos_y = y;
}*/

t_game	*init_game(t_map *map)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return(NULL);
	mlx_t* mlx = mlx_init( W_WIDTH, W_HEIGHT, "Cub3D", true);
	if (!mlx)
		return(NULL);
	game->mlx = mlx;
	//game->player = init_player(map->player_x, map->player_x);
	mlx_set_window_limit(game->mlx, W_WIDTH, W_HEIGHT, W_WIDTH, W_HEIGHT);
	mlx_image_t* img = mlx_new_image(game->mlx, W_WIDTH + 1, W_HEIGHT + 1);
	if (!img || (mlx_image_to_window(game->mlx, img, 0, 0) < 0))
		ft_error();
	int rgb =  get_rgba(255, 0, 255, 255);
	mlx_put_pixel(img, 50, 50, rgb);
	//mlx_loop_hook(game->mlx, ,game);
	//int rgb =  get_rgba(255, 0, 255, 255);
	int x;
	int y;

	x = 0;
	y = 0;
	while (y <= W_HEIGHT )
	{
		x = 0;
		while (x <= W_WIDTH)
		{
			mlx_put_pixel(img, x, y, rgb);
			x++;
		}
		y++;
	}
	game->map = map;
	return (game);
}


int main(int ac, char **av)
{
	t_map	map;
	t_game	*game;
	//int i = 0;

	if (ac < 2)
	{
		ft_putendl_fd("Usage: ./cub3D <map_file>", 2);
		return (1);
	}
	
	game = NULL;
	/*Deberiamos tener una funcion que inicialice 
		todo lo que contenga la structura map*/
	ft_memset(&map, 0, sizeof(t_map));
	init_variables(&map, av[1]);	
	// Load the map from the provided file
	if (load_map(&map) != 0)
		return (1);	
	game = init_game(&map);
	//mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free(game->map->text);
	return (EXIT_SUCCESS);
}
