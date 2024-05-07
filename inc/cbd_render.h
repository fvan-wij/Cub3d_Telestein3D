/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cbd_render.h                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/07 12:28:08 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/05/07 12:42:48 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CBD_RENDER_H
# define CBD_RENDER_H
# include <stdbool.h>
# include <stdint.h>
# include <cbd_vec.h>
# include <MLX42.h>

//Window size
# define WIDTH 					1280
# define HEIGHT 				720
# define FOV 					90

//Colors
# define WHITE 					0xFFFFFFFF
# define OFF_WHITE				0xF0F0F0FF
# define RED 					0xFF0000FF
# define GREEN 					0x00FF00FF
# define BLUE 					0x0000FFFF

//Dimensions
# define TILESIZE 				64
# define MINIMAP_WIDTH			184
# define MINIMAP_HEIGHT			160
# define N_PARTICLES			25
# define MAX_BLOOD_PARTICLES	25

//Animations
# define MAX_FRAMES				3

typedef struct s_map	t_map;
typedef struct s_player	t_player;
typedef struct s_entity	t_entity;
typedef struct s_app	t_app;

typedef struct s_rgba_step
{
	float	r;
	float	g;
	float	b;
	float	a;
}	t_rgba_step;

typedef struct s_wall_strip_data
{
	int		draw_start;
	int		draw_end;
	int		wl_height;
	double	wall_x;
	double	wall_y;
	int		y;
}	t_wall_strip_data;

typedef struct s_bresenham
{
	int			error[2];
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			cx;
	int			cy;
	int			y;
	int			x;
}	t_bresenham;

typedef struct s_line
{
	int			x1;
	int			y1;
	int			x2;
	int			y2;
}	t_line;

typedef union s_rgba
{
	int32_t	color;
	struct
	{
		uint8_t	a;
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	};
}	t_rgba;

typedef struct s_dda
{
	t_vec2d	side_dist;
	t_vec2d	delta_dist;
	t_vec2i	vec_map;
	t_vec2i	step;
	double	perp_wall_dist;
	bool	hit;
}	t_dda;

typedef struct s_ray
{
	t_vec2d	dir;
	t_vec2d	intersection;
	double	wall_dist;
	uint8_t	side;
	char	tile;
}	t_ray;

typedef struct s_particle
{
	t_vec2d	p;
	t_vec2d	dir;
	t_vec2d	size;
	t_vec2d	reset;
	t_vec2d	rp;
}	t_particle;

typedef struct s_animation_frame
{
	mlx_image_t		*img;
	uint8_t			duration;
}	t_animation_frame;

typedef struct s_animation
{
	t_animation_frame		frames[MAX_FRAMES];
	uint8_t					n_frames;
	size_t					current_frame;
	uint8_t					n_animations;
	size_t					current_animation;
	float					timer;
	float					duration;
	bool					loop;
	bool					enabled;
	float					reset_x;
	float					current_x;
}	t_animation;

typedef struct s_weapon
{
	t_animation	*use_anim;
	mlx_image_t	*img;
	uint8_t		type;
	bool		in_inventory;
	float		ammo;
}	t_weapon;

typedef enum e_inv_items
{
	WPN_FIST,
	WPN_CHAINSAW,
	WPN_MAP,
	WPN_SIZE,
}	t_inv_items;

typedef struct s_inventory
{
	t_weapon	wpn[WPN_SIZE];
	uint8_t		equipped;
}	t_inventory;

typedef enum e_hud_items
{
	HUD_MAP,
	HUD_OVERLAY,
	HUD_CRT,
	HUD_PULSE,
	HUD_SIZE,
}	t_hud_items;

//HUD data
typedef struct s_hud
{
	mlx_image_t	*img[HUD_SIZE];
}	t_hud;

typedef struct t_fx
{
	float	splat_timer;
	float	blood_timer;
	float	crt_timer;
	float	pulse_timer;
	bool	crt;
	bool	splat;
	bool	blood;
	bool	pulse;
}	t_fx;

typedef struct s_render
{
	mlx_image_t	*img;
	mlx_image_t	*sprite_img;
	mlx_image_t	*po_head;
	t_hud		*hud;
	t_inventory	*inv;
	t_ray		rays[WIDTH];
	t_particle	splat[MAX_BLOOD_PARTICLES];
	t_particle	blood[MAX_BLOOD_PARTICLES];
	t_fx		fx;
	float		headbob;
	float		map_peak;
	int			y_offset;
	float		timer;
	bool		b_timer;
	float		headache_timer;
	double		*zbuffer;
}	t_render;

