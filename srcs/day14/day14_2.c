
#include "base.h"

typedef struct	s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef struct	s_bots
{
	t_pos	pos;
	t_pos	vel;
}				t_bots;

static t_bots	*parse_bots(char **split)
{
	t_bots		*bots;
	int			y;

	bots = ft_calloc(sizeof(t_bots), ft_tab_len(split));

	y = -1;
	while (split[++y])
	{
		char **s = ft_split(split[y], ' ');
		char **pos = ft_split(s[0] + 2, ',');
		char **vel = ft_split(s[1] + 2, ',');

		bots[y] = (t_bots) {{ft_atoi(pos[0]), ft_atoi(pos[1])}, {ft_atoi(vel[0]), ft_atoi(vel[1])}};

		ft_free_tab((void **)s);
		ft_free_tab((void **)pos);
		ft_free_tab((void **)vel);
	}
	return (bots);
}

static void		elapse(t_bots *bots, int bots_len, t_pos area_size)
{
	int		i;
	t_pos	new_pos;

	i = -1;
	while (++i < bots_len)
	{
		new_pos.x = bots[i].pos.x + bots[i].vel.x;
		new_pos.y = bots[i].pos.y + bots[i].vel.y;

		if (new_pos.x < 0)
			new_pos.x = area_size.x - (0 - new_pos.x);
		else if (new_pos.x >= area_size.x)
			new_pos.x = 0 + (new_pos.x - area_size.x);
		
		if (new_pos.y < 0)
			new_pos.y = area_size.y - (0 - new_pos.y);
		else if (new_pos.y >= area_size.y)
			new_pos.y = 0 + (new_pos.y - area_size.y);
		
		bots[i].pos.x = new_pos.x;
		bots[i].pos.y = new_pos.y;
	}
}

static char	**create_map(t_bots *bots, int bots_len, t_pos area_size)
{
	char **map;

	map = malloc(sizeof(char *) * area_size.y + 1);

	for (int y = 0; y < area_size.y; y++)
	{
		map[y] = malloc(sizeof(char) * area_size.x + 1);
		ft_memset(map[y], '.', sizeof(map[y]));
	}

	for (int i = 0; i < bots_len; i++)
		map[bots[i].pos.y][bots[i].pos.x] = '#';

	return (map);
}

static void		show_bot(t_bots *bots, int bots_len, t_pos area_size)
{
	
	for (int y = 0; y < area_size.y; y++)
	{
		for (int x = 0; x < area_size.x; x++)
		{
			int count = 0;

			for(int i = 0; i < bots_len; i++)
				if (bots[i].pos.x == x && bots[i].pos.y == y)
					count++;
			if (count != 0)
				printf("%d", count);
			else
				printf(".");
		}
		printf("\n");
	}
	printf("\n");
}

static int		verify_tree(char **map, t_pos area_size)
{
	int	count;

	count = 0;
	for (int y = 0; y < area_size.y; y++)
	{
		for (int x = 0; x < area_size.x; x++)
		{
			if (map[y][x] == '#')
				count++;
			else
				count = 0;

			if (count >= 10)
				return (1);
		}
	}
	return (0);
}

long int		resolve_part2(char *input, char **split)
{
	(void) input;
	(void) split;
	long int	result;
	t_bots		*bots;
	t_pos		area_size = {101, 103};

	bots = parse_bots(split);
	int bots_len = ft_tab_len(split);
	// show_bot(bots, ft_tab_len(split), area_size);

	for (int i = 0; i < 8000; i++)
	{
		elapse(bots, bots_len, area_size);
		
		char **map = create_map(bots, bots_len, area_size);
		
		if (verify_tree(map, area_size))
		{
			printf("%d\n", i);
			show_bot(bots, bots_len, area_size);
		}
	}

	result = 0;
	
	// show_bot(bots, ft_tab_len(split), area_size);

	// result = quadrant(bots, ft_tab_len(split), area_size);

	return (result);
}
