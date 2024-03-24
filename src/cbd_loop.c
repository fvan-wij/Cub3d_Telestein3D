#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <cbd_audio.h>

void	cbd_loop(void *param)
{
	t_app *cbd;
	t_audio *audio;

	cbd = param;

	audio = cbd->audio;
	if (cbd->menudata->state == OFF)
	{
		cbd->render.img->instances->enabled = true;
		cbd->render.sprite_img->instances->enabled = true;
		move_player(cbd);
		update_entities(cbd);
		play_weapon_animation(cbd->mlx, cbd->playerdata.inv);
		cbd_render(cbd);
	}
	else if (cbd->menudata->state == MAP_SELECT)
		display_preview(cbd->menudata, cbd->mapdata);
	else if (cbd->menudata->state == MAP_LOAD)
	{
		change_map(cbd);
	}
	float vol = 0.6f - cbd->mapdata->entities->distance;
	if (vol > 0.6f)
		vol = 0.6f;
	if (vol < 0.0f)
		vol = 0.0f;
	ma_sound_set_volume(audio->sound[SND_TV_NOISE], vol);
	if (cbd->render.b_timer)
	{
		cbd->render.timer -= cbd->mlx->delta_time * 1000;
		cbd->render.headbob *= cbd->mlx->delta_time * 100;
	}
	if (cbd->render.timer < 0)
	{
		cbd->render.timer = 100;
		cbd->render.b_timer = false;
	}
}
