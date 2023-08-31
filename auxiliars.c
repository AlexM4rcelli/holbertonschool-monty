# include "monty.h"


/**
 * frees - frees every special allocation
 * @stack: linked list to free
 * @ins: array of instructions to free
 * @buff: string to free.
 */
void frees(stack_t *stack, char **ins char *buff)
{
	free_stack(stack);
	free_all(ins);
	free(buff);
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

	for (i = 0; array[i]; i++)
		free(array[i]);
	free(array);
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

int is_empty_line(const char *line)
{
    while (*line != '\0')
    {
        if (!isspace(*line))
            return 0;
        line++;
    }
    return 1;
}