

#include "base.h"

typedef struct	s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef struct	s_plot
{
	int	area;
	int	perimeter;
}				t_plot;

static int		is_in_bound(char **split, int x, int y)
{
	return ((x >= 0 && x < (int)ft_strlen(split[0]) && (y >= 0 && y < (int)ft_tab_len(split))));
}

char	**char_tab_dup(char **tab)
{
	char	**new_tab;
	int		k;

	k = -1;
	new_tab = ft_calloc(sizeof(char *), ft_tab_len(tab) + 1);
	while (tab[++k])
		new_tab[k] = ft_strdup(tab[k]);
	return (new_tab);
}

static void		set_next_pos(char **split, int x, int y, t_pos *next_pos)
{
	int		i;
	char	current;

	current = split[y][x];

	i = -1;
	if (is_in_bound(split, x, y - 1) && split[y - 1][x] == current)
		next_pos[++i] = (t_pos) {x, y - 1};
	if (is_in_bound(split, x + 1, y) && split[y][x + 1] == current)
		next_pos[++i] = (t_pos) {x + 1, y};
	if (is_in_bound(split, x, y + 1) && split[y + 1][x] == current)
		next_pos[++i] = (t_pos) {x, y + 1};
	if (is_in_bound(split, x - 1, y) && split[y][x - 1] == current)
		next_pos[++i] = (t_pos) {x - 1, y};
}

static int		get_perim(char **split, int x, int y)
{
	int		perim;
	t_pos	next_pos[4];

	ft_memset(next_pos, -1, sizeof(next_pos));
	set_next_pos(split, x, y, next_pos);

	perim = 0;
	while (next_pos[perim].x != -1 && next_pos[perim].y != -1 && perim != 4)
		perim++;
	perim = 4 - perim;
	return (perim);
}

static t_plot	backtrack(char **split, int x, int y, char **already)
{
	t_pos	next_pos[4];
	t_plot	tmp_plot;
	t_plot	result_plot;

	result_plot.area = 1;
	result_plot.perimeter = get_perim(split, x, y);

	ft_memset(next_pos, -1, sizeof(next_pos));
	set_next_pos(already, x, y, next_pos);

	already[y][x] = '.';

	if (next_pos[0].x == -1 && next_pos[0].y == -1)
		return (result_plot); //3 perimeter because coming from 1 direction and now having none

	for (int i = 0; i < 4; i++)
	{
		if (next_pos[i].x == -1 && next_pos[i].y == -1)
			break ;

		if (already[next_pos[i].y][next_pos[i].x] == '.')
			continue ;

		tmp_plot = backtrack(split, next_pos[i].x, next_pos[i].y, already);

		result_plot.area += tmp_plot.area;
		result_plot.perimeter += tmp_plot.perimeter;
	}
	return (result_plot);
}

long int		resolve_part1(char *input, char **split)
{
	(void)	input;
	char	**already;
	int		x;
	int		y;
	t_plot	plot;
	int		result;

	ft_memset(&plot, 0, sizeof(plot));
	already = char_tab_dup(split);

	result = 0;

	y = -1;
	while (split[++y])
	{
		x = -1;
		while (split[y][++x])
		{
			char tmp = already[y][x];

			if (already[y][x] == '.')
				continue ;

			plot = backtrack(split, x, y, already);

			result += plot.area * plot.perimeter;
		}
	}
	

	return (result);
}
