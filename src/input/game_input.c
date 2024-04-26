#include "cbd_render.h"
#include <cub3d.h>
#include <cbd_audio.h>

static void	switch_item(mlx_t *mlx, t_inventory *inv, t_audio *audio)
{
	const uint8_t	current_wpn = inv->equipped;

	if (!inv->wpns[inv->equipped].use_anim->loop)
	{
		if (mlx_is_key_down(mlx, MLX_KEY_1))
			inv->equipped = WPN_FIST;
		if (mlx_is_key_down(mlx, MLX_KEY_2)
			&& inv->wpns[WPN_CHAINSAW].in_inventory)
			inv->equipped = WPN_CHAINSAW;
		if (mlx_is_key_down(mlx, MLX_KEY_M)
			&& inv->wpns[WPN_MAP].in_inventory)
			inv->equipped = WPN_MAP;
		if (current_wpn != inv->equipped)
			play_sound(audio, SND_SEARCH, 3.5f, 1.0f);
	}
}

static	void	update_player_movement_state(mlx_t *mlx, t_player *playerdata)
{
	playerdata->state = PLAYER_IDLE;
	if (mlx_is_key_down(mlx, MLX_KEY_UP)
		|| mlx_is_key_down(mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(mlx, MLX_KEY_W)
		|| mlx_is_key_down(mlx, MLX_KEY_S)
		|| mlx_is_key_down(mlx, MLX_KEY_A)
		|| mlx_is_key_down(mlx, MLX_KEY_D))
		playerdata->state = PLAYER_WALKING;
	if (playerdata->state != PLAYER_IDLE
		&& mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT))
		playerdata->state = PLAYER_RUNNING;
}

static void	handle_fire_input(t_inventory *inv, mlx_key_data_t keydata,
		t_app *cbd, t_audio *audio)
{
	if (keydata.key == MLX_KEY_SPACE)
	{
		if (keydata.action == MLX_PRESS)
		{
			if (inv->equipped == WPN_FIST)
			{
				play_sound(audio, SND_PUNCH, 0.5f, 1.0f);
				destroy_wall(cbd->mapdata, &cbd->playerdata, cbd->audio);
			}
			if (inv->equipped == WPN_CHAINSAW
				&& inv->wpns[WPN_CHAINSAW].ammo <= 0)
				play_sound(audio, SND_NO_FUEL, 1.0f, 1.0f);
			inv->wpns[inv->equipped].use_anim->loop = true;
		}
		if (keydata.action == MLX_RELEASE && inv->equipped == WPN_CHAINSAW)
		{
			inv->wpns[WPN_CHAINSAW].use_anim->loop = false;
			stop_sound(audio, SND_SAW);
		}
	}
}

void	game_input(mlx_key_data_t keydata, t_app *cbd, t_audio *audio)
{
	handle_fire_input(cbd->playerdata.inv, keydata, cbd, audio);
	update_player_movement_state(cbd->mlx, &cbd->playerdata);
	switch_item(cbd->mlx, cbd->playerdata.inv, audio);
	if (cbd->render.fx.blood)
		play_sound(audio, SND_GUTS, 1.5f, 1.0f);
}
