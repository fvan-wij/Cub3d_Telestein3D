#include "cbd_render.h"
#include <cbd_audio.h>
#include <cub3d.h>

static void	loop_dynamic_audio(t_audio *audio, t_entity *ent,
								uint8_t sound, float volume)
{
	float	vol;

	if (!ent || ent->distance > 1.0 || !ent || ent->distance > 1.0)
	{
		ma_sound_set_volume(audio->sound[sound], 0.0f);
		return ;
	}
	vol = volume - ent->distance;
	if (vol < 0.0)
		vol = 0.0f;
	ma_sound_set_volume(audio->sound[sound], vol);
}

static void	update_walking_sounds(t_audio *audio, enum e_player_state state)
{
	if (state == PLAYER_RUNNING)
		loop_sound(audio, SND_WALK_GRASS, true);
	if (state == PLAYER_WALKING)
		loop_sound(audio, SND_WALK_GRASS, true);
	if (state == PLAYER_IDLE)
		stop_sound(audio, SND_WALK_GRASS);
}

static void	handle_chainsaw_sound(t_audio *audio, t_inventory *inv)
{
	if (inv->wpns[inv->equipped].use_anim->loop
		&& inv->equipped == WPN_CHAINSAW)
		loop_sound(audio, SND_SAW, false);
	else
		stop_sound(audio, SND_SAW);
	if (inv->equipped == WPN_CHAINSAW
		&& inv->wpns[WPN_CHAINSAW].use_anim->loop == false
		&& inv->wpns[WPN_CHAINSAW].ammo > 0)
		loop_sound(audio, SND_SAW_IDLE, false);
	else
		stop_sound(audio, SND_SAW_IDLE);
	if (ma_sound_is_playing(audio->sound[SND_SAW])
		&& inv->wpns[WPN_CHAINSAW].ammo <= 0)
	{
		stop_sound(audio, SND_SAW);
		play_sound(audio, SND_NO_FUEL2, 0.75f, 1.0f);
	}
	if (inv->wpns[WPN_CHAINSAW].ammo <= 0)
	{
		stop_sound(audio, SND_SAW);
		stop_sound(audio, SND_SAW_IDLE);
	}
}

void	update_game_audio(t_audio *audio, t_inventory *inv,
							enum e_player_state state)
{
	stop_sound(audio, SND_MENU);
	stop_sound(audio, SND_GAME_OVER);
	loop_sound(audio, SND_AMBIENT_LAUGH, false);
	loop_sound(audio, SND_TV_NOISE, false);
	loop_sound(audio, SND_TV_BYE + audio->channel, false);
	loop_dynamic_audio(audio, audio->tv, SND_TV_NOISE, 0.2f);
	loop_dynamic_audio(audio, audio->tv, SND_TV_BYE + audio->channel, 0.2f);
	loop_dynamic_audio(audio, audio->enemy, SND_LAUGH, 1.0f);
	take_damage(audio);
	play_jumpscare(audio);
	play_pickup(audio);
	play_chase(audio);
	update_walking_sounds(audio, state);
	handle_chainsaw_sound(audio, inv);
}
