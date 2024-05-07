/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   particles.c                                       :+:    :+:             */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/06 16:33:29 by dritsema      #+#    #+#                 */
/*   Updated: 2024/05/07 12:04:33 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdlib.h>

static void	fade_blood(mlx_image_t *img)
{
	uint32_t	x;
	uint32_t	y;
	int			index;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			index = (x + y * img->width) * 4;
			if (img->pixels[index + 3] >= 10)
				img->pixels[index + 3] -= 0.5;
			x++;
		}
		y++;
	}
}

void	draw_blood_splat(mlx_image_t *img, t_particle *splat, t_fx *fx)
{
	t_vec2i		it;
	t_particle	*particle;

	it = vec2i(0, 0);
	if (!fx->splat)
		return (fade_blood(img), init_blood_splat(splat));
	while (it.x < MAX_BLOOD_PARTICLES && fx->splat)
	{
		particle = &splat[it.x];
		particle->size = vec_sub(particle->size, vec_assign(0.75, 0.75));
		particle->p = vec_add(particle->p,
				vec_assign(particle->dir.x * 5, particle->dir.y * 20));
		if (particle->size.x <= 0 || particle->size.y <= 0)
			it.y++;
		draw_square_centered(img, color_rgba(125, 0, 0, 255),
			vec_to_int(particle->p), vec_to_int(particle->size));
		it.x++;
	}
	if (it.y == MAX_BLOOD_PARTICLES)
		fx->splat = false;
}

static void	reset_particles(int j, t_fx *fx, t_particle *blood_particle)
{
	if (j == MAX_BLOOD_PARTICLES)
	{
		fx->blood = false;
		init_blood_particles(blood_particle);
	}
}

void	draw_blood_particles(mlx_image_t *img, t_particle *blood_particle,
	t_fx *fx)
{
	int			i;
	int			j;
	t_particle	*particle;

	i = 0;
	j = 0;
	while (i < MAX_BLOOD_PARTICLES)
	{
		particle = &blood_particle[i];
		if (fx->blood)
		{
			particle->size.x -= 10.0;
			particle->size.y -= 10.0;
			particle->p.x = particle->p.x + (particle->dir.x) * 10;
			particle->p.y = particle->p.y + (particle->dir.y) * 10;
			if (particle->size.x <= 0 || particle->size.y <= 0)
				j++;
			draw_square_centered(img, color_rgba(rand(), 0, 0, 255),
				vec_to_int(particle->p), vec_to_int(particle->size));
		}
		else
			break ;
		i++;
	}
	reset_particles(j, fx, blood_particle);
}
