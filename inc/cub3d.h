#ifndef CUB3D_H
# define CUB3D_H

# define ERROR_MESSAGE "ERROR\n"

# define HEIGHT 1000
# define WIDTH 	1000

# define DEGREE 0.0174532925 

# define STEP 	5

# define M_PI 	3.14159265359

# define FOV 	60

// MAP
# define MAP_S_W 64
# define MAP_S_H 64
# define COLLISION_RADIUS 20

// TEXTURE SIDES
# define TEX_N 0
# define TEX_E 1
# define TEX_S 2
# define TEX_W 3

// COLORCODES
# define RED 		0xFF0000
# define YELLOW 	0xFFFF00
# define PINK   	0xFF6BAA
# define ORANGE 	0xFFA559
# define BLUE		0x001F3F
# define GREEN		0x00FF00
# define CYAN		0x00FFFF
# define MAGENTA	0xFF00FF
# define WHITE		0xFFFFFF
# define BLACK		0x000000
# define GRAY		0x808080
# define DARK_GRAY	0x404040
# define LIGHT_GRAY	0xC0C0C0
# define PURPLE		0x800080
# define DARK_RED	0x800000
# define DARK_GREEN	0x008000
# define DARK_BLUE	0x000080
# define BROWN		0x8B4513
# define GOLD		0xFFD700
# define LIME		0x00FF00
# define NAVY		0x000080
# define TEAL		0x008080
# define SILVER		0xC0C0C0
# define MAROON		0x800000

// KEYCODES
# define UP			65362
# define W			119
# define DOWN		65364
# define S			115
# define RIGHT		65363
# define D			100
# define LEFT		65361
# define A			97
# define MINUS		65453
# define PLUS		65451
# define ESC		65307
# define ZOOM_IN	5
# define ZOOM_OUT	4
# define ONE		49
# define TWO		50
# define THREE		51
# define RESET		114
# define SHIFT		65505
# define M			109
# define I			105

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_image;

typedef struct s_dpoint
{
	double		x;
	double		y;
}				t_dpoint;

typedef struct s_rect
{
	int			x;
	int			y;
	int			w;
	int			h;
}				t_rect;

typedef struct s_minimap
{
	int			w;
	int			h;
	int			x;
	int			y;
	int			tw; // tile width
	int			th; // tile height
	double		sx; // scale x
	double		sy; // scale y
}				t_minimap;

typedef struct s_player
{
	t_dpoint	*p; // player position
	t_dpoint	*p_dir; // player direction
	int			size;
	int			color;
	double		angle;
}				t_player;

typedef struct s_ray
{
	t_dpoint	*r; // ray point
	t_dpoint	*r0; // ray starting point
	t_dpoint	*offset; // ray offset (64)
	t_dpoint	*inc; // size increment
	double		r_angle;
	int			dof;
	int			steps;
	int			side;
	int			hit_vertical;
}				t_ray;

typedef struct s_wall_draw
{
	t_image		*tex;
	int			x;
	int			wall_top;
	int			wall_bottom;
	int			tex_x;
	double		step;
}				t_wall_draw;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_image		*img;
	t_player	*player;
	t_ray		*ray[WIDTH];
	t_image		wall_tex[4];
	char		**map;
	int			map_rows;
	int			map_cols;
	char		*tex_paths[4];
	int			floor_color;
	int			ceiling_color;
	char		player_start_dir;
	int			player_start_col;
	int			player_start_row;
	bool			key_w;
	bool			key_a;
	bool			key_s;
	bool			key_d;
	bool			key_left;
	bool			key_right;
	int			minimap_visible;
	int			instructions_visible;
}				t_game;

// ── CORE ─────────────────────────────────────────────
// core/main.c
int			main(int argc, char **argv);
void		re_render(t_game *cub);
// core/mlx_init.c
void		my_mlx_pixel_put(t_image *img, int x, int y, int color);
void		init_connection(t_game *cub);
void		init_window(t_game *cub);
void		init_image(t_game *cub);
void		init_mlx(t_game *cub);
// core/mlx_hooks.c
void		init_events(t_game *cub);
int			key_press(int keycode, t_game *cub);
int			close_handler(t_game *cub);
void		free_parsing_data(t_game *cub);

// ── MINIMAP ──────────────────────────────────────────
// minimap/mini_map.c
void		draw_2dmap(t_game *cub);
// minimap/mini_map_rays.c
void		draw_minimap_rays(t_game *cub, t_minimap *mm);
// minimap/mini_map_utils.c
void		draw_minimap_player(t_game *cub, t_minimap *mm);
int			is_wall(t_game *cub, int pixel_x, int pixel_y, int offset);

// ── PARSING ──────────────────────────────────────────
// parsing/parse_main.c
void		init_parsing_data(t_game *cub);
int			parse_cub_file(t_game *cub, char *filename);
// parsing/parse_colors.c
int			parse_color_line(char *line, char type, t_game *cub);
// parsing/parse_header.c
int			parse_header(t_game *cub, int fd);
// parsing/checking_map.c
int			validate_map(t_game *cub);
// parsing/map_loading.c
int			load_map(t_game *cub, char *filename);
int			count_map_dimensions(t_game *cub, int fd);
// parsing/parsing_utils.c
void		parsing_error(char *msg);
void		free_str_arr(char **arr);
char		*ft_strtrim_nl(char *str);
char		*pad_line(char *line, int width);

// ── PLAYER ───────────────────────────────────────────
// player/player.c
void		init_player(t_game *cub);
void		draw_player(t_game *cub);
// player/player_movement.c
void		player_movement(int keycode, t_game *cub);
void		player_direction(int keycode, t_game *cub);

// ── RAYCASTING ───────────────────────────────────────
// raycasting/rays.c
void		cast_rays(t_game *cub);
// raycasting/rays_init.c
void		init_rays(t_game *cub);
// raycasting/rays_utils.c
void		step_ray(t_game *cub, int r);
double		calculate_ray_angle(t_game *cub, int r);
// raycasting/rays_collision.c
t_dpoint	*check_horizontal_line(t_game *cub, int r);
t_dpoint	*check_vertical_line(t_game *cub, int r);
// raycasting/lines.c
void		draw_line(t_game *cub, int color, int r);
// raycasting/math.c
double		deg_to_rad(double degrees);
int			calculate_steps(double dx, double dy);
double		distance(t_dpoint *a, t_dpoint *b);
// ── RENDERING ────────────────────────────────────────
// rendering/render_3d.c
void		render_3d(t_game *cub);
// rendering/textures.c
int			load_textures(t_game *cub);
int			get_texture_color(t_image *tex, int x, int y);
// rendering/texture_utils.c
int			get_tex_x(t_game *cub, int r, t_image *tex);
int			clamp_tex_y(t_image *tex, double tex_pos);
int			get_start_y(int wall_top);
int			get_end_y(int wall_bottom);

// ── UI ───────────────────────────────────────────────
// ui/game_instructions.c
void		draw_instructions(t_game *cub);

#endif