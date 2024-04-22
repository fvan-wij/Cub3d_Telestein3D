#include "cbd_render.h"
#include <cub3d.h>
#include <cbd_error.h>
#include <cbd_audio.h>

void	mouse_hook(mouse_key_t button, action_t action,
		modifier_key_t mods, void *param)
{
	const t_app			*cbd = (t_app *) param;
	const t_audio		*audio = (t_audio *) cbd->audio;
	const t_inventory	*inv = cbd->playerdata.inv;

	(void) mods;
	if (button == MLX_MOUSE_BUTTON_LEFT)
	{
		if (action == MLX_PRESS)
		{
			if (inv->equipped == WPN_FIST)
			{
				play_sound(audio, SND_PUNCH, 0.5f, 1.0f);
				destroy_wall(cbd->mapdata, &cbd->playerdata, cbd->audio);
			}
			if (inv->equipped == WPN_CHAINSAW
				&& inv->weapons[WPN_CHAINSAW].ammo <= 0)
				play_sound(audio, SND_NO_FUEL, 1.0f, 1.0f);
			inv->weapons[inv->equipped].fire_animation->loop = true;
		}
		if (action == MLX_RELEASE && inv->equipped == WPN_CHAINSAW)
		{
			inv->weapons[WPN_CHAINSAW].fire_animation->loop = false;
			stop_sound(audio, SND_SAW);
		}
	}
}
