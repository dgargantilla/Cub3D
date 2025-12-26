/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapa_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:26:47 by shirakim          #+#    #+#             */
/*   Updated: 2025/12/24 13:35:58 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


int load_map_helper(t_map *data)
{
	 if (load_map_content(data) != 0)
    {
        printf("Error loading map content\n");
        free_map_array(data);
        free_textures(data);
        return (1);
    }
    if (validate_map(data) != 0)
    {
        printf("Map validation failed\n");
        free_map_array(data);
        free_textures(data);
        return (1);
    }
	return (0);
}
int	load_map(t_map *data)
{
    initialize_map_data(data);
    if (read_file_elements(data) != 0)
    {
        printf("Error reading file elements\n");
        free_textures(data);
        return (1);
    }
    mapa_memory(data);
    if (!data->map)
    {
        printf("Error allocating map memory\n");
        free_textures(data);
        return (1);
    }
	if (load_map_helper(data) != 0)
		return (1);
    return (0);
}
