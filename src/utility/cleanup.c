#include <cub3d.h>
#include <libft.h>
#include <MLX42.h>
#include <stdlib.h>

	// enum e_entity_type	type;
	// t_vec2d				pos;
	// t_vec2d				dir;
	// t_vec2d				*destinations;
	// int					health;
	// int					damage;
	// int					current_dest;
	// float				speed;
	// float				audio_timer;
	// mlx_texture_t		*texture;
	// enum e_entity_state	state;

void	free_node(t_entity *node)
{
	if (node->destinations)
		free(node->destinations);
	if (node->texture)
		free(node->texture);
	free(node);
}

void	cleanup_map(t_map *map)
{
	int i;

	if (map->raw_data)
		ft_del_2d(map->raw_data);
	if (map->cbd_map)
		ft_del_2d(map->cbd_map);
	if (map->walls.w_path)
		ft_del_2d(map->walls.w_path);
	if (map->walls.cw_path)
		ft_del_2d(map->walls.cw_path);
	if (map->walls.w_tex)
	{
		i = 0;
		while (i < map->walls.n_w)
		{
			mlx_delete_texture(map->walls.w_tex[i]);
			i++;
		}
		free(map->walls.w_tex);
	}
	if (map->walls.cw_tex)
	{
		i = 0;
		while (i < map->walls.n_cw)
		{
			mlx_delete_texture(map->walls.cw_tex[i]);
			i++;
		}
		free(map->walls.cw_tex);
	}
	if (map->entities)
	{
		t_entity *temp;
		t_entity *curr;

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
	// int i;

	// i = 0;
	// while (i < M_SIZE)
	// {
	// 	// mlx_delete_texture(menu->menu_tex[i]);
	// 	i++;
	// }
	free(menu);
}

void	cleanup(t_app *app)
{
	if (app->mapdata)
		cleanup_map(app->mapdata);
	if (app->menudata)
		cleanup_menu(app->menudata);
}
