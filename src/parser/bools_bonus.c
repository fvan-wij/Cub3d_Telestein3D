#include "cbd_render.h"
#include <cbd_error.h>
#include <cbd_parser.h>
#include <cub3d.h>
#include <stdio.h>
#include <stdlib.h>

static bool	is_mapchar(char c)
{
	size_t		i;
	const char	map_content[20] = {"0123456789NWES=-_\t "};

	i = 0;
	while (map_content[i])
	{
		if (c == map_content[i] || is_wall(c))
			return (true);
		i++;
	}
	return (false);
}

bool	is_mapcontent(char *line)
{
	size_t	i;

	i = 0;
	if (!line || line[0] == '\n')
		return (false);
	while (line[i])
	{
		if (is_mapchar(line[i]))
			i++;
		else
			break ;
	}
	if (line[i] == '\n')
		return (true);
	return (false);
}
