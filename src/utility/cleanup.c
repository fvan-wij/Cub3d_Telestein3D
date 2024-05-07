/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 12:12:39 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/05/07 15:31:03 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <libft.h>
#include <MLX42.h>
#include <stdlib.h>

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
		while (curr != NULL)
		{
			temp = curr;
			curr = curr->next;
			free_node(temp);
		}
	}
	free(map);
}

void	cleanup_player(t_player player, t_app *app)
{
	size_t	i;

	i = 0;
	if (player.inv)
	{
		while (i < WPN_SIZE)
		{
			mlx_delete_image(app->mlx, player.inv->wpn[i].img);
			free(player.inv->wpn[i].use_anim);
			i++;
		}
	}
	if (player.inv)
		free(player.inv);
}

void	cleanup_render(t_render *render, mlx_t *mlx)
{
	size_t	i;

	mlx_delete_image(mlx, render->img);
	mlx_delete_image(mlx, render->sprite_img);
	mlx_delete_image(mlx, render->po_head);
	i = 0;
	while (i < HUD_SIZE)
	{
		mlx_delete_image(mlx, render->hud->img[i]);
		i++;
	}
	free(render->hud);
	free(render->zbuffer);
}

void	cleanup(t_app *app)
{
	if (app->mapdata)
		cleanup_map(app->mapdata);
	if (app->menudata)
		free(app->menudata);
	cleanup_render(&app->render, app->mlx);
	cleanup_player(app->playerdata, app);
	mlx_terminate(app->mlx);
}
