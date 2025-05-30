#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"
#include "things.h"

/**
 * Implementation of things.h function.
 */
void add_trait(struct Thing *thing, const char *trait) {
	char *trait_copy = calloc(1, strlen(trait));
	if (!trait_copy) {
		perror("Failed to allocate memory for trait");
		exit(EXIT_FAILURE);
	}

	/* copy trait, accounting for tab */
	strcpy(trait_copy, trait + 1);
	insert_node(&(thing->traits), trait_copy, length(thing->traits));
}

/**
 * Implementation of things.h function.
 */
void generate_things(struct node **things) {
	FILE *file = fopen("thing_sheet", "r");
	if (!file) {
		perror("Error opening file `thing_sheet`");
		exit(EXIT_FAILURE);
	}

	struct Thing *current_thing = NULL;
	char line[MAX_STRLEN];
	while (fgets(line, sizeof(line), file)) {
		if (line[strlen(line) - 1] == '\n') {
			/* remove newline */
			line[strlen(line) - 1] = '\0';
		}

		if (strchr(line, ':')) {
			/* new thing ; save last thing if not first. */
			if (current_thing) {
				insert_node(things, current_thing, length(*things));
			}

			current_thing = calloc(1, sizeof(struct Thing));
			if (!current_thing) {
				perror("Failed to allocate memory for thing");
				exit(EXIT_FAILURE);
			}

			current_thing->traits = NULL;
			sscanf(line, "%[^:]", current_thing->name);
		} else if (current_thing && strlen(line) > 0) {
			/* trait ; update current thing */
			add_trait(current_thing, line);
		}
	}

	/* add last thing */
	if (current_thing) {
		insert_node(things, current_thing, length(*things));
	}
	fclose(file);
}

/**
 * Implementation of things.h function.
 */
void save_things(struct node *things) {
	FILE *file = fopen("things_sheet", "w");
	if (!file) {
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	struct node *current = things;
	while (current) {
		struct Thing *thing = (struct Thing *)current->value;
		fprintf(file, "%s:\n", thing->name);

		struct node *trait_node = thing->traits;
		while (trait_node) {
			fprintf(file, "\t%s\n", (char *)trait_node->value);
			trait_node = trait_node->next;
		}
		current = current->next;
	}
	fclose(file);
}

