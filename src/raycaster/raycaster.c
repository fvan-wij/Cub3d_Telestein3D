#include <cub3d.h>
#include <MLX42.h>
#include <math.h>

static t_vec2d	calculate_delta_distance(t_vec2d dir)
{
	t_vec2d	delta_dist;

	if (dir.x == 0)
		delta_dist.x = 1e30;
	else
		delta_dist.x = fabs(1 / dir.x);
	if (dir.y == 0)
		delta_dist.y = 1e30;
	else
		delta_dist.y = fabs(1 / dir.y);
	return (delta_dist);
}

static void	calculate_dda_components(t_dda *dda, t_ray *ray,
		t_vec2d pos, t_vec2d dir)
{
	dda->vec_map = vec2i_assign(pos.x, pos.y);
	dda->delta_dist = calculate_delta_distance(dir);
	if (ray->dir.x < 0)
	{
		dda->step.x = -1;
		dda->side_dist.x = (pos.x - dda->vec_map.x) * dda->delta_dist.x;
	}
	else
	{
		dda->step.x = 1;
		dda->side_dist.x = (dda->vec_map.x + 1.0 - pos.x) * dda->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		dda->step.y = -1;
		dda->side_dist.y = (pos.y - dda->vec_map.y) * dda->delta_dist.y;
	}
	else
	{
		dda->step.y = 1;
		dda->side_dist.y = (dda->vec_map.y + 1.0 - pos.y) * dda->delta_dist.y;
	}
}

static void	cast_dda_ray(t_ray *ray, t_dda *dda, char **map)
{
	while (!dda->hit)
	{
		if (dda->side_dist.x < dda->side_dist.y)
		{
			dda->side_dist.x += dda->delta_dist.x;
			dda->vec_map.x += dda->step.x;
			ray->side = 0;
		}
		else
		{
			dda->side_dist.y += dda->delta_dist.y;
			dda->vec_map.y += dda->step.y;
			ray->side = 1;
		}
		if (map[dda->vec_map.y][dda->vec_map.x]
			&& dda->vec_map.x >= 0 && dda->vec_map.y >= 0
			&& (is_wall_bonus(map[dda->vec_map.y][dda->vec_map.x])))
			dda->hit = true;
	}
}

/*
Needs:
	A context (The map)
	A position
	A direction
*/
t_ray	raycast(char **map, t_vec2d pos, t_vec2d dir)
{
	t_ray	ray;
	t_dda	dda;

	ray.dir = dir;
	ft_bzero(&dda, sizeof(t_dda));
	calculate_dda_components(&dda, &ray, pos, dir);
	cast_dda_ray(&ray, &dda, map);
	if (ray.side == 0)
		ray.wall_dist = (dda.side_dist.x - dda.delta_dist.x);
	else
		ray.wall_dist = (dda.side_dist.y - dda.delta_dist.y);
	ray.tile = map[dda.vec_map.y][dda.vec_map.x];
	ray.intersection.x = (pos.x + (ray.dir.x * ray.wall_dist));
	ray.intersection.y = (pos.y + (ray.dir.y * ray.wall_dist));
	return (ray);
}

void	cast_rays(char **map, t_render *render, t_player *p)
{
	int		x;
	double	camera_x;
	t_vec2d	dir;

	x = 0;
	while (x < WIDTH)
	{
		camera_x = (double)(2.0 * x / WIDTH) - 1;
		dir = vec_assign(p->dir.x + (p->plane.x * camera_x),
				p->dir.y + (p->plane.y * camera_x));
		render->rays[x] = raycast(map, p->pos, dir);
		x++;
	}
}
