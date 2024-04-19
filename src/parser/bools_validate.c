#include <cbd_parser.h>
#include <cbd_error.h>
#include <libft.h>
#include <cub3d.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/*
** Recursive funcction that checks if there are open walls (floodfill)
** Needs:
**	t_map *mapdata
**	int i (x location)
**	int j (y location)
** Returns:
**	true/false
*/
bool	wall_is_valid(t_map *mapdata, int i, int j)
{
	bool		err;
	const int 	lenW = ft_strlen(mapdata->raw_data[i]);
	const int 	lenH = ft_arrlen(mapdata->raw_data);

	err = true;
	if ((i < 0 || j < 0 || i >= lenH - 1 || j >= lenW - 1))
		return (false);
	if ((i == 0 || j == 0 || i == (lenH - 1) || j == (lenW - 1)) && !is_wall(mapdata->raw_data[i][j]))
		return (false);
	mapdata->raw_data[i][j] = FILL;
	if (err && (i + 1) <= (lenH - 1) && !is_wall(mapdata->raw_data[i + 1][j]) && mapdata->raw_data[i + 1][j] != FILL)
		err = wall_is_valid(mapdata, i + 1, j);
	if (err && (j + 1) <= (lenW - 1) && !is_wall(mapdata->raw_data[i][j + 1]) && mapdata->raw_data[i][j + 1] != FILL)
		err = wall_is_valid(mapdata, i, j + 1);
	if (err && (i - 1) >= 0 && !is_wall(mapdata->raw_data[i - 1][j]) && mapdata->raw_data[i - 1][j] != FILL)
		err = wall_is_valid(mapdata, i - 1, j);
	if (err && (j - 1) >= 0 && !is_wall(mapdata->raw_data[i][j - 1]) && mapdata->raw_data[i][j - 1] != FILL)
		err = wall_is_valid(mapdata, i, j - 1);
	return (err);
}

/*
** Recursive funcction that checks if there are open walls (floodfill)
** Needs:
**	t_map *mapdata
**	int i (x location)
**	int j (y location)
** Returns:
**	true/false
*/
bool	wall_is_valid_bonus(t_map *mapdata, int i, int j)
{
	const int 	lenW = mapdata->width;
	const int 	lenH = mapdata->height;
	bool		err;

	err = true;
	if ((i < 0 || j < 0 || i >= lenH - 1 || j >= lenW - 1))
		return (false);
	if ((i == 0 || j == 0 || i == (lenH - 1) || j == (lenW - 1))
		&& !is_wall_bonus(mapdata->raw_data[i][j]))
		return (false);
	mapdata->raw_data[i][j] = FILL;
	if (err && (i + 1) <= (lenH - 1)
		&& !is_wall_bonus(mapdata->raw_data[i + 1][j]) && mapdata->raw_data[i + 1][j] != FILL)
		err = wall_is_valid(mapdata, i + 1, j);
	if (err && (j + 1) <= (lenW - 1) && !is_wall_bonus(mapdata->raw_data[i][j + 1]) && mapdata->raw_data[i][j + 1] != FILL)
		err = wall_is_valid(mapdata, i, j + 1);
	if (err && (i - 1) >= 0 && !is_wall_bonus(mapdata->raw_data[i - 1][j]) && mapdata->raw_data[i - 1][j] != FILL)
		err = wall_is_valid(mapdata, i - 1, j);
	if (err && (j - 1) >= 0 && !is_wall_bonus(mapdata->raw_data[i][j - 1]) && mapdata->raw_data[i][j - 1] != FILL)
		err = wall_is_valid(mapdata, i, j - 1);
	return (err);
}

/*
** Checks if there are duplicate start positions
** Needs:
**	t_map *mapdata
**	t_valid (struct containing booleans of validated data)
** Returns:
**	true/false
*/
bool	is_duplicate(t_valid *is, t_map *mapdata)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < DIR_SIZE)
	{
		if (is->start[i] == true)
			count++;
		i++;
	}
	if (count >= 1 && (mapdata->start_pos.x != -1
			|| mapdata->start_pos.y != -1))
		return (true);
	return (false);
}

/*
** Checks if the given character is the starting position.
** Needs:
**	char c (current character to check)
**	t_map *mapdata
**	t_valid (struct containing booleans of validated data)
** Returns:
**	true/false
*/
bool	is_player(char c, t_map *mapdata, t_valid *is)
{
	if (c == 'N')
	{
		mapdata->start_dir = vec_assign(0, -1);
		return (is->start[N] = true);
	}
	else if (c == 'E')
	{
		mapdata->start_dir = vec_assign(1, 0);
		return (is->start[E] = true);
	}
	else if (c == 'S')
	{
		mapdata->start_dir = vec_assign(0, 1);
		return (is->start[S] = true);
	}
	else if (c == 'W')
	{
		mapdata->start_dir = vec_assign(-1, 0);
		return (is->start[W] = true);
	}
	return (false);
}

/*
** Checks if the start location is valid i.e. contains no duplicates
** Needs:
**	t_map *mapdata
**	t_valid *is (struct containing booleans with validated data)
** Returns:
**	true/false
*/
bool	start_is_valid(t_map *mapdata, t_valid *is)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (mapdata->raw_data[i])
	{
		j = 0;
		while (mapdata->raw_data[i][j])
		{
			if (is_player(mapdata->raw_data[i][j], mapdata, is)
				&& !is_duplicate(is, mapdata))
				mapdata->start_pos = vec_assign(j, i);
			else if (is_player(mapdata->raw_data[i][j], mapdata, is)
				&& is_duplicate(is, mapdata))
				return (false);
			if (j > (size_t) mapdata->width)
				mapdata->width = j;
			j++;
		}
		i++;
	}
	mapdata->height = i;
	return (true);
}
