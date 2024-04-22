#include <libft.h>
#include <MLX42.h>
#include <cub3d.h>
#include <cbd_error.h>
#include <cbd_audio.h>
#include <math.h>

float	correct_wall_clipping(float pos_component, bool invert,
		float pot_component, float radius)
{
	float	overlap;
	float	delta;

	if (invert)
		delta = 1 - pos_component;
	else
		delta = pos_component;
	if (delta <= radius)
	{
		overlap = radius - delta;
		if (invert)
			pot_component -= overlap;
		else
			pot_component += overlap;
	}
	return (pot_component);
}

t_vec2d	resolve_collision(char **map, t_vec2d pos,
		t_vec2d dir, t_vec2d potential_pos)
{
	const char	u = map[(int)pos.y - 1][(int)pos.x];
	const char	r = map[(int)pos.y][(int)pos.x + 1];
	const char	d = map[(int)pos.y + 1][(int)pos.x];
	const char	l = map[(int)pos.y][(int)pos.x - 1];
	const float	radius = vec_length(dir) / 8;

	if ((pos.x - (int) pos.x) <= 0.5 && is_wall_bonus(l))
		potential_pos.x = correct_wall_clipping((pos.x - (int) pos.x),
				false, potential_pos.x, radius);
	if ((pos.y - (int) pos.y) >= 0.5 && is_wall_bonus(d))
		potential_pos.y = correct_wall_clipping((pos.y - (int) pos.y),
				true, potential_pos.y, radius);
	if ((pos.y - (int) pos.y) <= 0.5 && is_wall_bonus(u))
		potential_pos.y = correct_wall_clipping((pos.y - (int) pos.y),
				false, potential_pos.y, radius);
	if ((pos.x - (int) pos.x) >= 0.5 && is_wall_bonus(r))
		potential_pos.x = correct_wall_clipping((pos.x - (int) pos.x),
				true, potential_pos.x, radius);
	return (potential_pos);
}

void	headbob(float *headbob, float speed)
{
	*headbob += speed;
	if (*headbob > 2 * M_PI)
		*headbob = 0;
}

void	reset_player_animation(t_render *render, mlx_t *mlx)
{
	render->headbob -= mlx->delta_time;
	if (render->headbob < 0)
		render->headbob = 0;
}

void	peek_map(t_inventory *inv, t_render *render,
		mlx_image_t *img, mlx_t *mlx)
{
	t_weapon	*weapon;

	weapon = &inv->weapons[inv->equipped];
	weapon->img->instances[0].x = (cos(render->headbob) * 2)
		+ (WIDTH >> 1) - (weapon->img->width >> 1);
	if (render->map_peak < -99)
		render->map_peak = -99;
	if (img->enabled && render->map_peak > -100)
		render->map_peak -= cos(mlx->delta_time) * 2;
	else if (render->map_peak < 0)
		render->map_peak += cos(mlx->delta_time) * 2;
}
