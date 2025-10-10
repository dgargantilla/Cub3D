#include "../includes/cub3D.h"
#include "../libft/inc/libft.h"


static int load_map_content(t_map *data)
{
    int fd;
    char *line;
    int i = 0;
    int map_started = 0;

    fd = open(data->text, O_RDONLY);
    if (fd == -1)
        return (1);

    while ((line = get_next_line(fd)) != NULL && i < data->height)
    {
        // Remove trailing newline
        int len = ft_strlen(line);
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
            // Copy map line
            data->map[i] = ft_strdup(line);
            if (!data->map[i])
            {
                free(line);
                close(fd);
                return (1);
            }
            i++;
        }

        free(line);
    }

    get_next_line(-1);
    close(fd);
    data->map[i] = NULL; // Null terminate the array

    return (0);
}

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

    // Initialize all pointers to NULL
    data->map = NULL;
    data->textures.north = NULL;
    data->textures.south = NULL;
    data->textures.west = NULL;
    data->textures.east = NULL;

    // Initialize other values
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

    fd = open(data->text, O_RDONLY);
    if (fd == -1)
        return (1);

    // Initialize map dimensions
    data->width = 0;
    data->height = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        result = parse_line_element(data, line);

        if (result == 1)  // Error
        {
            free(line);
            close(fd);
            return (1);
        }
        else if (result == 2)  // Map section started
        {
            map_started = 1;
        }

        if (map_started)
        {
            // Count map dimensions
            int len = ft_strlen(line);
            if (line[len - 1] == '\n')
                line[len - 1] = '\0';
            len = ft_strlen(line);
            if (len > data->width)
                data->width = len;
            data->height++;
        }

        free(line);
    }

    // Verify all required elements were found
    if ((data->got_textures != 15) || (data->got_colors != 3))
    {
        ft_putendl_fd("Error: Missing required elements in configuration", 2);
        close(fd);
        return (1);
    }

    if (data->height == 0 || data->width == 0)
    {
        ft_putendl_fd("Error: No map found in file", 2);
        close(fd);
        return (1);
    }

    close(fd);
    return (0);
}

int load_map(t_map *data)
{
    printf("Initializing map data...\n");
    // Initialize all data
    initialize_map_data(data);

    printf("Reading file elements and getting map dimensions...\n");
    // Read textures, colors and get map dimensions in one pass
    if (read_file_elements(data) != 0)
    {
        printf("Error reading file elements\n");
        return (1);
    }

    printf("Allocating map memory...\n");
    mapa_memory(data);

    printf("Loading map content...\n");
    if (load_map_content(data) != 0)
    {
        printf("Error loading map content\n");
        return (1);
    }

    printf("Validating map...\n");
    // Validate map
    if (validate_map(data) != 0)
    {
        printf("Map validation failed\n");
        return (1);
    }

    printf("Map loaded successfully\n");
    return (0);
}

void	ft_window_size(t_map *data)
{
	int		screen_width;
	int		screen_height;
	int		map_width_pixels;
	int		map_height_pixels;

	map_width_pixels = data->width * SPRITE_SIZE;
	map_height_pixels = data->height * SPRITE_SIZE;
	// mlx_get_screen_size(mlx, &screen_width, &screen_height); // TODO: Find correct MLX42 function
	screen_width = W_WIDTH;
	screen_height = W_HEIGHT;
	if (map_width_pixels > screen_width || map_height_pixels > screen_height)
	{
		ft_putendl_fd("Error: Map is longer than window.", 2);
		exit_game(data, 2);
	}
}

void	mapa_memory(t_map *data)
{
	int i;

	data->map = malloc(sizeof(char *) * (data->height + 1));
	if (!data->map)
	{
		ft_putendl_fd("Error allocating memory for map", 2);
		exit_game(data, 2);
	}
	i = 0;
	while (i <= data->height)
	{
		data->map[i] = NULL;
		i++;
	}
}

void	exit_game(t_map *data, int exit_code)
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
        if (data->textures.north)
            free(data->textures.north);
        if (data->textures.south)
            free(data->textures.south);
        if (data->textures.west)
            free(data->textures.west);
        if (data->textures.east)
            free(data->textures.east);
    }
    exit(exit_code);
}
