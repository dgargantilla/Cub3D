#include "includes/cub3D.h"
#include <stdio.h>

void test_map(const char *filename)
{
    t_map map;
    int i;

    printf("\n=== Testing Map: %s ===\n", filename);
    
    // Initialize map structure
    ft_memset(&map, 0, sizeof(t_map));

    // Allocate and copy filename
    map.text = malloc(sizeof(char) * (ft_strlen(filename) + 1));
    if (!map.text)
    {
        printf("❌ Error: Memory allocation failed\n");
        return;
    }
    ft_strlcpy(map.text, filename, ft_strlen(filename) + 1);

    // Load the map
    if (load_map(&map) != 0)
    {
        printf("❌ Error: Failed to load map\n");
        free(map.text);
        return;
    }

    // Validate the map
    printf("\n🔍 Validating map...\n");
    if (validate_map(&map) != 0)
    {
        printf("❌ Map validation failed\n");
        exit_game(&map, 1);
        return;
    }
    printf("✅ Map is valid!\n");

    // Print map information
    printf("\n📊 Map Information:\n");
    printf("Width: %d\n", map.width);
    printf("Height: %d\n", map.height);
    printf("Player position: (%d, %d)\n", map.player_x, map.player_y);

    // Print map content
    printf("\n🗺️  Map Content:\n");
    if (map.map)
    {
        for (i = 0; map.map[i]; i++)
        {
            printf("%s\n", map.map[i]);
        }
    }
    else
    {
        printf("❌ Error: Map content is NULL\n");
    }

    // Cleanup
    exit_game(&map, 0);
    printf("\n✅ Test completed\n");
    printf("----------------------------------------\n");
}

int main(void)
{
    printf("🧪 Starting Map Validation Tests\n");
    printf("----------------------------------------\n");

    // Test valid map
    test_map("map/mapa.cub");

    // Test map with open borders
    test_map("map/mapa_error1.cub");

    // Test map without player
    test_map("map/mapa_error2.cub");

    // Test map with multiple players
    test_map("map/mapa_error3.cub");

    // Test map with invalid characters
    test_map("map/mapa_error4.cub");

    printf("\n🏁 All tests completed!\n");
    return (0);
}