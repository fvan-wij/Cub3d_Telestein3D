#include "cbd_audio.h"
#include <cub3d.h>

static void	pick_up_chainsaw(t_entity *item, t_app *cbd)
{
	t_audio	*audio;

	audio = cbd->audio;
	if (vec_distance(item->pos, cbd->playerdata.pos) < 0.5
		&& !cbd->playerdata.inv->wpns[WPN_CHAINSAW].in_inventory)
	{
		cbd->playerdata.inv->wpns[WPN_CHAINSAW].in_inventory = true;
		cbd->playerdata.inv->equipped = WPN_CHAINSAW;
		item->enabled = false;
		audio->pickup = true;
	}
}

static void	pick_up_fuel(t_entity *item, t_app *cbd)
{
	t_audio	*audio;

	audio = cbd->audio;
	if (vec_distance(item->pos, cbd->playerdata.pos) < 0.5)
	{
		cbd->playerdata.inv->wpns[WPN_CHAINSAW].ammo += 25;
		item->enabled = false;
		audio->pickup = true;
	}
}

static void	pick_up_map(t_entity *item, t_app *cbd)
{
	t_audio	*audio;

	audio = cbd->audio;
	if (vec_distance(item->pos, cbd->playerdata.pos) < 0.5
		&& !cbd->playerdata.inv->wpns[WPN_MAP].in_inventory)
	{
		cbd->playerdata.inv->wpns[WPN_CHAINSAW].use_anim->loop = false;
		cbd->playerdata.inv->wpns[WPN_MAP].in_inventory = true;
		item->enabled = false;
		audio->pickup = true;
	}
}

void	update_item(t_entity *item, t_app *cbd)
{
	if (ft_strncmp(item->name, "chainsaw", 9) == 0 && item->enabled)
		pick_up_chainsaw(item, cbd);
	if (ft_strncmp(item->name, "fuel", 4) == 0 && item->enabled)
		pick_up_fuel(item, cbd);
	if (ft_strncmp(item->name, "po", 2) == 0 && item->enabled && item->dead)
		pick_up_map(item, cbd);
}
