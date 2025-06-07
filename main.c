#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "linkedlist.h"
#include "things.h"

/* for counting the trait with "most middleness" */
struct TraitNode {
	char trait[MAX_STRLEN];
	int count;
};

/**
 * Generates a linked list of TraitNodes which includes how many of each trait it finds.
 *
 * Parameters:
 * trait_counts - the linked list of TraitNodes to generate
 * things - the linked list of things
 *
 */
void get_trait_counts(struct node **trait_counts, struct node *things) {
	const int THING_CT = length(things);
	struct Thing *thing;
	struct TraitNode *trait;
	char *thing_trait;
	int thing_trait_ct, total_trait_ct = 0;
	int i, j, k;
	bool trait_found;

	*trait_counts = NULL;

	/* iterate over each thing */
	for (i = 0; i < THING_CT; i++) {
		thing = get_node(things, i)->value;
		thing_trait_ct = length(thing->traits);

		/* process thing's traits */
		for (j = 0; j < thing_trait_ct; j++) {

			/* check if trait  has been seen before */
			trait_found = false;
			thing_trait = get_node(thing->traits, j)->value;
			for (k = 0; k < total_trait_ct && !trait_found; k++) {
				trait_found |= strcmp(thing_trait, get_node(*trait_counts, k)->value) == 0;
			}

			/* process trait */
			if (trait_found) {
				(((struct TraitNode*)(get_node(*trait_counts, k - 1)->value))->count)++;
			} else {
				trait = (struct TraitNode*)calloc(1, sizeof(struct TraitNode));
				memcpy(trait->trait, thing_trait, strlen(thing_trait));
				trait->count = 1;
				insert_node(trait_counts, trait, 0);
				total_trait_ct++;
			}
		}
	}
}

/**
 * Finds the trait that applies to closest to half the things.
 *
 * Parameters:
 * trait_counts - linked list of TraitNodes
 * THING_CT - total # of things on the list
 *
 */
char *get_guess(struct node *trait_counts, const int THING_CT) {
	char *guess;
	int min_dist = INT_MAX, dist;
	const int TOTAL_TRAIT_CT = length(trait_counts);
	struct TraitNode *trait_n;
	int i;
	for (i = 0; i < TOTAL_TRAIT_CT; i++) {
		trait_n = get_node(trait_counts, i)->value;

		if (trait_n->count != 0 && trait_n->count != THING_CT) {
			/* If information would be gained... */
			dist = trait_n->count - THING_CT / 2;
			if (dist < 0) {
				dist = -dist;
			}
			if (dist < min_dist) {
				guess = trait_n->trait;
				min_dist = dist;
			}
		}
	}
	return guess;
}

/**
 *	Checks if a thing has a certain trait.
 *
 *	Parameters:
 *	thing - thing to check
 *	TRAIT - trait to look for
 *
 */
bool has_trait(struct Thing *thing, const char *TRAIT) {
	int trait_ct = length(thing->traits);
	bool trait_found = false;
	int i;
	for (i = 0; i < trait_ct && !trait_found; i++) {
		if (strcmp(get_node(thing->traits, i)->value, TRAIT) == 0) {
			trait_found = true;
		}
	}
	return trait_found;
}

/**
 *	Removes things what do or do not have a given trait.
 *
 *	Parameters:
 *	things - linked list of Thing structs
 *	TRAIT - trait to remove or keep
 *	WITH_TRAIT - true iff should remove things with trait, else keep
 *
 */
void purge_trait(struct node **things, const char *TRAIT, const bool WITH_TRAIT) {
	int things_ct = length(*things);
	int i;
	for (i = things_ct - 1; i >= 0; i--) {
		/* delete if necessary */
		if (has_trait(get_node(*things, i)->value, TRAIT) ^ WITH_TRAIT) {
			remove_node(things, i, false);
		}
	}
}

int main(void) {
	struct node *things = NULL, *remaining = NULL;
	struct node *trait_counts = NULL, *traits = NULL;
	char *trait;
	int things_ct;
	int i;
	char *guess, resp[MAX_STRLEN];
	printf("Welcome to the Guessing Game! Answer yes/no to each question, and I will divine what you're thinking of!\n");

	generate_things(&things);
	things_ct = length(things);

	/* save to separate list in case we need to update database */
	copy_list(&remaining, things);

	while (things_ct > 1) {
		get_trait_counts(&trait_counts, remaining);
		guess = get_guess(trait_counts, things_ct);

		/* save traits to add to new character in case of failure */
		trait = calloc(1, strlen(guess) + 1);
		if (!trait) {
			perror("Failed to allocate memory for trait");
			exit(EXIT_FAILURE);
		}

		/* copy trait, accounting for tab */
		strcpy(trait, guess);
		insert_node(&traits, trait, 0);

		printf("Is the thing you're thinking of %s?\n", guess);
		scanf(" %[^\n]s", resp);
		purge_trait(&remaining, guess, resp[0] == 'y');
		things_ct = length(remaining);

		/* clean up trait counts to use again */
		free_list(trait_counts, true);
	}

	/* make final guess */
	printf("You are thinking of %s.\n", ((struct Thing*)get_node(remaining, 0)->value)->name);

	/* clean up */
	for (i = length(things) - 1; i >= 0; i--) {
		free_list((((struct Thing*)(get_node(things, i)->value))->traits), true);
	}
	free_list(things, true);
	free_list(remaining, false);
	free_list(traits, true);

	return 0;
}

