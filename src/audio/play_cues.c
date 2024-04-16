#include <cbd_audio.h>
#include <cub3d.h>

void	take_damage(t_audio *audio)
{
	if (audio->damage)
	{
		play_sound(audio, SND_NEAR_DEATH, 0.75f, 0.95f);
		audio->damage = false;
	}
}

void	play_jumpscare(t_audio *audio)
{
	if (audio->trigger1 && audio->trigger1->distance < 0.03
		&& !audio->t1 && audio->trigger1->distance != 0.0f)
	{
		play_sound(audio, SND_IMPACT, 1.3f, 1.0f);
		audio->t1 = true;
	}
	else if (audio->trigger2 && audio->trigger2->distance < 0.15
		&& !audio->t2 && audio->trigger2->distance != 0.0f)
	{
		play_sound(audio, SND_IMPACT3, 1.0f, 1.0f);
		play_sound(audio, SND_CROWS, 1.0f, 1.0f);
		play_sound(audio, SND_BUSH, 1.0f, 1.0f);
		audio->t2 = true;
	}
}

void	play_pickup(t_audio *audio)
{
	if (audio->pickup)
	{
		play_sound(audio, SND_PICKUP, 1.0f, 1.0f);
		audio->pickup = false;
	}
}

void	play_chase(t_audio *audio)
{
	if (audio->chase)
	{
		loop_sound(audio, SND_CHASE, false);
		loop_sound(audio, SND_LAUGH, false);
		audio->chase = false;
	}
	if (audio->enemy && audio->enemy->dead)
	{
		stop_sound(audio, SND_LAUGH);
	}
}
