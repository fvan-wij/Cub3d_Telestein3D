#include "cbd_render.h"
#include <cbd_error.h>
#include <cbd_parser.h>
#include <cub3d.h>
#include <stdlib.h>

t_animation	load_animation(mlx_texture_t *texture, uint32_t frame_width,
		uint32_t frame_height)
{
	t_animation	animation;

	if (frame_width != texture->width)
		animation.n_frames = texture->width / frame_width;
	else
		animation.n_frames = 1;
	if (frame_height != texture->height)
		animation.n_animations = texture->height / frame_height;
	else
		animation.n_animations = 1;
	animation.enabled = true;
	animation.current_frame = 0;
	animation.current_animation = 0;
	animation.timer = 0;
	animation.duration = 0.1;
	animation.loop = true;
	return (animation);
}

void	get_core_entity_data(t_entity *ent, char **data)
{
	ent->enabled = true;
	ent->name = ft_strdup(data[1]);
	ent->texture = mlx_load_png(data[2]);
	ent->frame_width = ft_atoi(data[3]);
	ent->frame_height = ft_atoi(data[4]);
	ent->animation = load_animation(ent->texture,
			ent->frame_width, ent->frame_height);
}

void	get_enemy_entity_data(t_entity *ent, char **data)
{
	char		**temp;
	size_t		i;
	size_t		j;
	const size_t n = ft_arrlen(&data[8]);

	ent->speed = (float)ft_atoi(data[5]) + 0.5f;
	ent->health = (float)ft_atoi(data[6]);
	ent->damage = (float)ft_atoi(data[7]);
	ent->type = ENTITY_ENEMY;
	ent->destinations = ft_calloc(n + 1, sizeof(t_vec2d));
	ent->n_dest = n;
	i = 8;
	j = 0;
	while (data[i] && j < n)
	{
		temp = ft_split(data[i], ',');
		ent->destinations[j].x = ft_atoi(temp[0]) + .5;
		ent->destinations[j].y = ft_atoi(temp[1]) + .5;
		ft_del_2d(temp);
		i++;
		j++;
	}
	ent->pos.x = ent->destinations[0].x + .5;
	ent->pos.y = ent->destinations[0].y + .5;
}

void	get_other_entity_data(t_entity *ent, char **data, uint8_t type)
{
	char	p[2];
	size_t	i;

	i = 5;
	if (type == CONT_OBJECT)
		ent->type = ENTITY_DECOR;
	else
		ent->type = ENTITY_ITEM;
	ft_strlcpy(p, data[i], 3);
	ent->pos.x = (float)ft_atoi(p) + 0.5;
	ft_strlcpy(p, &data[i][3], 3);
	ent->pos.y = (float)ft_atoi(p) + 0.5;
}

/*
** Extracts entity data from the given line and stores it in the t_entity list
**
*/
t_entity	*append_entity(t_entity *entities, char *line, uint8_t type)
{
	t_entity	*new_entity;
	t_entity	*curr;
	char		**temp;
	// char		**temp2;
	// char		p[2];
	// size_t		i;
	// size_t		j;

	new_entity = ft_calloc(1, sizeof(t_entity));
	if (!new_entity)
		return (cbd_error(ERR_ALLOC), NULL);
	temp = ft_split(line, ' ');
	if (!temp)
		return (cbd_error(ERR_ALLOC), NULL);
	// const size_t n = ft_arrlen(&temp[8]);

	get_core_entity_data(new_entity, temp);

	// new_entity->enabled = true;
	// new_entity->name = ft_strdup(temp[1]);
	// new_entity->texture = mlx_load_png(temp[2]);
	// new_entity->frame_width = ft_atoi(temp[3]);
	// new_entity->frame_height = ft_atoi(temp[4]);
	// new_entity->animation = load_animation(new_entity->texture,
	// 		new_entity->frame_width, new_entity->frame_height);
	if (type == CONT_ENEMY)
	{

		get_enemy_entity_data(new_entity, temp);

		// new_entity->speed = (float)ft_atoi(temp[5]) + 0.5f;
		// new_entity->health = (float)ft_atoi(temp[6]);
		// new_entity->damage = (float)ft_atoi(temp[7]);
		// new_entity->type = ENTITY_ENEMY;
		// new_entity->destinations = ft_calloc(n + 1, sizeof(t_vec2d));
		// new_entity->n_dest = n;
		// i = 8;
		// j = 0;
		// while (temp[i] && j < n)
		// {
		// 	temp2 = ft_split(temp[i], ',');
		// 	new_entity->destinations[j].x = ft_atoi(temp2[0]) + .5;
		// 	new_entity->destinations[j].y = ft_atoi(temp2[1]) + .5;
		// 	ft_del_2d(temp2);
		// 	i++;
		// 	j++;
		// }
		// new_entity->pos.x = new_entity->destinations[0].x + .5;
		// new_entity->pos.y = new_entity->destinations[0].y + .5;
	}
	else if (type == CONT_OBJECT || type == CONT_ITEM)
	{

		get_other_entity_data(new_entity, temp, type);

		// if (type == CONT_OBJECT)
		// 	new_entity->type = ENTITY_DECOR;
		// else
		// 	new_entity->type = ENTITY_ITEM;
		// i = 5;
		// ft_strlcpy(p, temp[i], 3);
		// new_entity->pos.x = (float)ft_atoi(p) + 0.5;
		// ft_strlcpy(p, &temp[i][3], 3);
		// new_entity->pos.y = (float)ft_atoi(p) + 0.5;
	}
	if (!entities)
		return (ft_del_2d(temp), new_entity);
	else
	{
		curr = entities;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new_entity;
		return (ft_del_2d(temp), entities);
	}
}

