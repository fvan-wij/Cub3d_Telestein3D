/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   entity.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/07 12:13:19 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/05/07 12:13:20 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cbd_audio.h"
#include <cub3d.h>
#include <stdio.h>

void	animate_entity(t_entity *ent, t_app *cbd)
{
	if (ent->animation.enabled == false)
		return ;
	if (ent->type == ENTITY_ENEMY || ent->type == ENTITY_DECOR)
	{
		if (ent->state != ENTITY_IDLE || ent->type == ENTITY_DECOR)
		{
			if (ent->animation.timer <= 0)
			{
				ent->animation.current_frame++;
				if (ent->animation.current_frame == ent->animation.n_frames)
					ent->animation.current_frame = 0;
				ent->animation.timer = ent->animation.duration;
			}
			else
				ent->animation.timer -= cbd->mlx->delta_time;
		}
	}
}

void	move_entities(t_entity *ent, t_app *cbd)
{
	t_vec2d		new_pos;
	t_entity	*tmp_ent;

	tmp_ent = ent;
	while (tmp_ent)
	{
		if (ent->type == ENTITY_ENEMY)
		{
			if (tmp_ent->state == ENTITY_IDLE)
				return ;
			new_pos = tmp_ent->pos;
			new_pos = vec_add(new_pos, vec_mult(tmp_ent->dir,
						tmp_ent->speed * cbd->mlx->delta_time));
			new_pos = resolve_collision(cbd->mapdata->cbd_map,
					tmp_ent->pos, tmp_ent->dir, new_pos);
			tmp_ent->pos = new_pos;
		}
		tmp_ent = tmp_ent->next;
	}
}

void	update_checkpoint(t_entity *ent, t_app *cbd)
{
	t_audio	*audio;

	audio = cbd->audio;
	if (cbd->checkpoint)
		return ;
	if (ft_strncmp(ent->name, "checkpoint", 10) == 0)
	{
		if (vec_distance(ent->pos, cbd->playerdata.pos) < 0.5)
		{
			audio->checkpoint = true;
			cbd->mapdata->cbd_map[2][14] = '4';
		}
	}
}

void	update_entity(t_entity *ent, t_app *cbd)
{
	if (!ent->enabled)
		return ;
	animate_entity(ent, cbd);
	if (ent->type == ENTITY_ENEMY && ent->enabled && ent->health > 20)
	{
		update_enemy(ent, cbd);
	}
	if (ent->type == ENTITY_ITEM || ent->type == ENTITY_ENEMY)
	{
		update_item(ent, cbd);
	}
}

void	update_entities(t_app *cbd)
{
	t_entity	*ent;

	ent = cbd->mapdata->entities;
	while (ent)
	{
		update_entity(ent, cbd);
		ent = ent->next;
	}
}
