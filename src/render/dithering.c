#include <cbd_render.h>
#include <math.h>

static uint32_t	index_at(uint32_t x, uint32_t y, uint32_t width)
{
	const uint32_t	index = (x + y * width) * 4;

	return (index);
}

static void	diffuse_pixel(uint8_t *pixels, uint32_t x, uint32_t y, uint32_t q)
{
	pixels[index_at(x + 1, y, WIDTH)] += q * 7 / 16;
	pixels[index_at(x - 1, y + 1, WIDTH)] += q * 3 / 16;
	pixels[index_at(x, y + 1, WIDTH)] += q * 5 / 16;
}

static int32_t	quantized_pixel(uint8_t *pixels, uint32_t x, uint32_t y,
		uint8_t col)
{
	const uint32_t	index = (x + y * WIDTH) * 4;
	int32_t			new;

	if (col == 0)
		new = round(((2 * pixels[index] >> 8)) * ((255 >> 1)));
	else if (col == 1)
		new = round(((2 * pixels[index + 1] >> 8)) * ((255 >> 1)));
	else
		new = round(((2 * pixels[index + 2] >> 8)) * ((255 >> 1)));
	return (new);
}

static void	dither_pixels(uint8_t *pixels, uint32_t index,
		uint32_t x, uint32_t y)
{
	const int32_t	q_r = pixels[index] - quantized_pixel(pixels, x, y, 0);
	const int32_t	q_g = pixels[index + 1] - quantized_pixel(pixels, x, y, 1);
	const int32_t	q_b = pixels[index + 2] - quantized_pixel(pixels, x, y, 2);

	pixels[index] = quantized_pixel(pixels, x, y, 0);
	pixels[index + 1] = quantized_pixel(pixels, x, y, 1);
	pixels[index + 2] = quantized_pixel(pixels, x, y, 2);
	diffuse_pixel(pixels, x, y, q_r);
	diffuse_pixel(pixels + 1, x, y, q_g);
	diffuse_pixel(pixels + 2, x, y, q_b);
}

mlx_image_t	*dither_image(mlx_image_t *img)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	index;

	y = 1;
	while (y < img->height - 1)
	{
		x = 1;
		while (x < img->width - 1)
		{
			index = (x + y * WIDTH) * 4;
			dither_pixels(img->pixels, index, x, y);
			x++;
		}
		y++;
	}
	return (img);
}
