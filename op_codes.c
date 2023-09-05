# include "monty.h"

/**
 * my_push - pushes an integer on a stack
 * @head: double pointer to the top of the stack
 * @line: line number of the instruction in the file
 */
void my_push(stack_t **head, unsigned int line)
{
	int num, i = 0;
	char *num_str = NULL;
	stack_t *new;

	if (!(vars.ins[1]))
	{
		fprintf(stderr, "L%u: usage: push integer\n", line);
		frees(vars.stack, vars.ins, vars.buff);
		fclose(vars.file);
		exit(EXIT_FAILURE);
	}
	num_str = vars.ins[1];
	while (num_str[i])
	{
		if (!isdigit(num_str[i]) && num_str[i] != '-')
		{
			fprintf(stderr, "L%u: usage: push integer\n", line);
			frees(vars.stack, vars.ins, vars.buff);
			fclose(vars.file);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	new = malloc(sizeof(stack_t));
	if (!new)
	{
		perror("Error: malloc failed");
		frees(vars.stack, vars.ins, vars.buff);
		fclose(vars.file);
		exit(EXIT_FAILURE);
	}
	num = atoi(vars.ins[1]);
	(new)->prev = NULL;
	(new)->n = num;
	(new)->next = *head;
	if (*head)
		(*head)->prev = new;
	*head = new;
}

/**
 * my_pall - Prints all elements of the stack
 * @head: double pointer to the top of the stack
 * @line: line number of the instruction in the file
 */
void my_pall(stack_t **head, unsigned int line)
{
	(void)line;

    stack_t *curr = *head;

    while (curr)
    {
        fprintf(stdout, "%i\n", (curr)->n);
        curr = (curr)->next;
    }

    free_all(vars.ins);
    free(vars.buff);
    fclose(vars.file);
    exit(EXIT_SUCCESS);
}
/**
 * my_pint - prints the value at the top of the stack
 * @head: double pointer to the top of the stack
 * @line: line number of the instruction in the file
 */
void my_pint(stack_t **head, unsigned int line)
{
	if (*head == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line);
		free_all(vars.ins);
		free(vars.buff);
		fclose(vars.file);
		exit(EXIT_FAILURE);
	}

	printf("%d\n", (*head)->n);
}
