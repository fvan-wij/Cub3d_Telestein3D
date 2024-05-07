/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   get_data_bonus.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/07 12:09:59 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/05/07 12:09:59 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cbd_render.h"
#include <cbd_error.h>
#include <cbd_parser.h>
#include <cub3d.h>
#include <stdio.h>
#include <stdlib.h>

/*
** Identifies the element of the given line
**	returns enum CONT_...
*/
static uint8_t	identify_element(char *line)
{
	if (is_mapcontent(line))
		return (CONT_MAP);
	else if (line[0] == 'W' && (line[1] == '=' || line[1] == '-'
			|| line[1] == '_'))
		return (CONT_CWALL);
	else if (line[0] == 'W')
		return (CONT_WALL);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (CONT_COLF);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (CONT_COLC);
	else if (ft_strncmp(line, "e ", 2) == 0)
		return (CONT_ENEMY);
	else if (ft_strncmp(line, "o ", 2) == 0)
		return (CONT_OBJECT);
	else if (ft_strncmp(line, "i ", 2) == 0)
		return (CONT_ITEM);
	else
		return (CONT_UNKNOWN);
}

static t_map	*initialize_jump_table(t_map *mapdata)
{
	size_t	i;

	i = 0;
	while (i < 255)
	{
		if (mapdata->walls.w_path[(unsigned char)i])
		{
			mapdata->walls.w_tex[(unsigned char)i]
				= mlx_load_png(mapdata->walls.w_path[(unsigned char)i]);
			if (!mapdata->walls.w_tex[(unsigned char)i])
				return (NULL);
		}
		i++;
	}
	return (mapdata);
}

static void	extract_data(t_map *mapdata, uint8_t type, char *line)
{
	if (type == CONT_WALL)
		mapdata->walls.w_path[(unsigned char)line[1]] = ft_strtrim(&line[3],
				"\n");
	else if (type == CONT_CWALL)
		mapdata->walls.w_path[(unsigned char)line[1]] = ft_strtrim(&line[3],
				"\n");
	else if (type == CONT_MAP)
		mapdata->raw_data = ft_add_2d(mapdata->raw_data, line);
	else if (type == CONT_COLC)
		mapdata->ceiling = get_col(&line[2]);
	else if (type == CONT_COLF)
		mapdata->floor = get_col(&line[2]);
	else if (type == CONT_ENEMY || type == CONT_ITEM || type == CONT_OBJECT)
		mapdata->entities = append_entity(mapdata->entities, line, type);
}

/*
** Reads the map, stores the given line in a node,
**	returns linked list of all the elements
** Steps:
**	Initialize lst
**	Read line, identify element, store in node
*/
t_map	*get_map_data_bonus(int fd, char *line)
{
	uint8_t	type;
	t_map	*mapdata;

	mapdata = alloc_map_bonus();
	if (!mapdata)
		return (NULL);
	free(line);
	line = get_next_line(fd);
	while (line)
	{
		type = identify_element(line);
		extract_data(mapdata, type, line);
		free(line);
		line = get_next_line(fd);
	}
	mapdata = initialize_jump_table(mapdata);
	return (mapdata);
}
