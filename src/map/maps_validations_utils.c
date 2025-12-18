#include "../includes/cub3D.h"

int validate_top_bottom_borders(t_map *data)
{
    int j;

    j = 0;
    while (j < data->width)
    {
        if (j >= (int)ft_strlen(data->map[0]))
            return (0);
        if (data->map[0][j] != '1')
            return (0);
        j++;
    }

    j = 0;
    while (j < data->width)
    {
        if (j >= (int)ft_strlen(data->map[data->height - 1]))
            return (0);
        if (data->map[data->height - 1][j] != '1')
            return (0);
        j++;
    }
    return (1);
}

int validate_sides_borders(t_map *data)
{
    int i;

    i = 0;
    while (i < data->height)
    {
        if (data->map[i][0] != '1')
            return (0);
        if (data->map[i][data->width - 1] != '1')
            return (0);
        i++;
    }
    return (1);
}

int check_player_count(int player_count)
{
    if (player_count == 0)
    {
        ft_putendl_fd("Error: No player (P) found in map", 2);
        return (0);
    }
    if (player_count > 1)
    {
        ft_putendl_fd("Error: Multiple players found in map", 2);
        return (0);
    }
    return (1);
}