typedef struct s_render_entity
{
	t_render	*render;
	t_entity	*entity;
	t_player	*player;
	double		ent_x;
	double		ent_y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			sprite_height;
	int			draw_start_y;
	int			draw_end_y;
	int			sprite_width;
	int			draw_start_x;
	int			draw_end_x;
	int			tex_width;
	int			tex_height;
}	t_render_entity;

typedef struct s_wall	t_wall;

typedef void			(*t_wall_strip_func)(t_render render,
							int x, t_wall *walls, float wall_dist);

typedef struct s_wall
{
	t_wall_strip_func	jump_table[256];
	char				*w_path[256];
	mlx_texture_t		*w_tex[256];
	uint8_t				n_w;
	uint8_t				n_cw;
}	t_wall;

//				Color
int32_t			color(uint8_t r, uint8_t g, uint8_t b);
t_rgba			color32(uint32_t color);
int32_t			color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
t_rgba			get_color_from_tex(mlx_texture_t *tex, uint32_t x, uint32_t y);
t_rgba			color_darken(t_rgba color, int amount);

//				Draw
void			draw_hud(t_hud *hud, t_inventory *inv);
void			draw_background(mlx_image_t *img, int32_t color, int peek);
void			draw_player(mlx_image_t *img);
void			draw_map(char **map, t_hud *hud, int width, int height);
void			draw_minimap(mlx_image_t *hud_map,
					t_vec2d pos, char **map, t_vec2i size);
void			draw_wall_strip(t_render render, int x,
					mlx_texture_t *tex, int color_offset);
void			draw_walls(t_render render, t_map *map);
void			draw_walls_bonus(t_render render, t_map *map);
void			draw_sprites(t_render *render, t_map *map, t_player *player);
void			render_entities(t_render *render,
					t_entity *entities, t_player *player);
void			draw_equipped_weapon(t_inventory *inv);
t_entity		*spawn_blood(t_entity *head, t_player *player, uint8_t limb);
void			draw_entity_strip(int strip, t_render_entity re);

//				Draw shapes
void			draw_line(mlx_image_t *image, uint32_t color,
					t_vec2i p1, t_vec2i p2);
void			draw_square(mlx_image_t *image, uint32_t color,
					t_vec2i pos, t_vec2i dimension);
void			draw_square_centered(mlx_image_t *image, uint32_t color,
					t_vec2i pos, t_vec2i dimension);
void			draw_noise_square(mlx_image_t *image, t_vec2i pos,
					t_vec2i dimension);
void			draw_circle(mlx_image_t *image, uint32_t color,
					t_vec2i pos, float r);
void			draw_dust_particles(mlx_image_t *game, t_particle *particles);

//				Post processing
void			draw_gradient_bg(mlx_image_t *img,
					t_rgba top, t_rgba bot, int32_t offset);
void			draw_gradient_top(mlx_image_t *img,
					t_rgba top, t_rgba bot, int32_t end);
void			draw_gradient_bot(mlx_image_t *img,
					t_rgba top, t_rgba bot, int32_t end);
mlx_texture_t	*dither_texture(mlx_texture_t *tex);
mlx_image_t		*dither_image(mlx_image_t *img);
void			draw_scanlines_bg(mlx_image_t *img);
void			screenshake(t_render *render);

//				Particles
void			init_blood_splat(t_particle *splat_particle);
void			init_blood_particles(t_particle *blood_particle);
void			move_particles(t_particle *particles, float x, float y);
void			rotate_particles(t_particle *particles, float dir);
void			resolve_particles(t_particle *particles, int8_t dir);
void			draw_blood_splat(mlx_image_t *img, t_particle *splat, t_fx *fx);
void			draw_blood_particles(mlx_image_t *img,
					t_particle *blood_particle, t_fx *fx);

//				Animation
void			play_weapon_animation(mlx_t	*mlx, t_inventory *inv);
t_vec2d			resolve_collision(char **map, t_vec2d pos,
					t_vec2d dir, t_vec2d potential_pos);
void			headbob(float *headbob, float speed);
void			reset_player_animation(t_render *render, mlx_t *mlx);
void			peek_map(t_inventory *inv, t_render *render,
					mlx_image_t *img, mlx_t *mlx);

//				render_utility.c
t_rgba			get_texture_pixel(mlx_texture_t *tex, double x, double y);

#endif //CBD_RENDER_H
