# ifndef MONTY
# define MONTY
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <ctype.h>
/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
		int n;
		struct stack_s *prev;
		struct stack_s *next;
} stack_t;
/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
		char *opcode;
		void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;
/**
 * struct global_vars_s - structure to hold global variables for Monty
 * @ins: array of instruction tokens
 * @buff: buffer to hold lines read from the input file
 * @buffsize: size of the buffer for input lines
 * @stack: pointer to the top of the stack
 */
typedef struct global_vars_s
{
		char **ins;
		char *buff;
		size_t buffsize;
		stack_t *stack;
		FILE *file;
} global_vars_t;

extern global_vars_t vars;

int get_op_code(stack_t **stack, char **ins, unsigned int line);

void my_pall(stack_t **head, unsigned int line);
void my_push(stack_t **head, unsigned int line);
void my_pint(stack_t **head, unsigned int line);
void my_pop(stack_t **head, unsigned int line);
void my_swap(stack_t **head, unsigned int line);
void my_add(stack_t **head, unsigned int line);
void my_nop(stack_t **head, unsigned int line);

char **parser(char *str, char *separator);
void frees(stack_t *stack, char **ins, char *buff);
void free_all(char **array);
void free_stack(stack_t *head);
int is_empty_line(const char *line);

# endif
