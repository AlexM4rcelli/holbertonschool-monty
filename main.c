#include "monty.h"

global_vars_t vars;

/**
 * get_op_code - Executes the corresponding function based on opcode
 * @stack: Double pointer to the top of the stack
 * @ins: Array of instruction tokens
 * @line: Line number of the instruction in the file
 *
 * Return: 0 on match, -1 if doesn't match
 */
int get_op_code(stack_t **stack, char **ins, unsigned int line)
{
	unsigned int i = 0;

	instruction_t opcodes[] = {
		{"push", my_push},
		{"pall", my_pall},
		{"pint", my_pint},
		{"pop", my_pop},
		{"swap", my_swap},
		{"add", my_add},
		{"nop", my_nop},
		{NULL, NULL}
	};

	while (opcodes[i].opcode)
	{
		if (ins[0])
		{
			if (strcmp(opcodes[i].opcode, ins[0]) == 0)
			{
				opcodes[i].f(stack, line);
				return (0);
			}
		}
		i++;
	}
	return (-1);
}


/**
 * main - entry point of the Monty interpreter
 * @argc: number of command line arguments
 * @argv: array of command line arguments
 *
 * Return: Always 0 on success
 */
int main(int argc, char *argv[])
{
	size_t readed = 0;
	unsigned int line = 1;
	int op_code = 0;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	vars.file = fopen(argv[1], "r");
	if (!vars.file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while ((readed = getline(&vars.buff, &vars.buffsize, vars.file)) > 0)
	{
		if (is_empty_line(vars.buff))
		{
			line++;
			continue;
		}
		vars.ins = parser(vars.buff, " $\n\t\r\a");
		op_code = get_op_code(&vars.stack, vars.ins, line);
		if (op_code == -1)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line, vars.ins[0]);
			frees(vars.stack, vars.ins, vars.buff);
			fclose(vars.file);
			exit(EXIT_FAILURE);
		}
		free_all(vars.ins);
		line++;
	}
	if (fclose(vars.file) == -1)
		exit(EXIT_FAILURE);
	free_stack(vars.stack);
	free(vars.buff);
	return (0);
}
