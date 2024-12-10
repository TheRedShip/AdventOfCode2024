


#include "base.h"

typedef struct	s_pos
{
	int	x;
	int	y;
}				t_pos;

static int		is_in_bound(char **split, int x, int y)
{
	return ((x >= 0 && x < (int)ft_strlen(split[0]) && (y >= 0 && y < (int)ft_tab_len(split))));
}

static t_pos	*get_next_pos(char **split, int x, int y)
{
	int		i;
	char	current;
	t_pos	*next_pos;

	next_pos = malloc(sizeof(t_pos) * 4);
	ft_memset(next_pos, -1, sizeof(t_pos) * 4);

	current = split[y][x];

	i = -1;
	if (is_in_bound(split, x, y - 1) && split[y - 1][x] == current + 1)
		next_pos[++i] = (t_pos) {x, y - 1};
	if (is_in_bound(split, x + 1, y) && split[y][x + 1] == current + 1)
		next_pos[++i] = (t_pos) {x + 1, y};
	if (is_in_bound(split, x, y + 1) && split[y + 1][x] == current + 1)
		next_pos[++i] = (t_pos) {x, y + 1};
	if (is_in_bound(split, x - 1, y) && split[y][x - 1] == current + 1)
		next_pos[++i] = (t_pos) {x - 1, y};
	
	return (next_pos);
}

static int	trail(char **split, int x, int y)
{
	t_pos	*next_pos;
	int		paths;

	if (split[y][x] == '9')
		return (1);

	next_pos = get_next_pos(split, x, y);

	paths = 0;
	for (int i = 0; i < 4; i++)
	{
		if (next_pos[i].x == -1 && next_pos[i].y == -1)
			break ;
		
		paths += trail(split, next_pos[i].x, next_pos[i].y);
	}
	
	return (paths);
}

long int	resolve_part2(char *input, char **split)
{
	(void)	input;
	int		y;
	int		x;
	int		result;
	
	result = 0;
	
	y = -1;
	while (split[++y])
	{
		x = -1;
		while (split[++x])
		{
			if (split[y][x] == '0')
			{
				int paths = trail(split, x, y); 
				result += paths;
			}
		}
	}

	return (result);
}
