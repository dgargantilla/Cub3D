#include "../includes/cub3D.h"
#include "../libft/inc/libft.h"
#include <unistd.h>
#include <fcntl.h>

static void free_textures(t_map *data)
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

static int initialize_map_data(t_map *data)
{
    // First free any existing data
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

static int read_file_elements(t_map *data)
{
    int fd;
    char *line;
    int result;
    int map_started = 0;
    int len;

    fd = open(data->text, O_RDONLY);
    if (fd == -1)
        return (1);

    data->width = 0;
    data->height = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        len = ft_strlen(line);
        if (line[len - 1] == '\n')
            line[len - 1] = '\0';

        // If config not started yet, parse config lines
        if (!data->config_parsed)
        {
            result = parse_line_element(data, line);
            
            if (result == 1)  // Error
            {
                close(fd);
                free(line);
                return (1);
            }
            else if (result == 2)  // Map section started
            {
                map_started = 1;
                data->config_parsed = 1;
                // Don't free line yet, we need to process it as first map line
            }
            else
            {
                free(line);
                continue;
            }
        }

        // Process map section
        if (map_started)
        {
            // Validate no config after map
            if (ft_strncmp(line, "NO ", 3) == 0 ||
                ft_strncmp(line, "SO ", 3) == 0 ||
                ft_strncmp(line, "WE ", 3) == 0 ||
                ft_strncmp(line, "EA ", 3) == 0 ||
                ft_strncmp(line, "F ", 2) == 0 ||
                ft_strncmp(line, "C ", 2) == 0)
            {
                ft_putendl_fd("Error\nConfig found after map start", 2);
                free(line);
                close(fd);
                return (1);
            }

            // Count map dimensions
            len = ft_strlen(line);
            if (len > 0)
            {
                if (len > data->width)
                    data->width = len;
                data->height++;
            }
        }

        free(line);
    }

    close(fd);

    // Verify colors are present
    if ((data->got_colors != 2))
    {
        ft_putendl_fd("Error\nMissing required colors (F and C)", 2);
        return (1);
    }

    if (data->height == 0 || data->width == 0)
    {
        ft_putendl_fd("Error\nNo map found in file", 2);
        return (1);
    }

    return (0);
}

static int load_map_content(t_map *data)
{
    int fd;
    char *line;
    int i = 0;
    int map_started = 0;
    int len;

    fd = open(data->text, O_RDONLY);
    if (fd == -1)
        return (1);

    while ((line = get_next_line(fd)) != NULL && i < data->height)
    {
        // Remove trailing newline
        len = ft_strlen(line);
        if (line[len - 1] == '\n')
            line[len - 1] = '\0';

        // Skip configuration lines
        if (!map_started)
        {
            if (ft_strncmp(line, "NO ", 3) == 0 ||
                ft_strncmp(line, "SO ", 3) == 0 ||
                ft_strncmp(line, "WE ", 3) == 0 ||
                ft_strncmp(line, "EA ", 3) == 0 ||
                ft_strncmp(line, "F ", 2) == 0 ||
                ft_strncmp(line, "C ", 2) == 0 ||
                ft_strlen(line) == 0)
            {
                free(line);
                continue;
            }
            map_started = 1;
        }

        if (map_started)
        {
            // Copy map line (pad to width if needed)
            int line_len = ft_strlen(line);
            data->map[i] = malloc(sizeof(char) * (data->width + 1));
            if (!data->map[i])
            {
                free(line);
                close(fd);
                return (1);
            }
            ft_strlcpy(data->map[i], line, data->width + 1);
            // Pad with spaces if shorter
            for (int j = line_len; j < data->width; j++)
                data->map[i][j] = ' ';
            data->map[i][data->width] = '\0';
            i++;
        }

        free(line);
    }

    close(fd);
    data->map[i] = NULL; // Null terminate the array

    return (0);
}

void mapa_memory(t_map *data)
{
	int i;

	data->map = malloc(sizeof(char *) * (data->height + 1));
	if (!data->map)
	{
		ft_putendl_fd("Error\nMemory allocation failed for map", 2);
		exit_game(data, 2);
	}
	i = 0;
	while (i <= data->height)
	{
		data->map[i] = NULL;
		i++;
	}
}

void exit_game(t_map *data, int exit_code)
{
    int i;

    if (data)
    {
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

        // Free textures
        free_textures(data);
    }
    exit(exit_code);
}

int load_map(t_map *data)
{
    // Initialize all data
    initialize_map_data(data);

    // Single pass: read config, detect map start, and count map dimensions
    if (read_file_elements(data) != 0)
        return (1);

    // Allocate map memory
    mapa_memory(data);

    // Load map content
    if (load_map_content(data) != 0)
        return (1);

    // Validate map (returns 1 on success, 0 on failure)
    if (!validate_map(data))
        return (1);

    return (0);
}