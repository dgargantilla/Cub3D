/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_borders_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirakim <shirakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:15:00 by shirakim          #+#    #+#             */
/*   Updated: 2025/12/23 14:42:49 by shirakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	find_first_non_space(char *line, int row_len)
{
	int	j;

	j = 0;
	while (j < row_len)
	{
		if (line[j] != ' ')
			return (j);
		j++;
	}
	return (-1);
}

int	find_last_non_space(char *line, int row_len)
{
	int	j;

	j = row_len - 1;
	while (j >= 0)
	{
		if (line[j] != ' ' && line[j] != '\n')
			return (j);
		j--;
	}
	return (-1);
}

int	check_border_chars(char *line, int first, int last)
{
	if (first != -1 && line[first] != '1')
		return (0);
	if (last != -1 && line[last] != '1')
		return (0);
	return (1);
}

int	validate_line_borders(char *line, int row_len)
{
	int	first;
	int	last;

	first = find_first_non_space(line, row_len);
	last = find_last_non_space(line, row_len);
	if (!check_border_chars(line, first, last))
		return (0);
	return (1);
}
