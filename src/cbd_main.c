/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cbd_main.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 12:13:12 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/05/07 15:20:07 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <cbd_audio.h>

bool	cbd_main(t_app *cbd)
{
	if (cbd_init(cbd))
		return (FAILURE);
	cbd->audio = cbd_init_audio();
	play_sound(cbd->audio, SND_MENU, 0.6f, 1.0f);
	init_sound_triggers(cbd->audio, cbd);
	mlx_loop(cbd->mlx);
	cbd_uninit_audio(cbd->audio);
	cleanup(cbd);
	return (SUCCESS);
}
