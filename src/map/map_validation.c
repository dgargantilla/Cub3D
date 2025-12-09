#include "../includes/cub3D.h"
# include "../libft/inc/libft.h"


static int validate_borders(t_map *data)
{
    if (!validate_top_bottom_borders(data))
        return (0);
    if (!validate_sides_borders(data))
        return (0);
    return (1);
}

static int validate_player(t_map *data)
{
    int i;
    int j;
    int player_count;
    
    player_count = 0;

    i = 0;
    while (i < data->height)
    {
        j = 0;
        while (j < data->width)
        {
            if (data->map[i][j] == 'N' || data->map[i][j] == 'S' ||
                data->map[i][j] == 'E' || data->map[i][j] == 'W')
            {
                player_count++;
                data->player_x = j;
                data->player_y = i;
                data->player_dir = data->map[i][j];
            }
            j++;
        }
        i++;
    }
    return (check_player_count(player_count));
}

static int validate_characters(t_map *data)
{
    int i;
    int j;

    i = 0;
    while (i < data->height)
    {
        j = 0;
        while (j < data->width)
        {
            if (!(data->map[i][j] == '0' || data->map[i][j] == '1' ||
                  data->map[i][j] == 'N' || data->map[i][j] == 'S' ||
                  data->map[i][j] == 'E' || data->map[i][j] == 'W' ||
                  data->map[i][j] == ' '))
            {
                ft_putendl_fd("Error: Invalid character in map", 2);
                return (0);
            }
            j++;
        }
        i++;
    }

    return (1);
}

static int validate_map_space(t_map *data)
{
    int i;
    int j;

    i = 1;
    while (i < data->height - 1)
    {
        j = 1;
        while (j < data->width - 1)
        {
            if (data->map[i][j] == '0' || data->map[i][j] == 'P')
            {
                // Check if any adjacent cell is a space
                if (data->map[i-1][j] == ' ' || data->map[i+1][j] == ' ' ||
                    data->map[i][j-1] == ' ' || data->map[i][j+1] == ' ')
                {
                    ft_putendl_fd("Error: Map has open spaces", 2);
                    return (0);
                }
            }
            j++;
        }
        i++;
    }

    return (1);
}

int validate_map(t_map *data)
{
    if (!validate_borders(data))
    {
        ft_putendl_fd("Error: Map borders are not properly closed", 2);
        return (1);
    }

    if (!validate_player(data))
        return (1);

    if (!validate_characters(data))
        return (1);

    if (!validate_map_space(data))
        return (1);

    return (0);
}