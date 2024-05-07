#include <cub3d.h>
#include <cbd_error.h>

static void	init_entity_data(t_entity *new, char **temp)
{
	new->enabled = true;
	new->name = ft_strdup(temp[1]);
	new->texture = mlx_load_png(temp[2]);
	new->frame_width = ft_atoi(temp[3]);
	new->frame_height = ft_atoi(temp[4]);
	new->animation = load_animation(new->texture,
			new->frame_width, new->frame_height);
}

static t_vec2d	*get_destinations(const char **temp, size_t n)
{
	size_t	i;
	size_t	j;
	char	**dst;
	t_vec2d	*destinations;

	i = 8;
	j = 0;
	destinations = ft_calloc(n + 1, sizeof(t_vec2d));
	while (temp[i] && j < n)
	{
		dst = ft_split(temp[i], ',');
		destinations[j] = vec_assign(ft_atoi(dst[0]) + .5,
				ft_atoi(dst[1]) + .5);
		ft_del_2d(dst);
		i++;
		j++;
	}
	return (destinations);
}

static t_entity	*append_enemy(t_entity *new, const char **temp)
{
	size_t		n;

	new->speed = (float) ft_atoi(temp[5]) + 0.5f;
	new->health = (float) ft_atoi(temp[6]);
	new->damage = (float) ft_atoi(temp[7]);
	new->type = ENTITY_ENEMY;
	n = ft_arrlen((char **)&temp[8]);
	new->n_dest = n;
	new->destinations = get_destinations(temp, n);
	new->pos = vec_assign(new->destinations[0].x + .5,
			new->destinations[0].y + .5);
	return (new);
}

static t_entity	*append_object(t_entity *new, const char **temp, uint8_t type)
{
	char	p[2];
	size_t	i;

	if (type == CONT_OBJECT)
		new->type = ENTITY_DECOR;
	else
		new->type = ENTITY_ITEM;
	i = 5;
	ft_strlcpy(p, temp[i], 3);
	new->pos.x = (float) ft_atoi(p) + 0.5;
	ft_strlcpy(p, &temp[i][3], 3);
	new->pos.y = (float) ft_atoi(p) + 0.5;
	return (new);
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

	new_entity = ft_calloc(1, sizeof(t_entity));
	if (!new_entity)
		return (cbd_error(ERR_ALLOC), NULL);
	temp = ft_split(line, ' ');
	if (!temp)
		return (cbd_error(ERR_ALLOC), NULL);
	init_entity_data(new_entity, temp);
	if (type == CONT_ENEMY)
		new_entity = append_enemy(new_entity, (const char **) temp);
	else if (type == CONT_OBJECT || type == CONT_ITEM)
		new_entity = append_object(new_entity, (const char **) temp, type);
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
