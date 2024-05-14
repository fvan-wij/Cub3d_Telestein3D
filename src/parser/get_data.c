/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_data.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 12:09:55 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/05/14 15:56:34 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cbd_error.h>
#include <cbd_parser.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <cub3d.h>

static bool	retrieve_element(char *key, char *value, t_map *mapdata)
{
	if (ft_strncmp(key, "NO", 2) == 0 && !mapdata->walls.w_path[NO])
		mapdata->walls.w_path[NO] = get_texpath(value);
	else if (ft_strncmp(key, "SO", 2) == 0 && !mapdata->walls.w_path[SO])
		mapdata->walls.w_path[SO] = get_texpath(value);
	else if (ft_strncmp(key, "WE", 2) == 0 && !mapdata->walls.w_path[WE])
		mapdata->walls.w_path[WE] = get_texpath(value);
	else if (ft_strncmp(key, "EA", 2) == 0 && !mapdata->walls.w_path[EA])
		mapdata->walls.w_path[EA] = get_texpath(value);
	else if (ft_strncmp(key, "F ", 2) == 0)
		mapdata->floor = get_col(value);
	else if (ft_strncmp(key, "C ", 2) == 0)
		mapdata->ceiling = get_col(value);
	return (true);
}

/*
** Checks the given line and stores texture path or color in mapdata
**
** Needs:
**	a line of the .cub file
*/
static void	retrieve_elements(char *line, t_map *mapdata)
{
	char	**temp;

	temp = ft_split(line, ' ');
	if (retrieve_element(temp[0], temp[1], mapdata) == false)
		return (ft_del_2d(temp));
	ft_del_2d(temp);
}

t_map	*get_map_data_mandatory(int fd, t_valid *is, char *line)
{
	t_map	*mapdata;

	mapdata = alloc_map();
	if (!mapdata)
		return (NULL);
	while (line)
	{
		if ((is_last_element(is) && !is_content(line)) || line[0] == '\n')
			return (cbd_error(ERR_INVALID_MAP), free(line),
				cleanup_map(mapdata), NULL);
		else if (is_tex(line, is) || is_col(line, is))
			retrieve_elements(line, mapdata);
		else if (is_content(line) && is_last_element(is))
			mapdata->raw_data = ft_add_2d(mapdata->raw_data, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!get_mlx_tex(mapdata, TEX_SIZE))
		return (cleanup_map(mapdata), NULL);
	if (!mapdata->raw_data)
		return (cbd_error(ERR_INVALID_MAP), cleanup_map(mapdata), NULL);
	return (mapdata);
}

/*
** Gets all the necessary data from the .cub file
** such as:
** 	Path to NO, EA, SO, WE textures
** 	Map content
** 	Ceiling and floor colors
**
** Needs:
**	Open filedescriptor to the .cub file
**	Pointer to mapdata struct
**	Pointer to validation struct
**
** Returns:
**		t_map *mapdata
*/
t_map	*get_map_data(int fd, t_valid *is)
{
	char	*line;
	t_map	*mapdata;

	line = get_next_line(fd);
	if (ft_strncmp(line, "CBD_BONUS", 9) == 0)
		mapdata = get_map_data_bonus(fd, line);
	else
		mapdata = get_map_data_mandatory(fd, is, line);
	return (mapdata);
}
