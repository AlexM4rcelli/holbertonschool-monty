# include "monty.h"
/**
 * my_pop - removes the top element from the stack
 * @head: double pointer to the top of the stack
 * @line: line number of the instruction in the file
 */
void my_pop(stack_t **head, unsigned int line)
{
	stack_t *temp = NULL;

	if (*head == NULL)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line);
		free_all(vars.ins);
		free(vars.buff);
		fclose(vars.file);
		exit(EXIT_FAILURE);
	}

	temp = *head;
	*head = (*head)->next;
	if (*head)
		(*head)->prev = NULL;

	free(temp);
}

/**
 * my_swap - swaps the top two elements of the stack
 * @head: double pointer to the top of the stack
 * @line: line number of the instruction in the file
 */
void my_swap(stack_t **head, unsigned int line)
{
	stack_t *temp;

	if (*head == NULL || (*head)->next == NULL)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line);
		free_stack(vars.stack);
		free_all(vars.ins);
		free(vars.buff);
		fclose(vars.file);
		exit(EXIT_FAILURE);
	}

	temp = (*head)->next;
	(*head)->next = temp->next;
	if (temp->next)
		temp->next->prev = *head;

	temp->prev = NULL;
	temp->next = *head;
	(*head)->prev = temp;
	*head = temp;
}

/**
 * my_add - adds the top two elements of the stack
 * @head: double pointer to the top of the stack
 * @line: line number of the instruction in the file
 */
void my_add(stack_t **head, unsigned int line)
{
	if (*head == NULL || (*head)->next == NULL)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line);
		free_stack(vars.stack);
		free_all(vars.ins);
		free(vars.buff);
		fclose(vars.file);
		exit(EXIT_FAILURE);
	}

	(*head)->next->n += (*head)->n;
	my_pop(head, line);
}

/**
* my_nop - No operation
* @head: Double pointer to the top of the stack (unused)
* @line: Line number of the instruction in the file (unused)
*/
void my_nop(stack_t **head, unsigned int line)
{
	(void)head;
	(void)line;
}
