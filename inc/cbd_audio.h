#ifndef CBD_AUDIO_H
# define CBD_AUDIO_H

# include "miniaudio.h"
# include "cbd_render.h"
# include <stdbool.h>
# include <stdint.h>

typedef enum s_sounds {
	SND_WALK_SOLID,
	SND_WALK_GRASS,
	SND_MENU,
	SND_SEARCH,
	SND_MUSIC,
	SND_PUNCH,
	SND_TICK,
	SND_WALL1,
	SND_WALL2,
	SND_WALL3,
	SND_GUTS,
	SND_TAKE_DAMAGE,
	SND_NEAR_DEATH,
	SND_SAW,
	SND_SAW_IDLE,
	SND_TV_NOISE,
	SND_TV_BYE,
	SND_TV_JAZZ,
	SND_TV_RICKROLL,
	SND_TV_SURREAL,
	SND_AMBIENT_LAUGH,
	SND_IMPACT,
	SND_IMPACT2,
	SND_IMPACT3,
	SND_CROWS,
	SND_CHASE,
	SND_LAUGH,
	SND_NO_FUEL,
	SND_NO_FUEL2,
	SND_PICKUP,
	SND_GAME_OVER,
	SND_BUSH,
	SND_SIZE,
} t_sounds;

enum e_player_state;

typedef struct s_audio {
	ma_sound	*sound[SND_SIZE];
	ma_engine	*engine;
	bool		is_initialized;
	t_entity	*tv;
	t_entity	*trigger1;
	t_entity	*trigger2;
	t_entity	*enemy;
	bool		t1;
	bool		t2;
	bool		pickup;
	bool		damage;
	bool		is_dead;
	bool		chase;
	bool		checkpoint;
	uint8_t		channel;
}	t_audio;

//		cbd_audio.c
t_audio	*cbd_init_audio(void);
void	cbd_uninit_audio(t_audio *audio);
void	play_sound(const t_audio *audio, uint8_t type, float volume, float pitch);
void	loop_sound(const t_audio *audio, uint8_t type, bool alternate);
void	stop_sound(const t_audio *audio, uint8_t type);
void	reset_sounds(const t_audio *audio);

//		menu_audio.c
void	update_menu_audio(t_audio *audio, t_app *cbd);

//		game_audio.c
void	update_game_audio(t_audio *audio, t_inventory *inv, enum e_player_state state, mlx_t *mlx);

//		play_cues.c
void	play_walk_sound(t_audio *audio, float dt);
void	take_damage(t_audio *audio);
void 	play_jumpscare(t_audio *audio);
void 	play_pickup(t_audio *audio);
void	play_chase(t_audio *audio);

#endif
