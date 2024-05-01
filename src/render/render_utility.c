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
