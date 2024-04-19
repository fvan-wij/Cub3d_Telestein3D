#include <cbd_error.h>
#include <cbd_parser.h>
#include <fcntl.h>
#include <unistd.h>

/*
** Checks if given line is a NO, SO, EA, WE texture
** Needs:
**	line
**	t_valid is (struct containing all the read mapdata)
** Returns:
**	true/false
*/
bool	is_tex(char *line, t_valid *is)
{
	size_t	len;

	len = 0;
	if (!line)
		return (false);
	len = ft_strlen(line);
	if (len > 5 && ft_strncmp(&line[len - 5], ".png", 4) == 0)
	{
		if (ft_strncmp(line, "NO ", 3) == 0)
			return (is->tex[NO] = true);
		if (ft_strncmp(line, "SO ", 3) == 0)
			return (is->tex[SO] = true);
		if (ft_strncmp(line, "WE ", 3) == 0)
			return (is->tex[WE] = true);
		if (ft_strncmp(line, "EA ", 3) == 0)
			return (is->tex[EA] = true);
	}
	return (false);
}

/*
** Checks if given line is a floor or ceiling color
** Needs:
**	line
**	t_valid is (struct containing all the read mapdata)
** Returns:
**	true/false
*/
bool	is_col(char *line, t_valid *is)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		return (is->col_fl = true);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (is->col_cl = true);
	return (false);
}

/*
** Checks if colors and textures have already been read
** Needs:
**	t_valid is (struct containing all the read mapdata)
** Returns:
**	true/false
*/
bool	is_last_element(t_valid *is)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < TEX_SIZE)
	{
		if (is->tex[i] == true)
			count++;
		i++;
	}
	if (count == 4 && is->col_cl && is->col_fl)
		return (true);
	return (false);
}

/*
** Checks if given map is a bonus file
** Needs:
**	t_valid is (struct containing all the read mapdata)
** Returns:
**	true/false
*/
bool	is_bonus(int fd)
{
	int32_t	bytes;
	char	buffer[10];

	bytes = read(fd, &buffer, 10);
	if (bytes < 0)
		return (cbd_error(ERR_FILE_INEXISTS), false);
	if (ft_strncmp("CBD_BONUS", buffer, 9) == 0)
	{
		ft_printf("Is bonus!\n");
		return (true);
	}
	else
	{
		ft_printf("Is NOT bonus!\n");
		return (false);
	}
}

/*
** Opens texture and checks if texture exists
**
** Needs:
**	path
**
** Returns:
**	true/false
*/
bool	tex_exists(char *path)
{
	int	fd;
	int	len;

	len = ft_strlen(path);
	path[len - 1] = '\0';
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	return (close(fd), true);
}
