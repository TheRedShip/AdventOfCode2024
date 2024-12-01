/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day01_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:13:05 by TheRed            #+#    #+#             */
/*   Updated: 2024/12/01 16:13:05 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "day01.h"

static void		fill_tab(char **split, int *tab_left, int *tab_right)
{
	int	k;
	int	i;

	k = -1;
	while (*split)
	{
		i = 0;
		tab_left[++k] = ft_atoi(*split);
		while ((*split)[i] && ft_isdigit((*split)[i]))
			i++;
		while ((*split)[i] && ft_isspace((*split)[i]))
			i++;
		tab_right[k] = ft_atoi(*split + i);
		split++;
	}
}

int			count_time(int *tab, int num)
{
	int	count;

	count = 0;
	while (*tab)
	{
		if (*tab == num)
			count++;
		tab++;
	}
	return (count);
}

long int	resolve_part2(char *input, char **split)
{
	(void) input;
	int	i;
	int	len;
	int	result;
	int	*tab_left;
	int	*tab_right;

	len = ft_tab_len(split);
	tab_left = ft_calloc(sizeof(int), len + 1);
	if (!tab_left)
		return (0);
	tab_right = ft_calloc(sizeof(int), len + 1);
	if (!tab_right)
		return (0);

	fill_tab(split, tab_left, tab_right);
	
	result = 0;
	i = -1;
	while (tab_left[++i])
		result += tab_left[i] * count_time(tab_right, tab_left[i]);
	free(tab_left);
	free(tab_right);
	return (result);
}