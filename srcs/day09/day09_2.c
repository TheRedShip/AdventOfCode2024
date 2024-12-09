


#include "base.h"

static long int	*create_disk(char *input, long int disk_len)
{
	long int		i;
	long int		k;
	long int		id;
	long int		*disk;

	i = -1;
	
	disk = ft_calloc(sizeof(long int), disk_len);

	i = -1;
	k = -1;
	id = -1;
	while (input[++i])
	{
		if (i % 2 == 0)
			id++;
		for (long int j = 0; j < input[i] - '0'; j++)
		{
			if (i % 2 == 0)
				disk[++k] = id;
			else
				disk[++k] = -1;
		}
	}

	return (disk);
}

static void	swap(long int *a, long int *b)
{
	long int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	compact_disk(long int *disk, long int disk_len)
{
	long int	i;
	int			current_len_num;
	int			current_len_free;

	disk_len--;

	while (disk_len >= 0)
	{
		current_len_num = disk_len;
		while (disk_len >= 1 && disk[disk_len] == disk[disk_len - 1])
			disk_len--;
		current_len_num = current_len_num - disk_len + 1;


		current_len_free = 0;
		i = -1;
		while (++i < disk_len)
		{
			if (current_len_free >= current_len_num)
				break ;
			if (disk[i] != -1)
				current_len_free = 0;
			else
				current_len_free++;
		}
		
		if (current_len_free < current_len_num)
		{
			disk_len--;
			continue ;
		}

		i -= current_len_num;
		while (current_len_num > 0)
		{
			swap(disk + i, disk + (disk_len + current_len_num - 1));
			current_len_num--;
			i++;
		}

		disk_len--;
	}
}

long int	resolve_part2(char *input, char **split)
{
	(void)	split;
	(void)	input;
	long int		i;
	long int		*disk;
	long int		disk_len;
	long int		result;

	i = -1;
	disk_len = 0;
	while (input[++i])
		disk_len += input[i] - '0';

	disk = create_disk(input, disk_len);
	compact_disk(disk, disk_len);


	// for (i = 0; i < disk_len; i++)
	// 	printf("%ld ", disk[i]);
	// printf("\n");
	
	result = 0;

	i = -1;
	while (++i < disk_len)
	{
		if (disk[i] != -1)
		{
			// printf("\n%ld * %ld", i, disk[i]);
			result += i * disk[i];
		}
	}

	return (result);
}
