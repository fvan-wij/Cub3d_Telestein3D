/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   load_animation.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/07 12:08:18 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/05/07 12:08:19 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_animation	load_animation(mlx_texture_t *texture, uint32_t frame_width,
		uint32_t frame_height)
{
	t_animation	animation;

	if (frame_width != texture->width)
		animation.n_frames = texture->width / frame_width;
	else
		animation.n_frames = 1;
	if (frame_height != texture->height)
		animation.n_animations = texture->height / frame_height;
	else
		animation.n_animations = 1;
	animation.enabled = true;
	animation.current_frame = 0;
	animation.current_animation = 0;
	animation.timer = 0;
	animation.duration = 0.1;
	animation.loop = true;
	return (animation);
}
