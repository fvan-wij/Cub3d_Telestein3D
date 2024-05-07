/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   validate_data.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/07 12:10:14 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/05/07 12:10:15 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cbd_error.h>
#include <cbd_parser.h>
#include <cub3d.h>
#include <libft.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
** Copies the validated raw_data
** Needs:
**	t_map *mapdata
** Returns:
**	copied map
*/
static char	**copy_map(t_map *mapdata)
{
	size_t	i;
	char	**cbd_map;

	i = 0;
	cbd_map = ft_calloc(sizeof(char *), (mapdata->height + 1));
	while (i < (size_t)mapdata->height)
	{
		cbd_map[i] = ft_calloc(sizeof(char), mapdata->width + 1);
		ft_strcpy(cbd_map[i], mapdata->raw_data[i]);
		i++;
	}
	return (cbd_map);
}

/*
** Validates the given map
** Checks if:
**	start is valid
**	walls are valid
**	texture size is valid
**
** Needs:
**	t_map *mapdata
** Returns:
**	true/false
*/
bool	validate_map_data(t_map *mapdata, t_valid *is)
{
	if (!start_is_valid(mapdata, is))
		return (cbd_error(ERR_INVALID_START), false);
	mapdata->cbd_map = copy_map(mapdata);
	if (!mapdata->cbd_map)
		return (cbd_error(ERR_ALLOC), ft_del_2d(mapdata->raw_data), false);
	if (mapdata->is_bonus && !wall_is_valid_bonus(mapdata, mapdata->start_pos.y,
			mapdata->start_pos.x))
		return (cbd_error(ERR_INVALID_WALL), ft_del_2d(mapdata->raw_data),
			false);
	else if (!wall_is_valid(mapdata, mapdata->start_pos.y,
			mapdata->start_pos.x))
		return (cbd_error(ERR_INVALID_WALL), ft_del_2d(mapdata->raw_data),
			false);
	return (true);
}
