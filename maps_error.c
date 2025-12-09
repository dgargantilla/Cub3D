/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:20:29 by shirakim          #+#    #+#             */
/*   Updated: 2025/12/09 23:56:07 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
#include "../libft/inc/libft.h"


void	exit_error(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	exit(EXIT_FAILURE);
}

void	ft_check_borders(t_map *data)
{
	int	idx;

	idx = 0;
	while (idx < data->width)
	{
		if (data->map[0][idx] != '1' || data->map[data->height - 1][idx] != '1')
			exit_error("Error: El borde superior o inferior no está cerrado.");
		idx++;
	}
	idx = 0;
	while (idx < data->height)
	{
		if (data->map[idx][0] != '1' || data->map[idx][data->width - 1] != '1')
			exit_error("Error: El borde izquierdo o derecho no está cerrado.");
		idx++;
	}
}

void	comprobacion_open_ber(t_map *data)
{
	size_t	longitud;

	longitud = ft_strlen(data->text);
	if (longitud < 4 || ft_strncmp(&data->text[longitud - 4], ".ber", 4) != 0)
	{
		ft_putstr_fd("Error: el archivo debe tener la extensión .ber\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_printf("El archivo %s es válido\n", data->text);
}