
#include "base.h"

typedef struct	s_pos
{
	int	x;
	int	y;
}				t_pos;

static t_pos	get_bot(char **split)
{
	int	y;
	int	x;

	y = -1;
	while (split[++y])
	{
		x = -1;
		while(split[y][++x])
		{
			if (split[y][x] == '@')
			{
				split[y][x] = '.';
				return (t_pos) {x, y};
			}
		}
	}
	return (t_pos) {0, 0};
}

static t_pos		get_direction(char move)
{
	t_pos	direction;

	direction.x = 0;
	direction.y = 0;

	if (move == '^')
		direction.y = -1;
	else if (move == '>')
		direction.x = 1;
	else if (move == 'v')
		direction.y = 1;
	else if (move == '<')
		direction.x = -1;

	return (direction);
}

void		show_map(char **split, t_pos *bot)
{
	for (int y = 0; split[y]; y++)
	{
		for (int x = 0; split[y][x]; x++)
		{
			if (bot->x == x && bot->y == y)
				printf("@");
			else
				printf("%c", split[y][x]);
		}
		printf("\n");
	}
	printf("\n");
}

static void		move_wall(t_pos pos, t_pos direction, char **split)
{
	t_pos	new_pos;

	new_pos = (t_pos) {pos.x + direction.x, pos.y + direction.y};


	if (direction.x != 0 && (split[new_pos.y][new_pos.x] == '[' || split[new_pos.y][new_pos.x] == ']'))
		move_wall(new_pos, direction, split);
	else if (direction.y != 0)
	{
		if (split[new_pos.y][new_pos.x] == '[')
		{
			move_wall(new_pos, direction, split);
			move_wall((t_pos) {new_pos.x + 1, new_pos.y}, direction, split);
		}
		else if (split[new_pos.y][new_pos.x] == ']')
		{
			move_wall(new_pos, direction, split);
			move_wall((t_pos) {new_pos.x - 1, new_pos.y}, direction, split);
		}
	}
	
	split[new_pos.y][new_pos.x] = split[pos.y][pos.x];
	split[pos.y][pos.x] = '.';
}

static int		can_move_wall(t_pos pos, t_pos direction, char **split)
{
	t_pos	new_pos;

	new_pos = (t_pos) {pos.x + direction.x, pos.y + direction.y};

	if (split[new_pos.y][new_pos.x] == '.')
		return (1);
	if (split[new_pos.y][new_pos.x] == '#')
		return (0);
	
	if (direction.y != 0)
	{
		if (split[new_pos.y][new_pos.x] == '[')
			return (can_move_wall(new_pos, direction, split) &&
					can_move_wall((t_pos) {new_pos.x + 1, new_pos.y}, direction, split));

		if (split[new_pos.y][new_pos.x] == ']')
			return (can_move_wall(new_pos, direction, split) &&
					can_move_wall((t_pos) {new_pos.x - 1, new_pos.y}, direction, split));
	}
	if (direction.x != 0)
	{
		new_pos = (t_pos) {new_pos.x + direction.x, new_pos.y + direction.y};
		return (can_move_wall(new_pos, direction, split));
	}

	return (1);
}

static void		move_bot(t_pos *bot, char **split, t_pos direction)
{
	t_pos	new_pos;

	new_pos = (t_pos) {bot->x + direction.x, bot->y + direction.y};

	if (split[new_pos.y][new_pos.x] == '.')
	{
		*bot = new_pos;
		return ;
	}
	if (split[new_pos.y][new_pos.x] == '#')
		return ;

	if (direction.y != 0)
	{
		if (split[new_pos.y][new_pos.x] == '[')
		{
			if (can_move_wall(new_pos, direction, split) && can_move_wall((t_pos) {new_pos.x + 1, new_pos.y}, direction, split))
			{
				move_wall(new_pos, direction, split);
				move_wall((t_pos) {new_pos.x + 1, new_pos.y}, direction, split);
				*bot = new_pos;
			}
		}
		else if (split[new_pos.y][new_pos.x] == ']')
		{
			if (can_move_wall(new_pos, direction, split) && can_move_wall((t_pos) {new_pos.x - 1, new_pos.y}, direction, split))
			{
				move_wall(new_pos, direction, split);
				move_wall((t_pos) {new_pos.x - 1, new_pos.y}, direction, split);
				*bot = new_pos;
			}
		}
	}
	else if (direction.x != 0)
	{
		if (can_move_wall(new_pos, direction, split))
		{
			move_wall(new_pos, direction, split);
			*bot = new_pos;
		}
	}

}

static void		execute_moves(t_pos *bot, char **split, char *move_line)
{
	int		x;
	t_pos	direction;
	
	x = -1;
	while (move_line[++x])
	{
		direction = get_direction(move_line[x]);

		move_bot(bot, split, direction);

		show_map(split, bot);
	}

}

static long int		calcul_result(char **split)
{
	int			y;
	int			x;
	long int	result;

	result = 0;
	y = -1;
	while (split[++y])
	{
		x = -1;
		while (split[y][++x])
		{
			if (split[y][x] == 'O')
				result += 100 * y + x;
		}
	}
	return (result);
}

char			**wide_map(char **split)
{
	int		y;
	int		x;
	int		k;
	char	**map;

	map = ft_calloc(sizeof(char *), ft_tab_len(split) + 1);
	
	y = -1;
	while (split[++y])
	{
		map[y] = ft_calloc(sizeof(char), ft_strlen(split[y]) * 2 + 1);
		
		x = -1;
		k = -1;
		while (split[y][++x])
		{
			if (split[y][x] == 'O')
			{
				map[y][++k] = '[';
				map[y][++k] = ']';
			}
			else if (split[y][x] == '@')
			{
				map[y][++k] = '@';
				map[y][++k] = '.';
			}
			else if (split[y][x] == '.' || split[y][x] == '#')
			{
				for (int j = 0; j < 2; j++)
					map[y][++k] = split[y][x];
			}
		}
	}
	return (map);
}

long int		resolve_part2(char *input, char **old_split)
{
	(void) input;
	t_pos	bot;
	int		result;
	char	**moves;

	char **split = wide_map(old_split);

	bot = get_bot(split);
	
	moves = old_split;
	while (**moves == '#')
		moves++;

	while (*moves)
	{
		execute_moves(&bot, split, *moves);
		moves++;
	}

	result = calcul_result(split);

	return (result);
}

