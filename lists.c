#include "shell.h"

/**
 * add_node - Add a node to the start of the list
 * @head: Pointer to the head node
 * @str: String field of the node
 * @num: Node index used by history
 *
 * Return: Address of the new node
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_node;

	if (!head)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

/**
 * add_node_end - Add a node to the end of the list
 * @head: Pointer to the head node
 * @str: String field of the node
 * @num: Node index used by history
 *
 * Return: Address of the new node
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - Print only the str element of a list_t linked list
 * @h: Pointer to the first node
 *
 * Return: Size of the list
 */
size_t print_list_str(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * delete_node_at_index - Delete a node at the given index
 * @head: Address of the pointer to the first node
 * @index: Index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int count = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}

	node = *head;
	while (node)
	{
		if (count == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		count++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - Free all nodes of a list
 * @head_ptr: Address of the pointer to the head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;

	head = *head_ptr;
	node = head;

	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}

	*head_ptr = NULL;
}