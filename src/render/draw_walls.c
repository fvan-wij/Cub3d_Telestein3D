/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_walls.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/06 16:33:15 by dritsema      #+#    #+#                 */
/*   Updated: 2024/05/06 16:33:15 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>
#include <libft.h>

static void	calculate_start_and_end(t_wall_strip_data *strip,
	t_render *render, int x)
{
	strip->wl_height = (int)(HEIGHT / render->rays[x].wall_dist);
	if (render->rays[x].side == 0)
		strip->wall_x = render->rays[x].intersection.y
			- floor(render->rays[x].intersection.y);
	else
		strip->wall_x = render->rays[x].intersection.x
			- floor(render->rays[x].intersection.x);
	strip->draw_start = (HEIGHT / 2) - (strip->wl_height / 2);
	strip->draw_end = strip->draw_start + strip->wl_height;
	strip->draw_start += render->y_offset;
	strip->draw_end += render->y_offset;
	if (strip->draw_start < 0)
		strip->y = -strip->draw_start;
	else
		strip->y = 0;
	if (strip->draw_end >= HEIGHT)
		strip->draw_end = HEIGHT;
}

void	draw_wall_strip(t_render render, int x,
	mlx_texture_t *tex, int color_offset)
{
	t_wall_strip_data	strip;
	t_rgba				color;

	ft_bzero(&strip, sizeof(t_wall_strip_data));
	calculate_start_and_end(&strip, &render, x);
	while (strip.y + strip.draw_start < strip.draw_end
		&& strip.y + strip.draw_start < HEIGHT)
	{
		strip.wall_y = (strip.y / (double)strip.wl_height);
		color = get_texture_pixel(tex, strip.wall_x, strip.wall_y);
		color = color_darken(color, color_offset);
		mlx_put_pixel(render.img, x, strip.y + strip.draw_start, color.color);
		strip.y++;
	}
}

static void	draw_walls_west_east(t_render render, int x,
	t_wall *wall, double dist)
{
	if (render.rays[x].dir.x > 0)
		draw_wall_strip(render, x, wall->w_tex[WE], dist);
	if (render.rays[x].dir.x < 0)
		draw_wall_strip(render, x, wall->w_tex[EA], dist);
}

static void	draw_walls_north_south(t_render render, int x,
	t_wall *wall, double dist)
{
	if (render.rays[x].dir.x > 0)
		draw_wall_strip(render, x, wall->w_tex[NO], dist);
	if (render.rays[x].dir.x < 0)
		draw_wall_strip(render, x, wall->w_tex[SO], dist);
}

/*
** Draws the walls
** 	Needs:
** 		The game image
** 		The raycasting data
** 		The headbobbing data
** 		The map peak data
**		The wall texture data
*/
void	draw_walls(t_render render, t_map *map)
{
	uint16_t	x;

	x = 0;
	if (map->is_bonus)
		return (draw_walls_bonus(render, map));
	while (x < WIDTH)
	{
		if (render.rays[x].side == 0)
			draw_walls_west_east(render, x, &map->walls,
				render.rays[x].wall_dist * 30);
		else if (render.rays[x].side == 1)
			draw_walls_north_south(render, x, &map->walls,
				render.rays[x].wall_dist * 30);
		x++;
	}
}
