#include <cub3d.h>
#include <MLX42.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void	play_single_animation(float dt, t_weapon *weapon)
{
	int	current_frame;

	current_frame = (int)(weapon->fire_animation->timer
			/ weapon->fire_animation->frames[0].duration);
	weapon->fire_animation->timer += dt * 25;
	if (current_frame == 1)
		weapon->use_anim->frames[0].img->enabled = true;
	else
		weapon->use_anim->frames[0].img->enabled = false;
	if (current_frame == 2)
		weapon->use_anim->frames[1].img->enabled = true;
	else
		weapon->use_anim->frames[1].img->enabled = false;
	if (current_frame == 3)
		weapon->use_anim->frames[2].img->enabled = true;
	else
		weapon->use_anim->frames[2].img->enabled = false;
	if (current_frame > MAX_FRAMES)
	{
		weapon->use_anim->frames[0].img->enabled = false;
		weapon->use_anim->frames[1].img->enabled = false;
		weapon->use_anim->frames[2].img->enabled = false;
		weapon->use_anim->timer = 0;
		weapon->use_anim->loop = false;
	}
}

void	play_loop_animation(t_weapon *weapon)
{
	const int	shake = weapon->fire_animation->current_x + (sin(rand()) * 3);

	if (weapon->use_anim->loop)
	{
		weapon->use_anim->frames[1].img->enabled = true;
		weapon->use_anim->frames[1].img->instances->x = shake;
	}
}

void	update_animation(mlx_t *mlx, t_weapon *weapon)
{
	if (weapon->type == WPN_FIST)
		play_single_animation(mlx->delta_time, weapon);
	else if (weapon->type == WPN_CHAINSAW)
	{
		if (weapon->ammo > 0)
			play_loop_animation(weapon);
		else if (weapon->ammo <= 0)
			play_single_animation(mlx->delta_time, weapon);
	}
}

void	reset_animation(t_weapon *current_weapon)
{
	t_animation	*fire_animation;

	fire_animation = current_weapon->fire_animation;
	fire_animation->loop = false;
	if (fire_animation->frames[0].img)
		fire_animation->frames[0].img->enabled = false;
	if (fire_animation->frames[1].img)
		fire_animation->frames[1].img->enabled = false;
	if (fire_animation->frames[2].img)
		fire_animation->frames[2].img->enabled = false;
	if (current_weapon->img->enabled)
		current_weapon->img->enabled = true;
	if (fire_animation->frames[1].img)
		fire_animation->frames[1].img->instances->x = fire_animation->reset_x;
	fire_animation->current_x = fire_animation->reset_x;
}

void	play_weapon_animation(mlx_t	*mlx, t_inventory *inv)
{
	t_weapon	*weapon;

	weapon = &inv->wpns[inv->equipped];
	if (!weapon)
		return ;
	if (inv->equipped == WPN_MAP)
		reset_animation(&inv->wpns[WPN_CHAINSAW]);
	if (weapon->use_anim->loop)
	{
		inv->wpns[inv->equipped].img->enabled = false;
		update_animation(mlx, weapon);
	}
	else
		reset_animation(&inv->wpns[inv->equipped]);
}
