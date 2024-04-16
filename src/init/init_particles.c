/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_particles.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/16 19:13:49 by dritsema      #+#    #+#                 */
/*   Updated: 2024/04/16 21:01:31 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>
#include <stdlib.h>

void	init_blood_splat(t_particle *splat_particle)
{
	int		i;
	float	dice;
	float	rvalx;
	float	rvaly;

	i = 0;
	dice = (rand() / (float) RAND_MAX);
	rvalx = cos(rand());
	rvaly = sin(rand());
	while (i < MAX_BLOOD_PARTICLES)
	{
		if (dice < 0.5)
			rvalx = -rvalx;
		if (dice < 0.3)
			rvaly = -rvaly;
		splat_particle[i].dir.x = rvalx;
		splat_particle[i].dir.y = rvaly;
		splat_particle[i].p.x = (WIDTH >> 1) + (rvalx * 750);
		splat_particle[i].p.y = (HEIGHT >> 1) + (rvaly * 750);
		splat_particle[i].size.x = dice * 10;
		splat_particle[i].size.y = splat_particle[i].size.x;
		splat_particle[i].reset = splat_particle[i].size;
		splat_particle[i].rp = splat_particle[i].p;
		i++;
	}
}

void	init_blood_particles(t_particle *blood_particle)
{
	int		i;
	float	dice;
	float	rvalx;
	float	rvaly;

	i = 0;
	dice = (rand() / (float) RAND_MAX);
	rvalx = cos(rand());
	rvaly = sin(rand()) + 1;
	while (i < MAX_BLOOD_PARTICLES)
	{
		if (dice < 0.5)
			rvalx = -rvalx;
		if (dice < 0.2)
			rvaly = -rvaly;
		blood_particle[i].dir.x = rvalx * 10;
		blood_particle[i].dir.y = rvaly * 10;
		blood_particle[i].p.x = (WIDTH >> 1) + (rvalx * 150);
		blood_particle[i].p.y = (HEIGHT >> 1) + (rvaly * 150);
		blood_particle[i].size.x = dice * 75;
		blood_particle[i].size.y = blood_particle[i].size.x;
		blood_particle[i].reset = blood_particle[i].size;
		blood_particle[i].rp = blood_particle[i].p;
		i++;
	}
}

void	init_particles(t_particle *particles)
{
	int			i;
	const int	step = WIDTH / N_PARTICLES;

	i = 0;
	ft_memset(particles, 0, sizeof(t_particle[N_PARTICLES]));
	while (i < N_PARTICLES)
	{
		particles[i].dir.y = 1.0;
		particles[i].p.x = i * step;
		particles[i].p.y = ((float) rand() / (float)RAND_MAX) * HEIGHT;
		if (particles[i].p.x < (WIDTH >> 1))
			particles[i].dir.x = -1.0;
		else
			particles[i].dir.x = 1.0;
		particles[i].size.x = (float) rand() / (float)RAND_MAX * 4;
		particles[i].size.y = particles[i].size.x;
		particles[i].reset = particles[i].size;
		i++;
	}
}
