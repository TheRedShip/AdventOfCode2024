/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:30:37 by TheRed            #+#    #+#             */
/*   Updated: 2024/12/01 15:30:37 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

char *get_input(char *file)
{
	int fd;
	int rd_len;
	char buffer[1000];
	int len;
	char *res;

	fd = open(file, O_RDONLY);
	len = 0;
	if(fd < 0)
		return(0);
	rd_len = -1;
	while(rd_len)
	{
		rd_len = read(fd, buffer, 1000);
		len+= rd_len;
	}
	close(fd);
	res = malloc(len + 1);
	if(!res)
		return(0);
	fd = open(file, O_RDONLY);
	if(fd < 0)
		return(0);
	rd_len = read(fd,res, len);
	res[len] = 0;
	close(fd);
	return(res);
}

int main(int argc, char **argv)
{
	char	**split;
	char	*input;
	char	*input_cpy;
	char	*input_name;

	input_name = (argc > 1 && !ft_strcmp(argv[1], "test")) ? "input_test.txt" : "input.txt";
	input = get_input(input_name);
	input_cpy = ft_strdup(input);

	if (!input || !input_cpy)
		return (printf("Error reading the input file\n"));
	
	split = ft_split(input, '\n');
	if (!split)
		return (printf("Error splitting the input\n"));
	printf("Part 1: %ld\n", resolve_part1(input, split));
	ft_free_tab((void **)split);

	split = ft_split(input_cpy, '\n');
	if (!split)
		return (printf("Error splitting the input\n"));
	printf("Part 2: %ld\n", resolve_part2(input, split));
	
	ft_free_tab((void **)split);
	free(input);
	free(input_cpy);
	
	return (0);		
}
