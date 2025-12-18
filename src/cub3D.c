/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:30:01 by dgargant          #+#    #+#             */
/*   Updated: 2025/12/18 15:25:11 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "../libft/libft.h"

void	ft_move_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		destroy_all(game);
	move_player(game);
}

t_game	*init_game(t_map *map)
{
	t_game		*game;
	mlx_t		*mlx;
	mlx_image_t	*img;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (NULL);
	mlx = mlx_init(W_WIDTH, W_HEIGHT, "Cub3D", true);
	if (!mlx)
		return (NULL);
	game->side = 1;
	game->mlx = mlx;
	game->map = map;
	mlx_set_window_limit(game->mlx, W_WIDTH, W_HEIGHT, W_WIDTH, W_HEIGHT);
	img = mlx_new_image(game->mlx, W_WIDTH + 1, W_HEIGHT + 1);
	if (!img || (mlx_image_to_window(game->mlx, img, 0, 0) < 0))
		ft_error();
	game->img = img;
	game->player = init_player(get_rgba(255, 0, 255, 255));
	find_player(game);
	check_orientation(game, game->map->player_dir);
	game->textures = init_textures(game);
	mlx_loop_hook(game->mlx, ft_move_hook, game);
	return (game);
}

int	main(int ac, char **av)
{
	t_map	map;
	t_game	*game;

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
		free(map.text);
		ft_putendl_fd("Failed to load map", 2);
		return (1);
	}
	game = init_game(&map);
	mlx_loop(game->mlx);
	destroy_all(game);
	return (EXIT_SUCCESS);
}
