/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:30:01 by dgargant          #+#    #+#             */
/*   Updated: 2025/11/15 13:09:15 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
#include "../libft/inc/libft.h"


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
	int x = px / BLOCK2;
	int y = py / BLOCK2;
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
				draw_square(game, x * BLOCK, y * BLOCK, BLOCK, rgb);
			x++;
		}
		y++;
	}
}

void draw_background(t_game *game)
{
	int x;
	int y;
	int rgb_ceiling;
	int rgb_floor;

	x = 0;
	y = 0;
	
	// Get ceiling and floor colors from map
	if (game->map)
	{
		rgb_ceiling = get_rgba(game->map->ceilling.r, game->map->ceilling.g, game->map->ceilling.b, 255);
		rgb_floor = get_rgba(game->map->floor.r, game->map->floor.g, game->map->floor.b, 255);
	}
	else
	{
		rgb_ceiling = get_rgba(0, 0, 0, 255);  // Default black
		rgb_floor = get_rgba(0, 0, 0, 255);    // Default black
	}
	
	while (y <= W_HEIGHT)
	{
		x = 0;
		while (x <= W_WIDTH)
		{
			// Draw ceiling in top half
			if (y < W_HEIGHT / 2)
				mlx_put_pixel(game->img, x, y, rgb_ceiling);
			// Draw floor in bottom half
			else
				mlx_put_pixel(game->img, x, y, rgb_floor);
			x++;
		}
		y++;
	}
}

double	distance(double x, double y)
{
	return(sqrt((x * x) + (y * y)));
}

double	fix_distance(t_game *game, double x1, double y1, double x2, double y2)
{
	double delta_x = x2 - x1;
	double delta_y = y2 - y1;
	double angle = atan2(delta_y, delta_x) - game->player->p_ang;
	double fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void draw_raycast(t_game *game, double start_x, int rgb, int i)
{
	double cos_ang = cos(start_x);
	double sin_ang = sin(start_x);
	double ray_y = game->player->s_pos_y;
	double ray_x = game->player->s_pos_x;
	while (!touch(ray_y, ray_x, game))
	{
		//mlx_put_pixel(game->img, ray_x, ray_y, rgb);
		ray_x += cos_ang;
		ray_y += sin_ang;	
	}
	double dist = fix_distance( game ,game->player->s_pos_x,
		game->player->s_pos_y, ray_x, ray_y);
	if (dist == 0)
		dist = 0.1;
	double height = (BLOCK2 / dist) * (W_WIDTH / 2);
	double start_y = (W_HEIGHT - height) / 2;
	if (start_y <= 0)
		start_y = 1;
	double end = start_y + height;
	if (end >= W_HEIGHT)
		end = W_HEIGHT - 1;
	printf("\nstart_y : %f", start_y);
	while (start_y < end)
	{
		mlx_put_pixel(game->img, i, start_y, rgb);
		start_y++;
	}
}

void move_player(t_game *game)
{
	int rgb = get_rgba(255, 0, 255, 255);
	draw_background(game);
	//draw_map(game, rgb);
	
	//char **map = game->map->map;
	//int x = (int)game->player->s_pos_x / BLOCK;
	//int y = (int)game->player->s_pos_y / BLOCK;
	double speed_ang = 0.03;
	double cos_ang = cos(game->player->p_ang);
	double sin_ang = sin(game->player->p_ang);
	/*if(mlx_is_key_down(game->mlx, MLX_KEY_W))
		printf("x %d, y %d", x, y);*/
	double dob_pi = PI * 2;

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
		game->player->s_pos_y += sin_ang * 3;
		game->player->s_pos_x += cos_ang * 3;	
	}
	if(mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		game->player->s_pos_y -= sin_ang * 3;
		game->player->s_pos_x -= cos_ang * 3;
	}
	if(mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->player->s_pos_y -= cos_ang * 3;
		game->player->s_pos_x += sin_ang * 3;
	}
	if(mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->player->s_pos_y += cos_ang * 3;
		game->player->s_pos_x -= sin_ang * 3;
	}
	/*if(mlx_is_key_down(game->mlx, MLX_KEY_W))
	printf("x %d, y %d", x, y);*/
	
	//RAYCAST
	rgb = get_rgba(0, 0, 255, 255);
	double	fraction = PI / 3 / W_WIDTH;
	double	start_x = game->player->p_ang - PI / 6;
	int i = 0;
	while (i < W_WIDTH)
	{
		draw_raycast(game, start_x, rgb, i);
		start_x += fraction;
		i++;
	}
	
	
	//rgb = get_rgba(255, 0, 255, 255);
	//draw_square(game, game->player->s_pos_x, game->player->s_pos_y, BLOCK / 4 , rgb);
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
		while (game->map->map[y][x] != '\0')
		{
			c = game->map->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player->s_pos_y = (double)y * BLOCK2;
				game->player->s_pos_x = (double)x * BLOCK2;
				game->map->player_x = x;
				game->map->player_y = y;
				game->map->player_dir = c;
				return; // Found player, exit
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
	mlx_t* mlx = mlx_init(W_WIDTH, W_HEIGHT, "Cub3D", true);
	if (!mlx)
		return(NULL);
	game->mlx = mlx;
	game->map = map;
	// get_map(game); // REMOVED: map is now loaded in main()
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
	mlx_loop_hook(game->mlx, ft_move_hook, game);
	return (game);
}


int main(int argc, char **argv)
{
	t_map	map;
	t_game	*game;

	if (argc != 2)
	{
		ft_putendl_fd("Error\nUsage: ./Cub3D <map.cub>", 2);
		return (EXIT_FAILURE);
	}

	game = NULL;
	ft_memset(&map, 0, sizeof(t_map));
	
	map.map = NULL;
	init_variables(&map, argv[1]);
	
	if (load_map(&map) != 0)
	{
		ft_putendl_fd("Error\nFailed to load map", 2);
		return (EXIT_FAILURE);
	}
	game = init_game(&map);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
