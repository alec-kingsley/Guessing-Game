#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

int length(struct node *head) {
	int result = 0;
	while (head != NULL) {
		result++;
		head = head->next;
	}
	return result;
}

void insert_node(struct node **head, void *value, int pos) {
	struct node *new_node = (struct node *)calloc(1, sizeof(struct node));
	struct node *trav = *head;
	new_node->value = value;

	if (pos == 0) {
		new_node->next = *head;
		*head = new_node;
	} else {
		while (pos > 1 && trav->next != NULL) {
			trav = trav->next;
			pos--;
		}
		new_node->next = trav->next;
		trav->next = new_node;
	}
}

void remove_node(struct node **head, int pos, const bool FREE_VALUE) {
	struct node *trav = *head;
	struct node *temp;
	if (pos == 0) {
		*head = trav->next;
		free(trav);
	} else {
		while (pos > 1) {
			trav = trav->next;
			pos--;
		}
		temp = trav->next;
		trav->next = trav->next->next;
		if (FREE_VALUE) {
			free(temp->value);
		}
		free(temp);
	}
}

struct node *get_node(struct node *head, int pos) {
	while (pos > 0) {
		head = head->next;
		pos--;
	}
	return head;
}

void copy_list(struct node **dest, struct node *src) {
	struct node *trav = *dest;
	struct node *new_node = NULL;
	while (src != NULL) {
		new_node = calloc(1, sizeof(struct node));
		if (!new_node) {
			perror("Failed to allocate memory for new node");
			exit(EXIT_FAILURE);
		}

		new_node->value = src->value;
		new_node->next = NULL;

		if (*dest == NULL) {
			*dest = new_node;
		} else {
			trav->next = new_node;
		}

		trav = new_node;
		src = src->next;
	}
}

void free_list(struct node *head, const bool FREE_VALUES) {
	struct node *trav = head;
	while (head != NULL) {
		trav = head->next;
		if (FREE_VALUES) {
			free(head->value);
		}
		free(head);
		head = trav;
	}
}

