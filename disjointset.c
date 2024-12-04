#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *rep; // Representative of the set
    struct node *next; // Pointer to the next element in the set (for chaining)
    int data; // Element value
};

struct node* heads[50]; // Heads of each disjoint set
struct node* tails[50]; // Tails of each disjoint set
static int countRoot = 0; // Number of disjoint sets

// Create a new disjoint set containing only element x
void makeSet(int x) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->rep = newNode; // A set's representative is itself initially
    newNode->next = NULL;    // No next element initially
    newNode->data = x;       // Set data to the element x
    
    heads[countRoot] = newNode; // Set the head of this set
    tails[countRoot] = newNode; // Set the tail of this set
    countRoot++;                // Increase the count of disjoint sets
}

// Find the representative (root) of the set containing element 'a'
struct node* find(int a) {
    int i;
    for (i = 0; i < countRoot; i++) {
        struct node *tmp = heads[i];
        while (tmp != NULL) {
            if (tmp->data == a) {
                return tmp->rep; // Return the representative of the set
            }
            tmp = tmp->next;
        }
    }
    return NULL; // Element not found in any set
}

// Union two sets containing elements a and b
void unionSets(int a, int b) {
    struct node *repA = find(a);
    struct node *repB = find(b);
    
    if (repA == NULL || repB == NULL) {
        printf("\nOne or both elements not present in the disjoint set DS\n");
        return;
    }

    if (repA != repB) {
        // Merge the two sets
        struct node *tailB = NULL;
        int i, pos;
        for (i = 0; i < countRoot; i++) {
            if (heads[i] == repB) {
                pos = i;
                tailB = tails[i];
                // Shift other sets to close the gap
                for (int j = pos; j < countRoot - 1; j++) {
                    heads[j] = heads[j + 1];
                    tails[j] = tails[j + 1];
                }
                countRoot--;
                break;
            }
        }
        
        // Append set B to set A
        tails[repA - heads[0]]->next = repB; // Link the tail of set A to the head of set B
        tails[repA - heads[0]] = tailB; // Update the tail of set A to be the tail of set B

        // Update the representative for all elements in set B
        struct node *tmp = repB;
        while (tmp != NULL) {
            tmp->rep = repA;
            tmp = tmp->next;
        }
    }
}

// Search if an element exists in any set
int search(int x) {
    for (int i = 0; i < countRoot; i++) {
        struct node *tmp = heads[i];
        while (tmp != NULL) {
            if (tmp->data == x) {
                return 1; // Element found
            }
            tmp = tmp->next;
        }
    }
    return 0; // Element not found
}

// Main driver function
int main() {
    int choice, x, y;

    do {
        printf("\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
        printf("\n.......MENU.......\n\n1.Make Set\n2.Display set representatives\n3.Union\n4.Find Set\n5.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");

        switch (choice) {
            case 1:
                printf("\nEnter new element: ");
                scanf("%d", &x);
                if (search(x) == 1) {
                    printf("\nElement already present in the disjoint set DS\n");
                } else {
                    makeSet(x);
                }
                break;
            case 2:
                printf("\nSet representatives:\n");
                for (int i = 0; i < countRoot; i++) {
                    printf("Set containing %d, representative: %d\n", heads[i]->data, heads[i]->rep->data);
                }
                break;
            case 3:
                printf("\nEnter first element: ");
                scanf("%d", &x);
                printf("\nEnter second element: ");
                scanf("%d", &y);
                unionSets(x, y);
                break;
            case 4:
                printf("\nEnter the element: ");
                scanf("%d", &x);
                struct node *rep = find(x);
                if (rep == NULL) {
                    printf("\nElement not present in the DS\n");
                } else {
                    printf("\nThe representative of %d is %d\n", x, rep->data);
                }
                break;
            case 5:
                exit(0);
            default:
                printf("\nInvalid choice, try again.\n");
                break;
        }
    } while (1);

    return 0;
}

