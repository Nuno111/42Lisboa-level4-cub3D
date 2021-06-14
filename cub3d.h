/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:32:51 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/20 11:22:52 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <float.h>
# include "libft.h"
# include <stdint.h>

# define W 13
# define D 2
# define S 1
# define A 0
# define UP 1
# define RIGHT 2
# define DOWN 3
# define LEFT 4
# define ESC 53
# define ARR_LEFT 123
# define ARR_RIGHT 124

typedef uint16_t	t_word;
typedef int32_t		t_long;
typedef uint32_t	t_dword;

typedef struct s_file_header
{
	char	bf_type[2];
	t_dword	bf_size;
	t_word	bf_reserved1;
	t_word	bf_reserved2;
	t_dword	bf_offbits;
}				t_file_header;

typedef struct s_info_header
{
	t_dword	bi_size;
	t_long	bi_width;
	t_long	bi_height;
	t_word	bi_planes;
	t_word	bi_bitcount;
	t_dword	bi_compression;
	t_dword	bi_sizeimage;
	t_long	bi_xpelspermeter;
	t_long	bi_ypelspermeter;
	t_dword	bi_clrused;
	t_dword	bi_clrimportant;
}				t_info_header;

typedef struct s_img
{
	void		*img;
	int			*addr;
	int			bpp;
	int			line_length;
	int			end;
	int			width;
	int			height;
}				t_img;

typedef struct s_wall
{
	t_img			tex;
	int				x;
	int				y;
	double			height;
	unsigned int	color;
}			t_wall;

typedef struct s_txts
{
	t_img	no;
	t_img	ea;
	t_img	so;
	t_img	we;
	t_img	spr;
}				t_txts;

typedef struct s_color
{
	int	t;
	int	r;
	int	g;
	int	b;
	int	trgb;
}				t_color;

typedef struct s_scene
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*sprite;
	char	*line;
	t_color	*floor;
	t_color	*ceil;
	t_list	*tmp_map;
	char	**map;
	size_t	map_width;
	size_t	map_size;
	int		w;
	int		h;
}					t_scene;

typedef struct s_circle
{
	double	x;
	double	y;
	double	ang;
	double	radius;
	int		color;
}				t_circle;

typedef struct s_square
{
	double	x;
	double	y;
	double	size;
	int		color;
}				t_square;

typedef struct s_line
{
	double	x;
	double	y;
	double	dir;
	double	size;
	int		color;
}				t_line;

typedef struct s_ray
{
	t_line	line;
	bool	w_hrzt_hit;
	bool	w_vrtc_hit;
	double	w_hrzt_x;
	double	w_hrzt_y;
	double	w_vrtc_x;
	double	w_vrtc_y;
	double	w_txt_pixel;
	bool	s_hrzt_hit;
	bool	s_vrtc_hit;
	double	s_hrzt_x;
	double	s_hrzt_y;
	double	s_vrtc_x;
	double	s_vrtc_y;
	double	s_txt_pixel;
	bool	facing_up;
	bool	facing_right;
}				t_ray;

typedef struct s_player
{
	t_circle	circle;
	double		rot_ang;
	double		move_speed;
	double		rot_speed;
	double		fov_ang;
	int			turn_dir;
	int			walk_dir;
	t_ray		**rays;
	int			num_rays;
	double		dtpp;
	double		ang_inc;
}				t_player;

typedef struct s_intercect
{
	double	x;
	double	y;
	double	x_step;
	double	y_step;
	int		x_offset;
	int		y_offset;
}				t_intercect;

typedef struct s_sprite
{
	double	x;
	double	y;
	t_img	txt;
	double	dist;
	double	ang;
	double	h;
	int		x_strt;
	int		y_strt;
	bool	visible;
}			t_sprite;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_player		player;
	t_square		mmt;
	t_scene			stg;
	t_img			img;
	t_txts			txts;
	t_sprite		**sprs;
	int				sprs_num;
	int				cube_size;
	bool			screenshot;
	t_file_header	bpm_header;
	t_info_header	bpm_info_header;
}				t_game;

/*
Colours
*/
int			create_trgb(int t, int r, int g, int b);
int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);

/*
validate_stg
*/
void		error_and_exit_stg(t_scene *stg, char *err_msg);
void		init_stg(t_scene *stg);
void		free_stg(t_scene *stg);
void		validate_map(t_scene *stg);
char		**linked_to_array(t_scene *stg, t_list *head);
void		verify_position(t_scene *stg);
bool		verify_str(char *str, bool whole);
char		*replace_tabs(char *str);
bool		validate_name(char *file);
void		validate_floor_ceil(t_scene *stg,
				t_color **floor_or_ceil, char **strs);
void		validate_r(t_scene *stg, char **strs);
void		validate_textures(t_scene *stg, char **path, char **strs);
void		parse_stg(t_scene *stg, char *file);
void		create_fake_map(t_scene *stg);
void		verify_walls(t_scene *stg, char **m);
bool		validate_string(char *str);
bool		plus_found(int i, int j, char **m);
bool		char_not_valid(int i, int j, char **m);

/*
Drawing
*/
void		draw_inner_circle(t_img *img, t_circle circle, int res_width);
void		draw_line(t_img *img, t_line line, int res_width);
void		draw_circle(t_img *img, t_circle circle, int res_width);
void		draw_square(t_img *img, t_square square, int res_width);

/*
MLX Events
*/
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
int			handle_click(int btn, int x, int y, t_game *game);

/*
Draw game functions
*/
void		draw_minimap(t_scene *stg, t_game *game);
void		draw_rays(t_game *game);
void		draw_walls(t_game *game);
void		draw_floor_ceil(t_game *game, t_color color, bool floor);

/*
Game functions
*/
void		render_game(t_game *game);
bool		is_wall(double x, double y, t_game *game);
bool		is_sprite(double x, double y, t_game *game);
void		create_rays(t_game *game);
double		get_dist(double x, double y, double hit_x, double hit_y);
double		normalize_angle(double ray_ang);
void		get_horizontal_intercection(t_game *game, t_ray *ray);
void		get_vertical_intercection(t_game *game, t_ray *ray);
double		get_wall_height(t_game *game, t_ray *ray);
void		update_player(t_game *game);
void		update_rays(t_game *game);
t_img		assign_wall_texture(t_game *game, t_ray ray);
void		reset_rays(t_game *game);
void		exit_game(t_game *game, char *err_msg);
int			handle_destroy(t_game *game);
void		init_stuff(t_game *game);
void		get_player_pos(t_game *game);
void		calc_wall_dist(t_game *game, t_ray *ray);
void		init_wall_vars(t_ray *ray);
void		init_sprites(t_game *game);
void		init_sprite(t_game *game, int x, int y);
t_sprite	**realloc_sprs(t_game *game, t_sprite **arr, t_sprite *new);
void		draw_sprites(t_game *game);
double		get_spr_distance(t_game *game, double spr_x, double spr_y);
double		get_spr_angle(t_game *game, double spr_x, double spr_y);
bool		is_spr_visible(t_game *game, double ang);
void		update_sprs(t_game *game);
void		save_and_exit(t_game *game);
void		get_spr_pos(t_game *game, int i);
void		validate_floor_ceil2(t_scene *stg,
				t_color **floor_or_ceil, char **tmp_strs);
double		deg_to_rad(int deg);

#endif
