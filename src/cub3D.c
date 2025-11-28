/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:30:01 by dgargant          #+#    #+#             */
/*   Updated: 2025/11/28 19:56:51 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;

	p = b;
	while (len-- > 0)
		*p++ = (unsigned char)c;
	return (b);
}

void	ft_move_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->mlx);
		return ;
	}
	move_player(game);
}

void	get_map(t_game *game)
{
	game->map->map = malloc(sizeof(char *) * 11);
	game->map->map[0] = "11111111111";
	game->map->map[1] = "10000000001";
	game->map->map[2] = "10000000001";
	game->map->map[3] = "10001111001";
	game->map->map[4] = "10000N01001";
	game->map->map[5] = "10000001001";
	game->map->map[6] = "10000000001";
	game->map->map[7] = "10001000001";
	game->map->map[8] = "10001000001";
	game->map->map[9] = "11111111111";
	game->map->map[10] = NULL;
	game->map->width = 11;
	game->map->height = 11;
}

t_game	*init_game(t_map *map)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	mlx_t *mlx = mlx_init(W_WIDTH, W_HEIGHT, "Cub3D", true);
	if (!mlx)
		return(NULL);
	game->side = 1;
	game->tex_x = 0;
	game->tex_y = 0;
	game->tex_pos = 0;
	game->mlx = mlx;
	game->map = map;
	/* If no map was parsed, fallback to builtin demo map */
	if (!game->map->map)
		get_map(game);
	mlx_set_window_limit(game->mlx, W_WIDTH, W_HEIGHT, W_WIDTH, W_HEIGHT);
	mlx_image_t* img = mlx_new_image(game->mlx, W_WIDTH + 1, W_HEIGHT + 1);
	if (!img || (mlx_image_to_window(game->mlx, img, 0, 0) < 0))
		ft_error();
	game->img = img;
	game->player = init_player(get_rgba(255, 0, 255, 255));
	find_player(game);
	game->textures = init_textures(map);
	mlx_loop_hook(game->mlx, ft_move_hook, game);
	return (game);
}

int	main(int ac, char **av)
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
	ft_memset(&map, 0, sizeof(t_map));
	map.map = NULL;
	map.text = ft_strdup(av[1]);
	if (!map.text)
		return (1);
	if (load_map(&map) != 0)
	{
		ft_putendl_fd("Failed to load map", 2);
		return (1);
	}
	game = init_game(&map);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free(game->map->text);
	return (EXIT_SUCCESS);
}
