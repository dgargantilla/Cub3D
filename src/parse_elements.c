#include "../includes/cub3D.h"

static int is_valid_rgb(int r, int g, int b)
{
    return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}

static int parse_rgb(char *str, t_color *color)
{
    char **parts;
    int count;

    parts = ft_split(str, ',');
    if (!parts)
        return (1);
    
    // Count parts
    count = 0;
    while (parts[count])
        count++;
    
    if (count != 3)
    {
        ft_putendl_fd("Error: Invalid RGB format (should be R,G,B)", 2);
        return (1);
    }

    // Convert and validate each number
    color->r = ft_atoi(parts[0]);
    color->g = ft_atoi(parts[1]);
    color->b = ft_atoi(parts[2]);

    // Free parts
    for (int i = 0; parts[i]; i++)
        free(parts[i]);
    free(parts);

    if (!is_valid_rgb(color->r, color->g, color->b))
    {
        ft_putendl_fd("Error: RGB values must be between 0 and 255", 2);
        return (1);
    }

    return (0);
}

static int handle_texture(char *line, char **texture_path)
{
    while (*line && *line == ' ')
        line++;
    
    if (!*line)
    {
        ft_putendl_fd("Error: Missing texture path", 2);
        return (1);
    }

    // Free previous path if it exists
    if (*texture_path)
        free(*texture_path);
    
    /* Trim trailing spaces, tabs and CR */
    char *trimmed = ft_strtrim(line, " \t\r\n");
    if (!trimmed)
        return (1);
    *texture_path = ft_strdup(trimmed);
    free(trimmed);
    if (!*texture_path)
    {
        ft_putendl_fd("Error: Memory allocation failed", 2);
        return (1);
    }

    // Check if file exists and is readable
    int fd = open(*texture_path, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        printf("DEBUG: tried to open texture: '%s' (len=%zu)\n", *texture_path, ft_strlen(*texture_path));
    }
    if (fd == -1)
    {
        ft_putendl_fd("Error: Cannot open texture file", 2);
        return (1);
    }
    close(fd);

    return (0);
}

int parse_line_element(t_map *data, char *line)
{
    // Remove leading spaces
    while (*line && (*line == ' ' || *line == '\t'))
        line++;

    // Skip empty lines or lines with just spaces
    if (!*line || *line == '\n' || *line == '\r')
        return (0);

    // Remove trailing newline if present
    char *newline = ft_strchr(line, '\n');
    if (newline)
        *newline = '\0';

    if (ft_strncmp(line, "NO ", 3) == 0)
    {
        if (handle_texture(line + 3, &data->textures.north) == 0)
            data->got_textures |= 1;
    }
    else if (ft_strncmp(line, "SO ", 3) == 0)
    {
        if (handle_texture(line + 3, &data->textures.south) == 0)
            data->got_textures |= 2;
    }
    else if (ft_strncmp(line, "WE ", 3) == 0)
    {
        if (handle_texture(line + 3, &data->textures.west) == 0)
            data->got_textures |= 4;
    }
    else if (ft_strncmp(line, "EA ", 3) == 0)
    {
        if (handle_texture(line + 3, &data->textures.east) == 0)
            data->got_textures |= 8;
    }
    else if (ft_strncmp(line, "F ", 2) == 0)
    {
        if (parse_rgb(line + 2, &data->floor) == 0)
            data->got_colors |= 1;
    }
    else if (ft_strncmp(line, "C ", 2) == 0)
    {
        if (parse_rgb(line + 2, &data->ceiling) == 0)
            data->got_colors |= 2;
    }
    else if (ft_strchr("01NSEW", *line))
    {
        data->got_map = 1;
        return (2); // Signal start of map section
    }
    else
    {
        ft_putendl_fd("Error: Invalid identifier in configuration", 2);
        return (1);
    }

    return (0);
}