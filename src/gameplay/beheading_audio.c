#include <cub3d.h>
#include <cbd_audio.h>

void	start_sawing(t_app *cbd)
{
	const t_audio	*audio = cbd->audio;

	cbd->beheading.sawing = true;
	stop_sound(audio, SND_SAW_IDLE);
	play_sound(audio, SND_GUTS, 1.0f, 1.0f);
	loop_sound(audio, SND_SAW, false);
}

void	stop_sawing(t_app *cbd)
{
	const t_audio	*audio = cbd->audio;

	cbd->beheading.sawing = false;
	stop_sound(audio, SND_SAW);
	stop_sound(audio, SND_GUTS);
	loop_sound(audio, SND_SAW_IDLE, false);
}
