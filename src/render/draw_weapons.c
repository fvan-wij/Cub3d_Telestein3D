#include <cub3d.h>

void	draw_hud(t_hud *hud, t_inventory *inv)
{
	if (inv->equipped == WPN_MAP)
		hud->img[HUD_MAP]->enabled = true;
	else
		hud->img[HUD_MAP]->enabled = false;
}

void	draw_equipped_weapon(t_inventory *inv)
{
	if (inv->equipped == WPN_FIST
		&& inv->wpn[WPN_FIST].use_anim->loop != true)
		inv->wpn[WPN_FIST].img->enabled = true;
	else
		inv->wpn[WPN_FIST].img->enabled = false;
	if (inv->equipped == WPN_CHAINSAW
		&& inv->wpn[WPN_CHAINSAW].use_anim->loop != true)
		inv->wpn[WPN_CHAINSAW].img->enabled = true;
	else
		inv->wpn[WPN_CHAINSAW].img->enabled = false;
	if (inv->equipped == WPN_MAP
		&& inv->wpn[WPN_CHAINSAW].use_anim->loop != true)
		inv->wpn[WPN_MAP].img->enabled = true;
	else
		inv->wpn[WPN_MAP].img->enabled = false;
}
