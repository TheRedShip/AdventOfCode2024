/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day11_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:52:06 by TheRed            #+#    #+#             */
/*   Updated: 2024/12/11 23:36:19 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

#define MAP_MAX 1000
#define DEP_MAX 75

static long int	*parse_input(char *input)
{
	int			k;
	long int	*tab;
	char 		*tmp;
	int			tab_len;

	tab_len = 1;
	tmp = input;
	while (*tmp)
	{
		if (*tmp == ' ')
			tab_len++;
		tmp++;
	}

	tab = ft_calloc(sizeof(long int), tab_len + 1);
	tab[tab_len] = -1;

	k = -1;
	while (*input)
	{
		tab[++k] = ft_atoi(input);
		while (ft_isdigit(*input))
			input++;
		while (ft_isspace(*input))
			input++;
	}
	return (tab);
}

static int		get_number_size(long int num)
{
	int	size;

	size = 0;
	while (num > 0)
	{
		num /= 10;
		size++;
	}
	return (size);
}

static void	num_split(long int num, long int *left_num, long int *right_num)
{
	int			num_size;
	long int	tmp_left;
	
	num_size = get_number_size(num);
	
	*left_num = num;
	for (int i = 0; i < num_size / 2; i++)
		*left_num /= 10;
	
	tmp_left = *left_num;
	for (int i = 0; i < num_size / 2; i++)
		tmp_left *= 10;

	*right_num = num - tmp_left;
}

long int	blink(long int num, int depth, long int *map)
{
	long int	left;
	long int	right;
	long int	result;

	if (depth == 0)
		return (1);
	
	if (num >= 0 && num < MAP_MAX && map[((DEP_MAX - depth) * MAP_MAX) + num])
		return (map[((DEP_MAX - depth) * MAP_MAX) + num]);

	if (num == 0)
		return (blink(1, depth - 1, map));
	if (get_number_size(num) % 2 == 0)
	{
		num_split(num, &left, &right);
		result = blink(left, depth - 1, map);
		result += blink(right, depth - 1, map);
	}
	else
		result = blink(num * 2024, depth - 1, map);
	if (num >= 0 && num < MAP_MAX && !map[((DEP_MAX - depth) * MAP_MAX) + num])
		map[((DEP_MAX - depth) * MAP_MAX) + num] = result;
	return (result);
}

long int		resolve_part2(char *input, char **split)
{
	(void)		split;
	long int	map[MAP_MAX * DEP_MAX];
	long int	result;
	long int	*tab;
	int			i;

	ft_memset(map, 0, sizeof(map));

	result = 0;
	tab = parse_input(input);

	i = -1;
	while (tab[++i] != -1)
		result += blink(tab[i], DEP_MAX, map);

	return (result);
}
