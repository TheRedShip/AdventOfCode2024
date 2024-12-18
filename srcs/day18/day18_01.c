#include "base.h"

#define MEM_SIZE 70 + 1
#define MEM_ALTER 1024

typedef struct	s_pos
{
	int	x;
	int	y;
}				t_pos;

char            **parse_map(char **split, char **map, int len)
{
	int l = -1;

	for (int i = 0; i < MEM_SIZE; i++)
		ft_memset(map[i], '.', MEM_SIZE);

	if (len > ft_tab_len(split))
		len = ft_tab_len(split);

	while (++l < len)
	{
		int x = ft_atoi(split[l]);
		int y = ft_atoi(split[l] + 2 + ft_isdigit(*(split[l] + 1)));

		map[y][x] = '#';
	}

	return (map);
}

static void     show_map(char **map)
{
	for (int y = 0; map[y]; y++)
    {
        for (int x = 0; map[x]; x++)
        {
            printf("%c", map[y][x]);
        }
        printf("\n");
    }
}

static void		show_hash(int **hash)
{
	for (int y = 0; hash[y]; y++)
    {
        for (int x = 0; hash[x]; x++)
        {
			if (hash[y][x] == 0)
				printf("  #  ");
			else
		    printf(" %03d ", hash[y][x]);
        }
        printf("\n");
    }
}

static int		is_in_bound(char **split, int x, int y)
{
	return ((x >= 0 && x < (int)ft_strlen(split[0]) && (y >= 0 && y < (int)ft_tab_len(split))));
}

static void		set_next_pos(char **split, int x, int y, t_pos *next_pos)
{
	int		i;

	i = -1;
	if (is_in_bound(split, x, y - 1) && split[y - 1][x] == '.')
		next_pos[++i] = (t_pos) {x, y - 1};
	if (is_in_bound(split, x + 1, y) && split[y][x + 1] == '.')
		next_pos[++i] = (t_pos) {x + 1, y};
	if (is_in_bound(split, x, y + 1) && split[y + 1][x] == '.')
		next_pos[++i] = (t_pos) {x, y + 1};
	if (is_in_bound(split, x - 1, y) && split[y][x - 1] == '.')
		next_pos[++i] = (t_pos) {x - 1, y};
}

static int		step_cost(char **map, int **hash, t_pos pos)
{
	t_pos	next_pos[4];
	int		min_cost = -1;

	if (pos.x == MEM_SIZE - 1 && pos.y == MEM_SIZE - 1)
		return (0);

	map[pos.y][pos.x] = '#';

	ft_memset(next_pos, -1, sizeof(next_pos));
	set_next_pos(map, pos.x, pos.y, next_pos);

	if (next_pos[0].x == -1 && next_pos[0].y == -1)
	{
		map[pos.y][pos.x] = '.';
		return (-1);
	}

	for (int j = 0; next_pos[j].x != -1 && next_pos[j].y != -1; j++)
	{
		int	cost;

		if (hash[next_pos[j].y][next_pos[j].x] != 0)
			cost = hash[next_pos[j].y][next_pos[j].x];
		else
		{
			cost = step_cost(map, hash, next_pos[j]);
			hash[next_pos[j].y][next_pos[j].x] = cost;
		}

		if ((cost != -1 && cost <= min_cost) || (min_cost == -1))
			min_cost = cost;
	}

	map[pos.y][pos.x] = '.';

	if (min_cost == -1)
		return (-1);

	return (min_cost + 1);
}

long int		resolve_part1(char *input, char **split)
{
	(void) 		input;
	(void) 		split;
	long int	result;

	char		**map;
	int			**hash;

	map = ft_calloc(sizeof(char *), MEM_SIZE + 1);
	for (int i = 0; i < MEM_SIZE; i++)
		map[i] = ft_calloc(sizeof(char), MEM_SIZE + 1);

	hash = ft_calloc(sizeof(int *), MEM_SIZE + 1);
	for (int i = 0; i < MEM_SIZE; i++)
		hash[i] = ft_calloc(sizeof(int), MEM_SIZE + 1);

	parse_map(split, map, MEM_ALTER);

	show_map(map);

	result = step_cost(map, hash, (t_pos) {0, 0});
	
	show_hash(hash);

	return (result);
}