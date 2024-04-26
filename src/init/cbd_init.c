/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cbd_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/16 15:31:34 by dritsema      #+#    #+#                 */
/*   Updated: 2024/04/26 16:33:06 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <cbd_error.h>
#include <MLX42.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

mlx_image_t	*cbd_init_texture_img(mlx_t *mlx, char *path)
{
	mlx_texture_t	*tmp;
	mlx_image_t		*img;

	tmp = mlx_load_png(path);
	if (!tmp)
		return (NULL);
	img = mlx_texture_to_image(mlx, tmp);
	mlx_delete_texture(tmp);
	return (img);
}

void	init_render(t_render *render, t_hud *hud, t_inventory *inv)
{
	render->hud = hud;
	render->inv = inv;
	render->sprite = malloc(sizeof(t_sprite) * 1);
	render->sprite[0].pos.x = 2.5;
	render->sprite[0].pos.y = 9;
	render->sprite[0].tex = mlx_load_png
		("./data/textures/sprites/chainsaw.png");
	render->timer = 100;
	init_blood_splat(render->splat);
	init_blood_particles(render->blood);
}

void	init_playerdata(t_player *playerdata, t_map *mapdata)
{
	t_vec2d	start;

	start = mapdata->start_pos;
	mapdata->cbd_map[(int)start.y][(int)start.x] = '0';
	playerdata->pos = mapdata->start_pos;
	playerdata->dir = mapdata->start_dir;
	playerdata->pos.x += 0.5f;
	playerdata->pos.y += 0.5f;
	playerdata->scalar = 1;
	playerdata->plane = vec_rotate(playerdata->dir, M_PI / 2);
	playerdata->map_peak = 0;
	playerdata->target_distance = 0;
	playerdata->target_entity = NULL;
	playerdata->i_time = 0;
	playerdata->health = 10;
	playerdata->head_height = 0;
}

bool	cbd_init2(t_app *cbd)
{
	mlx_image_to_window(cbd->mlx, cbd->render.img, 0, 0);
	mlx_image_to_window(cbd->mlx, cbd->render.sprite_img, 0, 0);
	mlx_image_to_window(cbd->mlx, cbd->hud->img[HUD_OVERLAY], 0, 0);
	mlx_image_to_window(cbd->mlx, cbd->render.po_head, 0, 0);
	mlx_image_to_window(cbd->mlx, cbd->hud->img[HUD_MAP],
		(WIDTH >> 1) - (MINIMAP_WIDTH >> 2) - 16,
		(HEIGHT >> 1) + (MINIMAP_HEIGHT >> 3) - 8);
	mlx_image_to_window(cbd->mlx, cbd->hud->img[HUD_CRT], 0, 0);
	mlx_image_to_window(cbd->mlx, cbd->hud->img[HUD_PULSE], 0, 0);
	cbd->menudata = cbd_init_menu(cbd->mlx, cbd->mapdata);
	if (!cbd->menudata)
		return (cbd_error(ERR_ALLOC), FAILURE);
	init_playerdata(&cbd->playerdata, cbd->mapdata);
	init_render(&cbd->render, cbd->hud, cbd->playerdata.inv);
	init_particles(cbd->particles);
	cbd_init_beheading(cbd);
	cbd->elapsed_time = 0;
	mlx_key_hook(cbd->mlx, cbd_input, cbd);
	mlx_cursor_hook(cbd->mlx, cursor_hook, cbd);
	mlx_mouse_hook(cbd->mlx, mouse_hook, cbd);
	mlx_loop_hook(cbd->mlx, cbd_loop, cbd);
	return (SUCCESS);
}

bool	cbd_init(t_app *cbd)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	mlx_set_setting(MLX_MAXIMIZED, 1);
	cbd->mlx = mlx_init(WIDTH, HEIGHT, "Telestein 3D", true);
	if (!cbd->mlx)
		return (cbd_error(ERR_ALLOC), FAILURE);
	cbd->render.img = mlx_new_image(cbd->mlx, WIDTH, HEIGHT);
	cbd->render.sprite_img = mlx_new_image(cbd->mlx, WIDTH, HEIGHT);
	cbd->hud = cbd_init_hud(cbd->mlx);
	cbd->render.po_head = cbd_init_texture_img(cbd->mlx,
			"./data/textures/sprites/po_head.png");
	cbd->playerdata.inv = cbd_init_inventory(cbd->mlx);
	if (!cbd->playerdata.inv || !cbd->render.img
		|| !cbd->hud || !cbd->render.sprite_img || !cbd->render.po_head)
		return (cbd_error(ERR_ALLOC), FAILURE);
	return (cbd_init2(cbd));
}
