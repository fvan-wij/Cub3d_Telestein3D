/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_entity.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/06 16:24:17 by dritsema      #+#    #+#                 */
/*   Updated: 2024/05/06 16:25:25 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_rgba	get_animated_pixel(t_animation ani, mlx_texture_t *tex, int tx, int ty)
{
	t_rgba	color;
	int		frame_x;
	int		frame_y;
	int		frame_width;

	frame_width = tex->width / ani.n_frames;
	frame_x = tx + frame_width * ani.current_frame;
	frame_y = ty + frame_width * ani.current_animation;
	color = get_color_from_tex(tex, frame_x, frame_y);
	return (color);
}

static t_rgba	get_entity_pixel(t_render_entity re, int tx, int ty)
{
	t_rgba	color;

	color = get_animated_pixel(re.entity->animation,
			re.entity->texture, tx, ty);
	color = color_darken(color, re.transform_y * 30);
	return (color);
}

void	set_entity_pixel(t_render_entity re, int x, int y, t_rgba color)
{
	if (x == WIDTH / 2 && y == HEIGHT / 2)
	{
		re.player->target_distance = re.transform_y;
		re.player->target_entity = re.entity;
	}
	mlx_put_pixel(re.render->sprite_img, x, y, color.color);
	re.render->zbuffer[x + ((y) * WIDTH)] = re.transform_y;
}

void	draw_entity_strip(int strip, t_render_entity re)
{
	int		tex_x;
	int		y;
	int		tex_y;
	int		d;
	t_rgba	color;

	tex_x = (int)(256 * (strip - (-re.sprite_width / 2 + re.sprite_screen_x))
			* re.tex_width / re.sprite_width) / 256;
	y = re.draw_start_y;
	while (y < re.draw_end_y)
	{
		d = (y - re.render->y_offset)
			* 256 - HEIGHT * 128 + re.sprite_height * 128;
		tex_y = ((d * re.tex_height) / re.sprite_height) / 256;
		if (y >= 0 && y < HEIGHT)
		{
			color = get_entity_pixel(re, tex_x, tex_y);
			if (color.a != 0
				&& re.transform_y < re.render->zbuffer[strip + ((y) * WIDTH)])
			{
				set_entity_pixel(re, strip, y, color);
			}
		}
		y++;
	}
}
