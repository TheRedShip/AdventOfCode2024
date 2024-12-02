/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:46:35 by TheRed            #+#    #+#             */
/*   Updated: 2024/12/01 14:46:35 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "day01.h"

static int	ft_abs(int a)
{
	if (a >= 0)
		return (a);
	return (-a);
}

static void sort_tab(int *tab, int len)
{
	int i;
	int j;
	int tmp;
	
	i = 0;
	while(i < len - 1)
	{
		j = 0;
		while(j < len - 1)
		{
			if(tab[j] > tab[j + 1])
			{
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}


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

long int	resolve_part1(char *input, char **split)
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
	
	sort_tab(tab_left, len);
	sort_tab(tab_right, len);

	result = 0;
	i = -1;
	while (tab_left[++i])
		result += ft_abs(tab_left[i] - tab_right[i]);

	free(tab_left);
	free(tab_right);
	return (result);
}
