/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:30:01 by dgargant          #+#    #+#             */
/*   Updated: 2025/09/19 11:26:22 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


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

void	draw_scuare(t_game *game, int x, int y)
{
	int m_x;
	int m_y;
	int maxX;
	int maxY;
	int initX;
	int rgb;

	m_x = x * 100;
	m_y = y * 100;
	maxX = m_x + 100;
	maxY = m_y + 100;
	initX = m_x;
	rgb = get_rgba(255, 255, 255, 255);
	while (m_y <= maxY)
	{
		m_x = initX;
		while(m_x <= maxX)
		{
			mlx_put_pixel(game->img, m_x, m_y, rgb);
			m_x++;
		}
		m_y++;
	}
}

int mapX = 8;
	int mapY = 8; 
	//int mapS = 64;
	int map[] =
	{
		1,1,1,1,1,1,1,1,
		1,0,0,1,0,0,0,1,
		1,0,0,1,0,0,0,1,
		1,0,0,1,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,1,0,1,
		1,0,1,0,0,0,0,1,
		1,1,1,1,1,1,1,1,
};

void	draw_map(t_game	*game)
{	
	int x;
	int y;

	y = 0;
	x = 0;
	while (y < mapY)
	{
		x = 0;
		while (x < mapX)
		{
			if (map[(y * mapX + x)] == 1)
				draw_scuare(game, x, y);
			x++;
		}
		y++;
	}
}

void draw_background(t_game *game)
{
	int x;
	int y;
	int rgb;

	x = 0;
	y = 0;
	rgb =  get_rgba(0, 0, 0, 255);
	while (y <= W_HEIGHT )
	{
		x = 0;
		while (x <= W_WIDTH)
		{
			mlx_put_pixel(game->img, x, y, rgb);
			x++;
		}
		y++;
	}
} 

void draw_player(t_game *game)
{
	int y_neg;
	int x_neg;
	int y_pos;
	int x_pos;
	int x;
	
	y_neg = game->player->s_pos_y - 8;
	y_pos = game->player->s_pos_y + 8;
	x_neg = game->player->s_pos_x - 8;
	x_pos = game->player->s_pos_x + 8;
	x =  x_neg;
	while (y_neg <= y_pos )
	{
		x_neg = x;
		while (x_neg <= x_pos )
		{
			mlx_put_pixel(game->img, x_neg, y_neg, game->player->c_player);
			x_neg++;
		}
		y_neg++;
	}
		
}

void move_player(t_game *game)
{
	draw_background(game);
	draw_map(game);
	if(mlx_is_key_down(game->mlx, MLX_KEY_W)
	 && game->player->s_pos_y - 10 > 0)
		game->player->s_pos_y -= 10;
	if(mlx_is_key_down(game->mlx, MLX_KEY_S)
	 && game->player->s_pos_y + 10 < W_HEIGHT)
		game->player->s_pos_y += 10;
	if(mlx_is_key_down(game->mlx, MLX_KEY_A)
	 && game->player->s_pos_x - 10 > 0)
		game->player->s_pos_x -= 10;
	if(mlx_is_key_down(game->mlx, MLX_KEY_D)
	&& game->player->s_pos_x + 10 < W_WIDTH)
		game->player->s_pos_x += 10;
	draw_player(game);
}

void ft_move_hook(void *param)
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

t_player *init_player(int x, int y, int rgb)
{
	t_player *player;

	player = malloc(sizeof(t_player));
	if (!player)
		return(NULL);
	player->s_pos_x = x;
	player->s_pos_y = y;
	player->c_player = rgb;
	return (player);
}

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
	game->img = img;
	int rgb =  get_rgba(255, 0, 255, 255);
	game->player = init_player(550, 250, rgb);
	draw_background(game);
	draw_player(game);
	mlx_loop_hook(game->mlx, ft_move_hook, game);
	//move_player(game);
	//mlx_put_pixel(img, 50, 50, rgb);
	//mlx_loop_hook(game->mlx, ,game);
	//int rgb =  get_rgba(255, 0, 255, 255);
	/*int x;
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
	}*/
	game->map = map;
	return (game);
}


int main()
{
	t_map	map;
	t_game	*game;

	game = NULL;
	/*Deberiamos tener una funcion que inicialice 
		todo lo que contenga la structura map*/
	ft_memset(&map, 0, sizeof(t_map));
	game = init_game(&map);
	//mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
