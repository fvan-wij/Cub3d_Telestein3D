/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   particle_movement.c                               :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/07 12:08:49 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/05/07 12:08:50 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <MLX42.h>
#include <cub3d.h>
#include <cbd_error.h>
#include <cbd_audio.h>
#include <stdlib.h>

void	move_particles(t_particle *particles, float x, float y)
{
	size_t	i;

	i = 0;
	while (i < N_PARTICLES)
	{
		particles[i].p.x += x;
		particles[i].p.y += y;
		i++;
	}
}

void	rotate_particles(t_particle *particles, float dir)
{
	size_t	i;

	i = 0;
	dir *= 4;
	while (i < N_PARTICLES)
	{
		particles[i].p.x += dir;
		i++;
	}
}

void	resolve_particles(t_particle *particles, int8_t dir)
{
	size_t	i;
	t_vec2d	rand_pos;

	i = 0;
	while (i < N_PARTICLES)
	{
		if (particles[i].p.x < (WIDTH >> 1))
			particles[i].dir.x = -1.0;
		else
			particles[i].dir.x = 1.0;
		particles[i].size.x -= 0.05;
		particles[i].size.y -= 0.05;
		particles[i].p.y += dir;
		particles[i].p.x += particles[i].dir.x * 5;
		if (particles[i].size.x < 0 || particles[i].size.y < 0)
		{
			rand_pos.x = (float) rand() / (float)RAND_MAX * WIDTH;
			rand_pos.y = (float) rand() / (float)RAND_MAX * HEIGHT;
			particles[i].size = particles[i].reset;
			particles[i].p = vec_assign(rand_pos.x, rand_pos.y);
		}
		i++;
	}
}
