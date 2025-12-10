#include "../includes/cub3D.h"
# include "../../libft/libft.h"

int is_config_line(char *line)
{
    return (ft_strncmp(line, "NO ", 3) == 0 ||
            ft_strncmp(line, "SO ", 3) == 0 ||
            ft_strncmp(line, "WE ", 3) == 0 ||
            ft_strncmp(line, "EA ", 3) == 0 ||
            ft_strncmp(line, "F ", 2) == 0 ||
            ft_strncmp(line, "C ", 2) == 0 ||
            ft_strlen(line) == 0);
}

char *skip_config_lines(int fd)
{
    char *line;
    int map_started = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        int len = ft_strlen(line);
        if (line[len - 1] == '\n')
            line[len - 1] = '\0';
        if (!map_started)
        {
            if (is_config_line(line))
            {
                free(line);
                continue;
            }
            map_started = 1;
        }
        if (map_started)
            return (line);
        free(line);
    }
    return (NULL);
}

int load_map_lines(t_map *data, int fd, char *first_line)
{
    char *line;
    int i = 0;

    line = first_line;
    while (line != NULL && i < data->height)
    {
        data->map[i] = ft_strdup(line);
        if (!data->map[i])
        {
            free(line);
            close(fd);
            return (1);
        }
        i++;
        free(line);
        line = get_next_line(fd);
        if (line && line[ft_strlen(line) - 1] == '\n')
            line[ft_strlen(line) - 1] = '\0';
    }

    get_next_line(-1);
    close(fd);
    data->map[i] = NULL;
    return (0);
}

int load_map_content(t_map *data)
{
    int fd;
    char *first_line;

    fd = open(data->text, O_RDONLY);
    if (fd == -1)
        return (1);

    first_line = skip_config_lines(fd);
    if (!first_line)
    {
        close(fd);
        return (1);
    }

    return (load_map_lines(data, fd, first_line));
}