/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:30:01 by dgargant          #+#    #+#             */
/*   Updated: 2025/10/10 10:54:28 by dgargant         ###   ########.fr       */
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

/*void	draw_scuare(t_game *game, int x, int y)
{
	int m_x;
	int m_y;
	int maxX;
	int maxY;
	int initX;
	int rgb;

	m_x = x * BLOCK;
	m_y = y * BLOCK;
	maxX = m_x + BLOCK;
	maxY = m_y + BLOCK;
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
}*/

/*void	draw_vector(t_game *game)
{
	
}*/

/*int mapX = 8;
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
};*/





/*void draw_player(t_game *game)
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
		
}*/
/*bool player_movement(t_game *game)
{
	if (game->player->s_pos_y - 10 <= 0)
		return (false);
	if (game->player->s_pos_y + 10 >= W_HEIGHT)
	return (false);
	if (game->player->s_pos_x - 10 <= 0)
	return (false);
	if (game->player->s_pos_x + 10 >= W_WIDTH)
		return (false);
	return (true);
}*/



bool touch(float py, float px, t_game *game)
{
	int x = px / BLOCK;
	int y = py / BLOCK;
	if(game->map->map[y][x] == '1')
		return (true);
	return (false);
}


void draw_square(t_game  *game, int x, int y, int size, int rgb)
{
	int i;

	i = 0;
	while (i++ < size)
		mlx_put_pixel(game->img, x + i, y, rgb);
	i = 0;
	while (i++ < size)
		mlx_put_pixel(game->img, x, y + i, rgb);
	i =  0;
	while (i++ < size)
	{
		mlx_put_pixel(game->img, x + size, y + i, rgb);
	}
	i = 0;
	while (i++ < size)
	{
		mlx_put_pixel(game->img, x + i, y + size, rgb);
	}
}

void	draw_map(t_game	*game, int rgb)
{	
	char 	**map;
	int 	x;
	int 	y;

	y = 0;
	x = 0;
	map = game->map->map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(game, x * 64, y * 64, 64, rgb);
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

void move_player(t_game *game)
{
	int rgb = get_rgba(255, 0, 255, 255);
	draw_background(game);
	draw_map(game, rgb);
	
	//char **map = game->map->map;
	//int x = (int)game->player->s_pos_x / BLOCK;
	//int y = (int)game->player->s_pos_y / BLOCK;
	float speed_ang = 0.1;
	float cos_ang = cos(game->player->p_ang);
	float sin_ang = sin(game->player->p_ang);
	/*if(mlx_is_key_down(game->mlx, MLX_KEY_W))
		printf("x %d, y %d", x, y);*/
	float dob_pi = (PI * 2);

	/// ROTACION
	if(mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player->p_ang += speed_ang;
	if(mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player->p_ang -= speed_ang;
	if(game->player->p_ang > dob_pi)
		game->player->p_ang = 0;
	if(game->player->p_ang < 0)
		game->player->p_ang = dob_pi;

	/// MOVEMENT
	if(mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		game->player->s_pos_y += sin_ang * 5;
		game->player->s_pos_x += cos_ang * 5;	
	}
	if(mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		game->player->s_pos_y -= sin_ang * 5;
		game->player->s_pos_x -= cos_ang * 5;
	}
	if(mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->player->s_pos_y -= sin_ang * 5;
		game->player->s_pos_x += cos_ang * 5;
	}
	if(mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->player->s_pos_y += sin_ang * 5;
		game->player->s_pos_x -= cos_ang * 5;
	}
	/*if(mlx_is_key_down(game->mlx, MLX_KEY_W))
		printf("x %d, y %d", x, y);*/
	
	float ray_y = game->player->s_pos_y;
	float ray_x = game->player->s_pos_x;
	rgb = get_rgba(0, 0, 255, 255);
	while (!touch(ray_y, ray_x, game))
	{
		mlx_put_pixel(game->img, ray_x, ray_y, rgb);
		ray_x += cos_ang;
		ray_y += sin_ang;	
	}
	rgb = get_rgba(255, 0, 255, 255);
	draw_square(game, game->player->s_pos_x, game->player->s_pos_y, 10 , rgb);
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


void get_map(t_game *game)
{
	game->map->map = malloc(sizeof(char *) * 11);
	game->map->map[0] = "11111111111";
	game->map->map[1] = "10000000001";
	game->map->map[2] = "10000000001";
	game->map->map[3] = "10001111001";
	game->map->map[4] = "10000P01001";
	game->map->map[5] = "10000001001";
	game->map->map[6] = "10000000001";
	game->map->map[7] = "10001000001";
	game->map->map[8] = "10001000001";
	game->map->map[9] = "11111111111";
	game->map->map[10] = NULL;
}

void find_player(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (game->map->map[y] != NULL)
	{
		x = 0;
		while (x < 11 )
		{
			c = game->map->map[y][x];
			if (c == 'P')
			{
				game->player->s_pos_y = (double)y *BLOCK;
				game->player->s_pos_x = (double)x *BLOCK;
			}
			x++;
		}
		y++;
	}
}

t_player *init_player(int rgb)
{
	t_player *player;

	player = malloc(sizeof(t_player));
	if (!player)
		return(NULL);
	player->s_pos_x = 0;
	player->s_pos_y = 0;
	player->p_ang = PI / 2;
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

	game->map = map;
	get_map(game);
	mlx_set_window_limit(game->mlx, W_WIDTH, W_HEIGHT, W_WIDTH, W_HEIGHT);
	mlx_image_t* img = mlx_new_image(game->mlx, W_WIDTH + 1, W_HEIGHT + 1);
	if (!img || (mlx_image_to_window(game->mlx, img, 0, 0) < 0))
		ft_error();
	game->img = img;
	int rgb =  get_rgba(255, 0, 255, 255);
	game->player = init_player(rgb);
	find_player(game);
	printf("posicion x: %f, posicion y: %f", game->player->s_pos_x, game->player->s_pos_y);
	draw_background(game);
	//draw_square(game, game->player->s_pos_x, game->player->s_pos_y, 10 , rgb);
	mlx_loop_hook(game->mlx, ft_move_hook, game);
	//move_player(game);
	//mlx_put_pixel(img, 50, 50, rgb);
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
	
	map.map = NULL;
	game = init_game(&map);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
