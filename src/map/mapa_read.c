#include "../includes/cub3D.h"
# include "../libft/inc/libft.h"

int load_map(t_map *data)
{
    initialize_map_data(data);
    if (read_file_elements(data) != 0)
    {
        printf("Error reading file elements\n");
        return (1);
    }
    mapa_memory(data);
    if (load_map_content(data) != 0)
    {
        printf("Error loading map content\n");
        free_map_array(data);
        return (1);
    }
    if (validate_map(data) != 0)
    {
        printf("Map validation failed\n");
        free_map_array(data);
        return (1);
    }
    return (0);
}