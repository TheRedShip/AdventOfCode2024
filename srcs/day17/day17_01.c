

#include "base.h"
#include <string.h>
#include <math.h>

typedef enum	s_op
{
	ADV = 0,
	BXL = 1,
	BST = 2,
	JNZ = 3,
	BXC = 4,
	OUT = 5,
	BDV = 6,
	CDV = 7,
	END = 8
}				t_op;

typedef struct	s_reg
{
	long int	a;
	long int	b;
	long int	c;
}				t_reg;

typedef struct	s_com
{
	t_reg		reg;
	int			cursor;
}				t_com;

int	*parse_com(char **split, t_com *com)
{
	int		k;
	int		*prog;
	int		prog_len;
	char	*prog_input;
	
	com->reg.a = atol(split[0] + 12);
	com->reg.b = atol(split[1] + 12);
	com->reg.c = atol(split[2] + 12);

	com->cursor = 0;

	prog_input = split[3] + 9;
	prog_len = 1;
	for (int i = 0; prog_input[i]; i++)
		if (prog_input[i] == ',')
			prog_len++;
	
	k = -1;
	prog = ft_calloc(sizeof(int), prog_len + 1);
	for (int i = 0; prog_input[i]; i++)
	{
		if (ft_isdigit(prog_input[i]))
			prog[++k] = prog_input[i] - '0';
	}
	prog[prog_len] = END;

	return (prog);
}

int				get_combo(t_op operand, t_com com)
{
	if (operand >= 0 && operand <= 3)
		return (operand);
	if (operand == 4)
		return (com.reg.a);
	if (operand == 5)
		return (com.reg.b);
	if (operand == 6)
		return (com.reg.c);
	if (operand == 7)
		return (-1);
	return (-1);
}

void			exec_adv(t_com *com, int operand)
{
	com->reg.a = com->reg.a / (pow(2.0, (double) operand));
}

void			exec_bxl(t_com *com, int operand)
{
	com->reg.b = com->reg.b ^ operand;
}

void			exec_bst(t_com *com, int operand)
{
	com->reg.b = operand % 8;
}

void			exec_jnz(t_com *com, int operand)
{
	if (com->reg.a == 0)
		return ;
	com->cursor = operand - 2; //skipping com->cursor+=2;
}

void			exec_bxc(t_com *com, int operand)
{
	(void) operand;
	com->reg.b = com->reg.b ^ com->reg.c;
}

void			exec_out(t_com *com, int operand)
{
	(void) com;
	printf("%d,", operand % 8);
}

void			exec_bdv(t_com *com, int operand)
{
	com->reg.b = com->reg.a / (pow(2.0, (double) operand));
}

void			exec_cdv(t_com *com, int operand)
{
	com->reg.c = com->reg.a / (pow(2.0, (double) operand));
}

void			execute_prog(int *prog, t_com *com)
{
	t_op	op;
	int		combo;
	int		litteral;

	int		prog_len;

	prog_len = -1;
	while (prog[++prog_len] != END);

	while (prog[com->cursor] != END && com->cursor < prog_len)
	{
		op = prog[com->cursor];
		
		combo = get_combo(prog[com->cursor + 1], *com);
		litteral = prog[com->cursor + 1];

		if (op == ADV)
			exec_adv(com, combo);
		else if (op == BXL)
			exec_bxl(com, litteral);
		else if (op == BST)
			exec_bst(com, combo);
		else if (op == JNZ)
			exec_jnz(com, litteral);
		else if (op == BXC)
			exec_bxc(com, 0);
		else if (op == OUT)
			exec_out(com, combo);
		else if (op == BDV)
			exec_bdv(com, combo);
		else if (op == CDV)
			exec_cdv(com, combo);

		com->cursor += 2;
	}
}

long int		resolve_part1(char *input, char **split)
{
	(void)		split;
	(void)		input;
	t_com		com;
	int			*prog;

	prog = parse_com(split, &com);

	printf("Reg A: %ld\n", com.reg.a);
	printf("Reg B: %ld\n", com.reg.b);
	printf("Reg C: %ld\n", com.reg.c);

	printf("prog: ");
	for (int i = 0; prog[i] != END; i++)
		printf("%d ", prog[i]);
	printf("\n");
	printf("\n");
	
	execute_prog(prog, &com);

	printf("\n");
	printf("\n");

	printf("Reg A: %ld\n", com.reg.a);
	printf("Reg B: %ld\n", com.reg.b);
	printf("Reg C: %ld\n", com.reg.c);

	return (0);
}