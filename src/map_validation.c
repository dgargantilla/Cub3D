#include "../includes/cub3D.h"
#include "../libft/inc/libft.h"

static int is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

static int validate_borders(t_map *data)
{
    int i;
    int j;

    // Check first and last row - must be all '1's
    for (j = 0; j < data->width; j++)
    {
        if (j >= (int)ft_strlen(data->map[0]))
            return (0);
        if (data->map[0][j] != '1')
            return (0);
    }

    // Check last row
    for (j = 0; j < data->width; j++)
    {
        if (j >= (int)ft_strlen(data->map[data->height - 1]))
            return (0);
        if (data->map[data->height - 1][j] != '1')
            return (0);
    }

    // Check first and last column of each row
    for (i = 0; i < data->height; i++)
    {
        if (data->map[i][0] != '1')
            return (0);
        if (data->map[i][data->width - 1] != '1')
            return (0);
    }

    return (1);
}

static int validate_player(t_map *data)
{
    int i;
    int j;
    int player_count = 0;

    for (i = 0; i < data->height; i++)
    {
        for (j = 0; j < data->width; j++)
        {
            if (data->map[i][j] == 'N' || data->map[i][j] == 'S' ||
                data->map[i][j] == 'E' || data->map[i][j] == 'W')
            {
                player_count++;
                data->player_x = j;
                data->player_y = i;
                data->player_dir = data->map[i][j];
            }
        }
    }

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

static int validate_characters(t_map *data)
{
    int i;
    int j;

    for (i = 0; i < data->height; i++)
    {
        for (j = 0; j < data->width; j++)
        {
            if (!is_valid_char(data->map[i][j]))
            {
                ft_putendl_fd("Error: Invalid character in map", 2);
                return (0);
            }
        }
    }

    return (1);
}

static int validate_map_space(t_map *data)
{
    int i;
    int j;

    for (i = 1; i < data->height - 1; i++)
    {
        for (j = 1; j < data->width - 1; j++)
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
        }
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