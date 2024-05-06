/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   audio_trigger_init.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/26 16:33:46 by dritsema      #+#    #+#                 */
/*   Updated: 2024/04/26 16:33:46 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cbd_audio.h"
#include "cub3d.h"

void	init_sound_triggers(t_audio *audio, t_app *cbd)
{
	t_entity	*ent;

	ent = cbd->mapdata->entities;
	while (ent)
	{
		if (ft_strncmp("tv", ent->name, 2) == 0)
			audio->tv = ent;
		if (ft_strncmp("trigger1", ent->name, 8) == 0)
			audio->trigger1 = ent;
		if (ft_strncmp("trigger2", ent->name, 8) == 0)
			audio->trigger2 = ent;
		if (ft_strncmp("po", ent->name, 2) == 0)
			audio->enemy = ent;
		ent = ent->next;
	}
}
