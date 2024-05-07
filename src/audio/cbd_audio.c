/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cbd_audio.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/07 12:07:11 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/05/07 12:07:14 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cbd_audio.h>
#include <stdlib.h>
#include <libft.h>

void	play_sound(const t_audio *audio, uint8_t type,
		float volume, float pitch)
{
	ma_sound_seek_to_pcm_frame(audio->sound[type], 0);
	ma_sound_set_pitch(audio->sound[type], pitch);
	ma_sound_set_volume(audio->sound[type], volume);
	ma_sound_start(audio->sound[type]);
}

static void	alternate_pitch(const t_audio *audio, uint8_t type)
{
	static float	timer;
	static int		alternate;

	timer -= 0.25;
	if (alternate == 0)
		ma_sound_set_pitch(audio->sound[type], 1.05f);
	else
		ma_sound_set_pitch(audio->sound[type], 0.97f);
	if (timer < 0)
	{
		alternate++;
		timer = 1;
	}
	if (alternate > 1)
		alternate = 0;
}

void	loop_sound(const t_audio *audio, uint8_t type, bool alternate)
{
	ma_bool32	is_looping;

	is_looping = true;
	if (ma_sound_is_playing(audio->sound[type]))
		return ;
	if (alternate)
		alternate_pitch(audio, type);
	ma_sound_set_looping(audio->sound[type], is_looping);
	ma_sound_start(audio->sound[type]);
}

void	stop_sound(const t_audio *audio, uint8_t type)
{
	ma_sound_stop(audio->sound[type]);
	ma_sound_seek_to_pcm_frame(audio->sound[type], 0);
}

void	reset_sounds(const t_audio *audio)
{
	size_t	i;

	i = 0;
	while (i < SND_SIZE)
	{
		ma_sound_stop(audio->sound[i]);
		ma_sound_seek_to_pcm_frame(audio->sound[i], 0);
		i++;
	}
}
