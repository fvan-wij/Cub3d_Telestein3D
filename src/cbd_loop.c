/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cbd_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 12:13:09 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/05/07 14:03:36 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <cbd_audio.h>

static void	loop_behead(t_app *cbd, t_audio *audio)
{
	behead(cbd);
	cbd->elapsed_time += cbd->mlx->delta_time;
	cbd->render.img->instances->enabled = true;
	cbd->render.sprite_img->instances->enabled = true;
	update_player(&cbd->playerdata, cbd);
	update_entities(cbd);
	update_timers(&cbd->render.fx, cbd->mlx->delta_time);
	play_weapon_animation(cbd->mlx, cbd->playerdata.inv);
	update_game_audio(audio, cbd->playerdata.inv,
		cbd->playerdata.state, cbd->mlx);
	cbd_render(cbd);
}

static void	loop_game(t_app *cbd, t_audio *audio)
{
	cbd->elapsed_time += cbd->mlx->delta_time;
	cbd->render.img->instances->enabled = true;
	cbd->render.sprite_img->instances->enabled = true;
	cbd->render.y_offset = 0;
	mouse_input(cbd);
	update_player(&cbd->playerdata, cbd);
	escape_player(cbd->playerdata.pos, cbd->playerdata.dir, cbd);
	move_player(cbd, cbd->mlx->delta_time * 1.5f);
	update_entities(cbd);
	move_entities(cbd->mapdata->entities, cbd);
	deal_damage(cbd);
	update_timers(&cbd->render.fx, cbd->mlx->delta_time);
	play_weapon_animation(cbd->mlx, cbd->playerdata.inv);
	update_game_audio(audio, cbd->playerdata.inv,
		cbd->playerdata.state, cbd->mlx);
	cbd_render(cbd);
}

void	cbd_loop(void *param)
{
	t_app	*cbd;
	t_audio	*audio;

	cbd = param;
	audio = cbd->audio;
	if (cbd->menudata->state == OFF)
	{
		if (cbd->state == STATE_BEHEAD)
			loop_behead(cbd, audio);
		else
			loop_game(cbd, audio);
	}
	else if (cbd->menudata->state == MAP_SELECT)
		display_preview(cbd->menudata, cbd->mapdata);
	else if (cbd->menudata->state == MAP_LOAD)
		change_map(cbd);
	else if (cbd->menudata->state == GAME_EXIT)
		mlx_close_window(cbd->mlx);
	update_menu_audio(audio, cbd);
}
