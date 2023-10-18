#include "shell.h"

alias_list *add_alias_end(alias_list **head, char *name, char *value);
void free_alias_list(alias_list *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

/**
 * add_alias_end - This function adds a new node to the end
 * of a linked list.
 *
 * @head: A pointer to the head of the linked list.
 * @name: The name of the new node.
 * @value: The value of the added node.
 *
 * Return: A pointer to the new node, NULL in case of failure.
 */

alias_list *add_alias_end(alias_list **head, char *name, char *value)
{
	alias_list *new_node = malloc(sizeof(alias_list));
	alias_list *last;

	if (!new_node)
		return (NULL);

	new_node->next = NULL;
	new_node->a_node = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!new_node->a_node)
	{
		free(new_node);
		return (NULL);
	}
	new_node->a_value = value;
	_strcpy(new_node->a_node, name);

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * add_node_end - Appends a new node at the end of a list_t linked list.
 * @head: The head pointer of linked list.
 * @dir: The directory of the new node.
 *
 * Return: A pointer to the new node, NULL in case of an error.
 */

list_t *add_node_end(list_t **head, char *dir)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *last;

	if (!new_node)
		return (NULL);

	new_node->node = dir;
	new_node->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * free_alias_list - This function deallocates memory for a linked
 * list of alias nodes.
 *
 * @head: The header to the linked list.
 */

void free_alias_list(alias_list *head)
{
	alias_list *next;

	while (head)
	{
		next = head->next;
		free(head->a_node);
		free(head->a_value);
		free(head);
		head = next;
	}
}

/**
 * free_list - This function frees memory for a linked list.
 *
 * @head: The header to the linked list.
 */

void free_list(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->node);
		free(head);
		head = next;
	}
}
