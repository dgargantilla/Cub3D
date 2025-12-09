#include "../includes/cub3D.h"
# include "../libft/inc/libft.h"

void free_map_array(t_map *data)
{
    int i;

    if (data->map)
    {
        i = 0;
        while (data->map[i])
        {
            free(data->map[i]);
            i++;
        }
        free(data->map);
    }
    if (data->text)
        free(data->text);
}

void exit_game(t_map *data, int exit_code)
{
    if (data)
    {
        free_map_array(data);
        free_textures(data);
    }
    exit(exit_code);
}