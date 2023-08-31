# include "monty.h"

global_vars_t vars;

/**
 * main - entry point of the Monty interpreter
 * @argc: number of command line arguments
 * @argv: array of command line arguments
 *
 * Return: Always 0 on success
 */
int main(int argc, char *argv[])
{
	ssize_t readed = 0;
	unsigned int line = 1;
	int op_code = 0;
	FILE *file = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	while ((readed = getline(&vars.buff, &vars.buffsize, file)) != -1)
	{
		vars.ins = parser(vars.buff, " $\n\t");
		op_code = get_op_code(&vars.stack, vars.ins, line);
		if (op_code == -1)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line, vars.ins[0]);
			fclose(file);
			free_all(vars.ins);
			free(vars.buff);
			exit(EXIT_FAILURE);
		}
		free_all(vars.ins);
		line++;
	}
	if (fclose(file) == -1)
		exit(EXIT_FAILURE);
	free_stack(vars.stack);
	free(vars.buff);
	return (0);
}