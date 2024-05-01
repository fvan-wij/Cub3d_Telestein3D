#include <cub3d.h>
#include <math.h>
#include <stdlib.h>

void	draw_scanlines_bg(mlx_image_t *img)
{
	t_rgba		c;
	uint32_t	y;
	uint32_t	x;
	uint8_t		v1;

	y = 0;
	while (y < img->height)
	{
		if (y % 5 == 0)
		{
			x = 0;
			while (x < img->width)
			{
				v1 = rand();
				c.r = v1;
				c.g = v1;
				c.b = v1;
				c.a = 80;
				if (x < img->width && y < img->height)
					mlx_put_pixel(img, x, y, c.color);
				x++;
			}
		}
		y++;
	}
}

void	screenshake(t_render *render)
{
	if (render->fx.crt)
	{
		render->headbob += 10;
		draw_scanlines_bg(render->img);
	}
}
