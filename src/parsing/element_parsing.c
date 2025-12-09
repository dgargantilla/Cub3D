#include "../includes/cub3D.h"
# include "../libft/inc/libft.h"

int process_line_for_elements(t_map *data, char *line, int *map_started)
{
    int result;
    result = parse_line_element(data, line);
    if (result == 1)
        return (1);
    else if (result == 2)
        *map_started = 1;
    if (*map_started)
    {
        int len = ft_strlen(line);
        if (line[len - 1] == '\n')
            line[len - 1] = '\0';
        len = ft_strlen(line);
        if (len > data->width)
            data->width = len;
        data->height++;
    }
    return (0);
}

int validate_elements_after_read(t_map *data)
{
    if ((data->got_textures != 15) || (data->got_colors != 3))
    {
        ft_putendl_fd("Error: Missing required elements in configuration", 2);
        return (1);
    }
    if (data->height == 0 || data->width == 0)
    {
        ft_putendl_fd("Error: No map found in file", 2);
        return (1);
    }
    return (0);
}

int read_file_elements(t_map *data)
{
    int fd;
    char *line;
    int map_started = 0;

    fd = open(data->text, O_RDONLY);
    if (fd == -1)
        return (1);
    data->width = 0;
    data->height = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        if (process_line_for_elements(data, line, &map_started) == 1)
        {
            free(line);
            close(fd);
            // Clear GNL static by reading rest
            while (get_next_line(fd) != NULL);
            return (1);
        }
        free(line);
    }
    close(fd);
    return (validate_elements_after_read(data));
}