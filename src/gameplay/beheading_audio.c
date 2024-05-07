/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   beheading_audio.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/07 12:07:54 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/05/07 12:07:55 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
