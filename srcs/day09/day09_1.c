


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

	disk_len--;

	i = -1;
	while (++i < disk_len)
	{
		while (disk[i] != -1)
			i++;
		while (disk[disk_len] == -1)
			disk_len--;

		if (i >= disk_len)
			break ;

		swap(disk + i, disk + disk_len);
		disk_len--;
	}
}

long int	resolve_part1(char *input, char **split)
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
	// 	prlong intf("%d ", disk[i]);
	// prlong intf("\n");

	result = 0;

	i = -0;
	while (disk[i] != -1)
	{
		result += i * disk[i];
		i++;
	}

	return (result);
}
