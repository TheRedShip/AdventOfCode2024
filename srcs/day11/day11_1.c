/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day11_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:51:55 by TheRed            #+#    #+#             */
/*   Updated: 2024/12/11 23:33:57 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

static t_list	*lst_new(long int num)
{
	long int	*content;

	content = ft_calloc(sizeof(long int), 2);
	*content = num;
	return (ft_lstnew((void *)content));
}

static t_list	*parse_input(char *input)
{
	t_list	*tab = NULL;

	while (*input)
	{
		ft_lstadd_back(&tab, lst_new(ft_atoi(input)));

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

static void		lst_split(t_list **new_lst, long int num, int num_size)
{
	long int	left_num;
	long int	right_num;

	left_num = num;
	for (int i = 0; i < num_size / 2; i++)
		left_num /= 10;

	ft_lstadd_front(new_lst, lst_new(left_num));

	for (int i = 0; i < num_size / 2; i++)
		left_num *= 10;

	right_num = num - left_num;
	ft_lstadd_front(new_lst, lst_new(right_num));
}

static t_list	*blink(t_list **tab)
{
	t_list		*tmp;
	t_list		*new_list = NULL;
	long int	content;
	int			number_size;

	tmp = *tab;
	while (tmp)
	{
		content = *(long int *)tmp->content;
		number_size = get_number_size(content);

		if (content == 0)
			ft_lstadd_front(&new_list, lst_new(1));
		else if (number_size % 2 == 0)
			lst_split(&new_list, content, number_size);
		else
			ft_lstadd_front(&new_list, lst_new(content * 2024));

		tmp = tmp->next;
	}
	ft_lstclear(tab, free);
	return (new_list);
}

long int		resolve_part1(char *input, char **split)
{
	(void)		split;
	long int	result;
	t_list		*tab;

	tab = parse_input(input);
	for (int i = 0; i < 25; i++)
		tab = blink(&tab);
	
	// t_list *tmp = tab;
	// while (tmp)
	// {
	// 	printf("%ld ", *(long int *)tmp->content);
	// 	tmp = tmp->next;
	// }
	// printf("\n");
	
	result = ft_lstsize(tab);

	ft_lstclear(&tab, free);
	return (result);
}
