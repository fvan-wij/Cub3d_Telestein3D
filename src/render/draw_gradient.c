#include <cub3d.h>

t_rgba_step	calculate_step(t_rgba top, t_rgba bot, uint32_t cap)
{
	t_rgba_step	step;

	step.r = (float)(bot.r - top.r) / cap;
	step.g = (float)(bot.g - top.g) / cap;
	step.b = (float)(bot.b - top.b) / cap;
	step.a = (float)(bot.a - top.a) / cap;
	return (step);
}

void	draw_gradient_top(mlx_image_t *img, t_rgba top, t_rgba bot, int32_t end)
{
	uint32_t	cap;
	t_rgba		color;
	t_rgba_step	step;
	uint32_t	y;
	uint32_t	x;

	cap = (img->height >> 1) + end;
	step = calculate_step(top, bot, cap);
	y = 0;
	while (y < cap)
	{
		x = 0;
		while (x < img->width)
		{
			color.r = top.r + step.r * y;
			color.g = top.g + step.g * y;
			color.b = top.b + step.b * y;
			color.a = top.a + step.a * y;
			if (x < img->width && y < img->height)
				mlx_put_pixel(img, x, y, color.color);
			x++;
		}
		y++;
	}
}

void	draw_gradient_bot(mlx_image_t *img, t_rgba top, t_rgba bot, int32_t end)
{
	uint32_t	cap;
	t_rgba_step	step;
	t_rgba		color;
	uint32_t	y;
	uint32_t	x;

	cap = (img->height >> 1) + end;
	step = calculate_step(top, bot, cap);
	y = cap;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			color.r = top.r + step.r * (y - cap);
			color.g = top.g + step.g * (y - cap);
			color.b = top.b + step.b * (y - cap);
			color.a = top.a + step.a * (y - cap);
			if (x < img->width && y < img->height)
				mlx_put_pixel(img, x, y, color.color);
			x++;
		}
		y++;
	}
}

void	draw_gradient_bg(mlx_image_t *img, t_rgba c1,
	t_rgba c2, int32_t offset)
{
	draw_gradient_top(img, c1, c2, offset);
	draw_gradient_bot(img, c2, c1, offset);
}
