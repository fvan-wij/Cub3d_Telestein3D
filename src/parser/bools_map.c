#include <cbd_parser.h>
#include <stdbool.h>

/*
** Checks if given character is a map character
** Needs:
**	char c
** Returns:
**	true/false
*/
static bool	is_mapchar(char c)
{
	size_t		i;
	const char	map_content[10] = {"0NWES\t \0"};

	i = 0;
	while (map_content[i])
	{
		if (c == map_content[i] || is_wall(c))
			return (true);
		i++;
	}
	return (false);
}

/*
** Checks if given character is a wall
** Needs:
**	char c
** Returns:
**	true/false
*/
bool	is_wall(char c)
{
	if (c == '1')
		return (true);
	return (false);
}

/*
** Checks if given character is a wall
** Needs:
**	char c
** Returns:
**	true/false
*/
bool	is_wall_bonus(char c)
{
	size_t		i;
	const char	map_content[13] = "123456789=-_";

	i = 0;
	while (map_content[i])
	{
		if (c == map_content[i])
			return (true);
		i++;
	}
	return (false);
}

/*
** Checks if given line is mapcontent
** Needs:
**	line
** Returns:
**	true/false
*/
bool	is_content(char *line)
{
	size_t	i;

	i = 0;
	if (!line)
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
