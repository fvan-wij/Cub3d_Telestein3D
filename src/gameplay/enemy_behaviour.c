/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   enemy_behaviour.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/07 12:07:58 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/05/07 12:07:59 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cbd_audio.h"
#include <cub3d.h>

static void	handle_idle_state(t_entity *ent)
{
	ent->state = ENTITY_IDLE;
	ent->current_dest++;
	if (ent->current_dest == ent->n_dest)
		ent->current_dest = 0;
}

static void	handle_agro_state(t_entity *ent, t_app *cbd)
{
	t_audio	*audio;

	audio = cbd->audio;
	ent->state = ENTITY_AGROED;
	cbd->mapdata->cbd_map[2][14] = '4';
	cbd->checkpoint = true;
	audio->chase = true;
	ent->dir = vec_sub(cbd->playerdata.pos, ent->pos);
	if (vec_distance(cbd->playerdata.pos, ent->pos) < 0.6)
	{
		if (cbd->playerdata.i_time <= 0)
		{
			ent->state = ENTITY_ATTACK;
			audio->damage = true;
			attack_player(ent, &cbd->playerdata, &cbd->render.fx);
		}
		ent->state = ENTITY_IDLE;
	}
}

static void	handle_patrol_state(t_entity *ent)
{
	ent->dir = vec_sub(ent->destinations[ent->current_dest], ent->pos);
	ent->state = ENTITY_PATROL;
}

void	update_enemy(t_entity *ent, t_app *cbd)
{
	if (vec_distance(ent->pos, ent->destinations[ent->current_dest]) < 0.1)
		handle_idle_state(ent);
	if (vec_distance(cbd->playerdata.pos, ent->pos) < 10
		&& ft_strncmp("po", ent->name, 8) == 0)
		handle_agro_state(ent, cbd);
	else if (vec_distance(ent->destinations[ent->current_dest],
			ent->pos) > 0.05)
		handle_patrol_state(ent);
	vec_normalize(&ent->dir);
}
