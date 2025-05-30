#include <stdbool.h>

struct node {
	void *value;
	struct node *next; 
};

int length(struct node *head);

void insert_node(struct node **head, void *value, int pos);

void remove_node(struct node **head, int pos, const bool FREE_VALUE);

struct node *get_node(struct node *head, int pos);

void copy_list(struct node **dest, struct node *src);

void free_list(struct node *head, const bool FREE_VALUES);

