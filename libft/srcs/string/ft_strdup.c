/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:42:06 by rgramati          #+#    #+#             */
/*   Updated: 2024/12/07 00:16:57 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, int n)
{
	char	*cpy;
	char	*tmp;

	cpy = malloc((ft_max(n, ft_strlen(str)) + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	tmp = cpy;
	while (*str && n--)
		*(cpy++) = *(str++);
	*cpy = 0;
	return (tmp);
}

char	*ft_strdup(char *str)
{
	char	*cpy;
	char	*tmp;

	cpy = ft_calloc((ft_strlen(str) + 1), sizeof(char));
	if (!cpy)
		return (NULL);
	tmp = cpy;
	while (*str)
		*(cpy++) = *(str++);
	return (tmp);
}
