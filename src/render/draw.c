#include <cub3d.h>
#include <stdlib.h>

void	draw_background(mlx_image_t *img, int32_t color, int peek)
{
	const t_vec2i	init = {0, 0};
	const t_vec2i	screen = {WIDTH, HEIGHT / 2 + peek};
	const t_vec2i	init2 = {0, HEIGHT / 2 + peek};
	const t_vec2i	screen2 = {WIDTH, HEIGHT};

	draw_square(img, color, init, screen);
	draw_square(img, color, init2, screen2);
}

void	draw_dust_particles(mlx_image_t *game, t_particle *particles)
{
	int		i;
	float	y;

	i = 0;
	while (i < N_PARTICLES)
	{
		y = ((float) rand() / (float)RAND_MAX / 4);
		particles[i].dir.y = y - 0.05;
		particles[i].p.x = particles[i].p.x + particles[i].dir.x * 2;
		particles[i].p.y = particles[i].p.y + particles[i].dir.y * 2;
		particles[i].dir.x = 0.1 * -y;
		if (particles[i].p.y > HEIGHT)
			particles[i].p.y = 0;
		if (particles[i].p.y < 0)
			particles[i].p.y = HEIGHT;
		if (particles[i].p.x > WIDTH)
			particles[i].p.x = y;
		if (particles[i].p.x < 0)
			particles[i].p.x = WIDTH;
		draw_square(game, color(75, 75, 75), vec_to_int(particles[i].p),
			vec_to_int(particles[i].size));
		i++;
	}
}
