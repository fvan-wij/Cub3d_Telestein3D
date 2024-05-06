/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   entity.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/06 16:24:50 by dritsema      #+#    #+#                 */
/*   Updated: 2024/05/06 16:31:32 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdlib.h>
#include <stdio.h>

static void	set_zbuffer(double *zbuffer)
{
	int	i;

	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		zbuffer[i] = 1000000;
		i++;
	}
}

t_render_entity	init_entity_render2(t_entity *entity, t_render_entity re)
{
	if (re.draw_start_y < 0)
		re.draw_start_y = 0;
	if (re.draw_end_y >= HEIGHT)
		re.draw_end_y = HEIGHT - 1;
	re.sprite_width = abs((int)(HEIGHT / (re.transform_y)));
	re.draw_start_x = -re.sprite_width / 2 + re.sprite_screen_x;
	if (re.draw_start_x < 0)
		re.draw_start_x = 0;
	re.draw_end_x = re.sprite_width / 2 + re.sprite_screen_x;
	if (re.draw_end_x >= WIDTH)
		re.draw_end_x = WIDTH - 1;
	re.tex_width = entity->frame_width;
	re.tex_height = entity->frame_height;
	return (re);
}

t_render_entity	init_entity_render(
		t_render *render, t_entity *entity, t_player *p)
{
	t_render_entity	re;

	re.render = render;
	re.entity = entity;
	re.player = p;
	re.ent_x = entity->pos.x - p->pos.x;
	re.ent_y = entity->pos.y - p->pos.y;
	re.inv_det = 1.0 / (p->plane.x * p->dir.y - p->dir.x * p->plane.y);
	re.transform_x = re.inv_det * (p->dir.y * re.ent_x - p->dir.x * re.ent_y);
	re.transform_y = re.inv_det
		* (-p->plane.y * re.ent_x + p->plane.x * re.ent_y);
	re.sprite_screen_x = (int)
		((WIDTH / 2) * (1.0 + re.transform_x / re.transform_y));
	re.sprite_height = abs((int)(HEIGHT / (re.transform_y)));
	re.draw_start_y = -re.sprite_height / 2 + HEIGHT / 2 + render->y_offset;
	re.draw_end_y = re.sprite_height / 2 + HEIGHT / 2 + render->y_offset;
	return (init_entity_render2(entity, re));
}

// Render an entity
void	render_entity(t_render *render, t_entity *ent, t_player *player)
{
	t_render_entity	rent;
	int				strip;

	rent = init_entity_render(render, ent, player);
	if (ent->enabled == false)
		return ;
	ent->distance = vec_distance(player->pos, ent->pos);
	if (ent->distance < 100.0)
		ent->distance /= 100;
	strip = rent.draw_start_x;
	while (strip < rent.draw_end_x)
	{
		if (rent.transform_y > 0 && strip > 0 && strip < WIDTH
			&& rent.transform_y < rent.render->rays[strip].wall_dist)
			draw_entity_strip(strip, rent);
		strip++;
	}
}

// Loop over entities and render each one
void	render_entities(t_render *render, t_entity *entities, t_player *player)
{
	t_entity	*ent;

	ent = entities;
	player->target_distance = 0;
	player->target_entity = NULL;
	ft_memset(render->sprite_img->pixels, 0, WIDTH * HEIGHT * 4);
	set_zbuffer(render->zbuffer);
	while (ent)
	{
		render_entity(render, ent, player);
		ent = ent->next;
	}
}
