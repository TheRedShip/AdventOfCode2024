/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day08_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 16:59:03 by TheRed            #+#    #+#             */
/*   Updated: 2024/12/08 16:59:03 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

typedef struct	s_node
{
	int 	x;
	int		y;
	char	node;
}				t_node;

static t_node	*parsing(char **split)
{
	t_node	*antennas;
	int		tab_len;
	int		y;
	int		x;
	int		k;

	tab_len = 0;
	y = -1;
	while (split[++y])
	{
		x = -1;
		while (split[y][++x])
			if (ft_isalnum(split[y][x]))
				tab_len++;
	}

	antennas = ft_calloc(sizeof(t_node), tab_len + 1);

	k = -1;
	y = -1;
	while (split[++y])
	{
		x = -1;
		while (split[y][++x])
			if (ft_isalnum(split[y][x]))
				antennas[++k] = (t_node) {x, y, split[y][x]};
	}
	return (antennas);
}

static int	is_in_bound(char **split, int *pos)
{
	return ((pos[0] >= 0 && pos[0] < (int)ft_strlen(split[0]) && (pos[1] >= 0 && pos[1] < (int)ft_tab_len(split))));
}

static void		find_antinode(t_node *antennas, char **split, char **map_copy)
{
	int	i;
	int	j;
	int	dist[2];
	int	new_pos[2][2];
	
	i = -1;
	while (antennas[++i].node)
	{
		j = i;
		while (antennas[++j].node)
		{
			if (antennas[i].node == antennas[j].node)
			{
				dist[0] = antennas[j].x - antennas[i].x;
				dist[1] = antennas[j].y - antennas[i].y;
				
				new_pos[0][0] = antennas[i].x - dist[0];
				new_pos[0][1] = antennas[i].y - dist[1];

				new_pos[1][0] = antennas[j].x + dist[0];
				new_pos[1][1] = antennas[j].y + dist[1];


				if (is_in_bound(split, new_pos[0]) && map_copy[new_pos[0][1]][new_pos[0][0]] != '#')
					map_copy[new_pos[0][1]][new_pos[0][0]] = '#';
				if (is_in_bound(split, new_pos[1]) && map_copy[new_pos[1][1]][new_pos[1][0]] != '#')
					map_copy[new_pos[1][1]][new_pos[1][0]] = '#';
			}
		}
	}
}

static char	**char_tab_dup(char **tab)
{
	char	**new_tab;
	int		k;

	k = -1;
	new_tab = ft_calloc(sizeof(char *), ft_tab_len(tab) + 1);
	while (tab[++k])
		new_tab[k] = ft_strdup(tab[k]);
	return (new_tab);
}

long int	resolve_part1(char *input, char **split)
{
	(void)	input;
	int		result;
	t_node	*antennas;
	char	**map_copy;

	map_copy = char_tab_dup(split);
	antennas = parsing(split);
	
	find_antinode(antennas, split, map_copy);
	
	result = 0;
	for (int i = 0; map_copy[i]; i++)
		for (int j = 0; map_copy[j]; j++)
			if (map_copy[i][j] == '#')
				result++;

	free(antennas);
	ft_free_tab((void **)map_copy);
	return (result);
}