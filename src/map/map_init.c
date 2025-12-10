#include "../includes/cub3D.h"
# include "../libft/libft.h"

void free_textures(t_map *data)
{
    if (data->textures.north)
        free(data->textures.north);
    if (data->textures.south)
        free(data->textures.south);
    if (data->textures.west)
        free(data->textures.west);
    if (data->textures.east)
        free(data->textures.east);
    data->textures.north = NULL;
    data->textures.south = NULL;
    data->textures.west = NULL;
    data->textures.east = NULL;
}

int initialize_map_data(t_map *data)
{
    if (data->map)
    {
        for (int i = 0; data->map[i]; i++)
            free(data->map[i]);
        free(data->map);
    }
    free_textures(data);
    data->map = NULL;
    data->textures.north = NULL;
    data->textures.south = NULL;
    data->textures.west = NULL;
    data->textures.east = NULL;
    data->width = 0;
    data->height = 0;
    data->player_x = -1;
    data->player_y = -1;
    data->player_dir = 0;
    data->got_textures = 0;
    data->got_colors = 0;
    data->got_map = 0;
    return (0);
}

void mapa_memory(t_map *data)
{
    int i;

    data->map = malloc(sizeof(char *) * (data->height + 1));
    if (!data->map)
        return ;
    i = 0;
    while (i < data->height)
    {
        data->map[i] = NULL;
        i++;
    }
}