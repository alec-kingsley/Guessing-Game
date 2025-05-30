#define MAX_STRLEN 100

/* thing struct for each thing to guess */
struct Thing {
	char name[100];
	struct node *traits;

};

/**
 * Add a trait to a thing's trait list.
 *
 * Parameters:
 * thing - the thing to modify
 * trait - the trait to add
 *
 */
void add_trait(struct Thing *thing, const char *trait);

/**
 * Generate the things linked list from "things_sheet" file.
 *
 * Parameters:
 * things - the linked list of things (should start as empty)
 *
 */
void generate_things(struct node **things);

/**
 * Save the things linked list to "things_sheet".
 *
 * Parameters:
 * things - the linked list of things
 *
 */
void save_things(struct node *things);

