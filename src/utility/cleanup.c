#include <cub3d.h>
#include <libft.h>
#include <MLX42.h>
#include <stdlib.h>

void	free_node(t_entity *node)
{
	if (node->destinations)
		free(node->destinations);
	if (node->texture)
		free(node->texture);
	free(node);
}

void	free_jump_table(t_map *map)
{
	int	i;

	i = 0;
	while (i < 255)
	{
		if (map->walls.w_path[i])
			free(map->walls.w_path[i]);
		i++;
	}
	i = 0;
	while (i < 255)
	{
		if (map->walls.w_tex[i])
			mlx_delete_texture(map->walls.w_tex[i]);
		i++;
	}
}

void	cleanup_map(t_map *map)
{
	t_entity	*temp;
	t_entity	*curr;

	if (map->raw_data)
		ft_del_2d(map->raw_data);
	if (map->cbd_map)
		ft_del_2d(map->cbd_map);
	free_jump_table(map);
	if (map->entities)
	{
		curr = map->entities;
		while (curr->next != NULL)
		{
			temp = curr;
			curr = curr->next;
			free_node(temp);
		}
	}
	free(map);
}

void	cleanup_menu(t_menu *menu)
{
	free(menu);
}

void	cleanup_render(t_render render)
{
	free(render.zbuffer);
}

void	cleanup(t_app *app)
{
	if (app->mapdata)
		cleanup_map(app->mapdata);
	if (app->menudata)
		cleanup_menu(app->menudata);
	cleanup_render(app->render);
}
