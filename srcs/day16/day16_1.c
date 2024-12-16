

#include "base.h"
#include <string.h>

typedef struct	s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef enum	s_dir
{
	EAST = 0,
	NORTH = 1,
	WEST = 2,
	SOUTH = 3,
	END = 4
}				t_dir;

typedef struct	s_bot
{
	t_pos		pos;
	t_pos		dir;
	t_dir		dir_val;
	long int	cost;
}				t_bot;

t_pos			get_dir(t_dir dir)
{
	dir %= 4;

	if (dir == EAST)
		return (t_pos) {1, 0};
	if (dir == NORTH)
		return (t_pos) {0, -1};
	if (dir == WEST)
		return (t_pos) {-1, 0};
	if (dir == SOUTH)
		return (t_pos) {0, 1};
	return ((t_pos) {0, 0});
}

static int		is_in_bound(char **split, int x, int y)
{
	return ((x >= 0 && x < (int)ft_strlen(split[0]) && (y >= 0 && y < (int)ft_tab_len(split))));
}

static void		set_next_dir(char **split, t_bot bot, t_dir *next_pos)
{
	int		k;
	t_pos	next_dir;
	char	current_char;

	k = -1;
	for (int j = 0; j < 4; j++)
	{
		next_dir = get_dir(bot.dir_val + j);

		if (!is_in_bound(split, bot.pos.x + next_dir.x, bot.pos.y + next_dir.y))
			continue ;

		current_char = split[bot.pos.y + next_dir.y][bot.pos.x + next_dir.x];
		if (current_char == '.' || current_char == 'E')
			next_pos[++k] = (bot.dir_val + j) % 4;
	}
}

int				get_new_cost(t_bot bot, t_dir new_dir)
{
	if (bot.dir_val == new_dir)
		return (1);
	
	if (new_dir > bot.dir_val)
	{
		if (new_dir - bot.dir_val == 2)
			return (2001);
	}
	if (bot.dir_val > new_dir)
	{
		if (bot.dir_val - new_dir == 2)
			return (2001);
	}
	return (1001);
}

long int		backtrack(char **split, long int **hash, t_bot bot, t_pos end)
{
	t_dir	dirs[5];
	int		cost;
	int		min_cost;
	int		current_cost;
	t_dir	current_dir;

	if (bot.pos.x == end.x && bot.pos.y == end.y)
		return (bot.cost);

	split[bot.pos.y][bot.pos.x] = '#';

	min_cost = -1;

	memset(dirs, END, sizeof(dirs));
	set_next_dir(split, bot, dirs);

	if ((dirs[0] < 0 || dirs[0] >= 4))
	{
		split[bot.pos.y][bot.pos.x] = '.';
		return (-1);
	}
	for (int j = 0; (dirs[j] >= 0 && dirs[j] < 4) && j < 4; j++)
	{
		if (dirs[j] < 0 || dirs[j] >= 4)
			break ;

		current_cost = get_new_cost(bot, dirs[j]);
		bot.dir = get_dir(dirs[j]);
		current_dir = bot.dir_val;

		bot.pos.x += bot.dir.x;
		bot.pos.y += bot.dir.y;
		bot.dir_val = dirs[j];
		bot.cost += current_cost;

		cost = backtrack(split, hash, bot, end);

		bot.dir_val = current_dir;
		bot.cost -= current_cost;
		bot.pos.x -= bot.dir.x;
		bot.pos.y -= bot.dir.y;

		if (cost != -1 && (cost < min_cost || min_cost == -1))
			min_cost = cost;
	}

	split[bot.pos.y][bot.pos.x] = '.';

	if (min_cost == -1)
		return (-1);

	(void) end;
	return (min_cost);
}

void			show_map(char **split, t_pos start, t_pos end)
{
	for (int y = 0; y < (int) ft_tab_len(split); y++)
	{
		for (int x = 0; x < (int) ft_strlen(split[y]); x++)
		{
			if (x == start.x && y == start.y)
				printf("S");
			else if (x == end.x && y == end.y)
				printf("E");
			else
				printf("%c", split[y][x]);
		}
		printf("\n");
	}
	printf("\n");
}

long int		resolve_part1(char *input, char **split)
{
	(void)	split;
	(void)	input;
	
	long int	**map;
	int			result;
	
	t_bot	bot;
	t_pos	end = (t_pos) {ft_strlen(split[0]) - 2, 1};

	ft_memset(&bot, 0, sizeof(t_bot));

	bot.pos = (t_pos) {1, ft_tab_len(split) - 2};

	split[bot.pos.y][bot.pos.x] = '.';
	split[end.y][end.x] = '.';

	map = ft_calloc(sizeof(long int *), ft_tab_len(split) + 1);
	for (int i = 0; split[i]; i++)
		map[i] = ft_calloc(sizeof(long int), ft_strlen(split[i]) + 1);

	show_map(split, bot.pos, end);

	result = backtrack(split, map, bot, end);

	return (result);
}
