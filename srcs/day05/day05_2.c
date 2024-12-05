/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day05_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 23:17:39 by TheRed            #+#    #+#             */
/*   Updated: 2024/12/05 23:44:27 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

typedef struct s_orders
{
	int				left;
	int				right;
	struct s_orders	*next;
}				t_orders;

static void add_order(char *line, t_orders **orders)
{
	t_orders *new;

	new = malloc(sizeof(t_orders));
	new->left = ft_atoi(line);
	while(ft_isdigit(*line))
		line++;
	line++;
	new->right = ft_atoi(line);
	new->next = *orders;
	*orders = new;
}

static int	verify_order(int num, int *tab, t_orders *orders)
{
	int	i;
	t_orders *tmp;

	i = -1;
	while (tab[++i])
	{
		tmp = orders;

		if (tab[i] == num)
			return (1);

		while (tmp)
		{
			if (tmp->left == num && tmp->right == tab[i])
				return (0);
			tmp = tmp->next;
		}
	}
	return (1);
}

static int	is_behind(t_orders *orders, int before, int after)
{
	while (orders)
	{
		if (orders->right == before && orders->left == after)
			return (0);
		orders = orders->next;
	}
	return (1);
}

static int	sort(int *tab, t_orders *orders, int len)
{
	int	tmp;
	int	i;
	int	j;

	i = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[++j])
		{
			if (!is_behind(orders, tab[i], tab[j]))
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
		}
	}
	return (tab[len / 2]);
}

static int	verify_orders(char *update, t_orders *orders)
{
	int	i;
	int	tab_len;
	int	*tab;

	tab_len = 1;
	i = -1;
	while (update[++i])
		tab_len += update[i] == ',';
	tab = ft_calloc(sizeof(int), tab_len + 1);

	i = -1;
	while(++i < tab_len)
	{
		tab[i] = ft_atoi(update);
		update += 3;
	}

	i = tab_len;
	while(tab[--i])
	{
		if (!verify_order(tab[i], tab, orders))
			return (sort(tab, orders, tab_len));
	}
	return (0);
}

long int	resolve_part2(char *input, char **split)
{
	(void) input;
	int		result;
	t_orders *orders;

	orders = NULL;
	while ((*split)[2] == '|')
	{
		add_order(*split, &orders);
		split++;
	}

	result = 0;
	split++;
	while (*split)
	{
		result += verify_orders(*split, orders);
		split++;
	}

	return (result);
}