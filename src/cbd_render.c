#include <cub3d.h>
#include <math.h>
#include <stdlib.h>

/*
** Renders the game
	Needs:
	The image to render on
	The raycasting data
	The headbobbing data
	The map peak data
	The minimap data
	The HUD data
	The equipped weapon data
	The particles data

	Raycasting needs:
		The map
		The player position
		The player direction
		The player plane
	Each raycast itself needs:
		The Map
		A position
		A direction
		and returns: The raycast data
*/
void	cbd_render(t_app *cbd)
{
<<<<<<< HEAD
	draw_gradient_top(cbd->render.img, (t_rgba)cbd->mapdata->ceiling.color, (t_rgba)color(0,0,0), cbd->render.y_offset);
	draw_gradient_bot(cbd->render.img, (t_rgba)color(0,0,0), (t_rgba)cbd->mapdata->floor.color, cbd->render.y_offset);
	cast_rays(cbd->mapdata->cbd_map, &cbd->render, &cbd->playerdata);
	draw_walls(cbd->render, cbd->mapdata);
	render_entities(&cbd->render, cbd->mapdata->entities, &cbd->playerdata);
	draw_minimap(cbd->hud->img[HUD_MAP], cbd->playerdata.pos, cbd->mapdata->cbd_map, vec2i_assign(cbd->mapdata->width, cbd->mapdata->height));
=======
	draw_gradient_top(cbd->render.img, cbd->mapdata->ceiling.color,
		color(0, 0, 0), cbd->render.y_offset);
	draw_gradient_bot(cbd->render.img, color(0, 0, 0),
		cbd->mapdata->floor.color, cbd->render.y_offset);
	cast_rays(cbd->mapdata->cbd_map, &cbd->render, &cbd->playerdata);
	draw_walls(cbd->render, cbd->mapdata);
	render_entities(&cbd->render, cbd->mapdata->entities, &cbd->playerdata);
	draw_minimap(cbd->hud->img[HUD_MAP], cbd->playerdata.pos,
		cbd->mapdata->cbd_map, cbd->mapdata->width, cbd->mapdata->height);
>>>>>>> cub3d_eval
	draw_hud(cbd->hud, cbd->playerdata.inv);
	draw_equipped_weapon(cbd->playerdata.inv);
	draw_dust_particles(cbd->render.img, cbd->particles);
	cbd->render.img = dither_image(cbd->render.img);
	draw_blood_splat(cbd->render.hud->img[HUD_OVERLAY],
		cbd->render.splat, &cbd->render.fx);
	draw_blood_particles(cbd->render.sprite_img,
		cbd->render.blood, &cbd->render.fx);
	if (cbd->state == STATE_BEHEAD)
	{
		draw_square(cbd->hud->img[HUD_OVERLAY], color(0, 0, 0),
			vec2i(0, 0), vec2i(WIDTH, HEIGHT >> 3));
		draw_square(cbd->hud->img[HUD_OVERLAY], color(0, 0, 0),
			vec2i(0, HEIGHT - (HEIGHT >> 3)), vec2i(WIDTH, HEIGHT >> 3));
	}
	screenshake(&cbd->render);
}
