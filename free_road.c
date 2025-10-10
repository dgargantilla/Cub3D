/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_road.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:47:07 by shirakim          #+#    #+#             */
/*   Updated: 2025/10/06 20:48:03 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3D.h"
#include "../libft/inc/libft.h"


void	free_map(t_map *data)
{
	int	i;

	i = 0;
	while (data->map && data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
}