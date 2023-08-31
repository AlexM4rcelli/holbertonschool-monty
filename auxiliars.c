# include "main.h"

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
		{NULL, NULL}
	};

	while (opcodes[i].opcode)
	{
		if (strcmp(opcodes[i].opcode, ins[0]) == 0)
		{
			opcodes[i].f(stack, line);
			return (0);
		}
		i++;
	}
	return (-1);
}

/**
 * free_stack - frees a doubly linked list
 * @head: linked list to free
 */
void free_stack(stack_t *head)
{
	stack_t *curr = head;
	stack_t *next;

	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
}

/**
 * free_all - frees a array of arrays
 * @array: array to free
 */

void free_all(char **array)
{
	int i;

	if (array)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);
		free(array);
	}
}

/**
 * parser - Tokenize a string based on a separator.
 * @str: The string to be tokenized.
 * @separator: The separator used for tokenization.
 *
 * Return: An array of tokens.
 */
char **parser(char *str, char *separator)
{
	char **tokens = NULL, *token = NULL, *aux = NULL;
	int i, count = 0, j;

	if (!str)
		return (NULL);
	for (i = 0; str[i]; i++)
	{
		for (j = 0; separator[j]; j++)
		{
			if (str[i] == separator[j] || str[i + 1] == '\0')
				count++;
		}
	}
	count++;
	tokens = malloc(count * sizeof(char *));
	if (!tokens)
	{
		perror("Error: malloc failed");
		exit(EXIT_FAILURE);
	}
	aux = strdup(str);
	token = strtok(aux, separator);
	for (i = 0; token; i++)
	{
		tokens[i] = strdup(token);
		if (!tokens[i])
		{
			perror("Error: malloc failed");
			free_all(tokens);
			free(aux);
			exit(EXIT_FAILURE);
		}
		token = strtok(NULL, separator);
	}
	tokens[i] = NULL;
	free(aux);
	return (tokens);
}
