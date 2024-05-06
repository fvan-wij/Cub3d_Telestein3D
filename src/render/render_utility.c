/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_utility.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/06 16:33:32 by dritsema      #+#    #+#                 */
/*   Updated: 2024/05/06 16:33:33 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* Takes a normalized x and y and returns the
   relative pixel color within the texture
*/
t_rgba	get_texture_pixel(mlx_texture_t *tex, double x, double y)
{
	t_rgba	color;

	color = get_color_from_tex(tex, x * tex->width, y * tex->height);
	return (color);
}
