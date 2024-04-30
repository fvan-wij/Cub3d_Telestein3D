#include <cub3d.h>

void	draw_player(mlx_image_t *img)
{
	const float	r = (TILESIZE) >> 5;

	draw_circle(img, color(100, 255, 100),
		vec2i_assign((float)(img->width >> 1),
			(float)(img->height >> 1)), r);
}

static void	draw_tile(mlx_image_t *hud_map, t_vec2d offset,
	char **map, t_vec2i it)
{
	t_vec2i		loc;
	t_vec2i		size;
	const float	tile_h = (float)(MINIMAP_HEIGHT >> 3);

	loc.x = (it.x * tile_h) + offset.x;
	loc.y = (it.y * tile_h) + offset.y;
	size.x = tile_h + 1;
	size.y = tile_h + 1;
	if (map[it.y][it.x] == '0' && loc.x < MINIMAP_WIDTH
		&& loc.y < MINIMAP_HEIGHT)
		draw_square(hud_map, color_rgba(0, 0, 0, 50), loc, size);
	else if ((map[it.y][it.x] == '=' || map[it.y][it.x] == '-'
		|| map[it.y][it.x] == '_') && loc.x < MINIMAP_WIDTH
		&& loc.y < MINIMAP_HEIGHT)
		draw_square(hud_map, color_rgba(5, 200, 45, 100), loc, size);
}

void	draw_minimap(mlx_image_t *hud_map, t_vec2d pos,
	char **map, t_vec2i size)
{
	const float	tile_h = (float)(MINIMAP_HEIGHT >> 3);
	uint16_t	y;
	uint16_t	x;
	t_vec2d		offset;

	draw_square(hud_map, color_rgba(200, 200, 200, 200), vec2i_assign(0, 0),
		vec2i_assign(hud_map->width, hud_map->height));
	offset.x = -(((pos.x / MINIMAP_WIDTH) * MINIMAP_WIDTH) * tile_h)
		+ (MINIMAP_WIDTH >> 1);
	offset.y = -(((pos.y / MINIMAP_HEIGHT) * MINIMAP_HEIGHT) * tile_h)
		+ (MINIMAP_HEIGHT >> 1);
	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			draw_tile(hud_map, offset, map, vec2i_assign(x, y));
			x++;
		}
		y++;
	}
	draw_player(hud_map);
}

void	draw_map(char **map, t_hud *hud, int width, int height)
{
	const t_vec2i	size = {TILESIZE, TILESIZE};
	t_vec2i			p;
	uint16_t		i;
	uint16_t		j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			p.x = (j * TILESIZE);
			p.y = (i * TILESIZE);
			if (p.x <= WIDTH && p.y <= HEIGHT)
			{
				if (map[i][j] == '1' || map[i][j] == '2')
					draw_square(hud->img[HUD_MAP], color(200, 200, 200),
						p, size);
				else
					draw_square(hud->img[HUD_MAP], OFF_WHITE, p, size);
			}
			j++;
		}
		i++;
	}
}
