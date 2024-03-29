#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct contact {
    char name[32];
    char phone[16];
};

typedef struct contact contact;

int compare_contacts(const void *a, const void *b) {
    const contact *contact1 = (const contact *)a;
    const contact *contact2 = (const contact *)b;

    return strcmp(contact1->name, contact2->name);
}

int main() {
    int numContacts;

    printf("Enter the number of contacts: ");
    scanf("%d", &numContacts);

    // Allocate memory for the phonebook
    contact *phonebook = (contact *)malloc(numContacts * sizeof(contact));
    if (phonebook == NULL) {
        printf("Memory allocation failed.");
        return 1;
    }

    // Get contact details from the user
    for (int i = 0; i < numContacts; i++) {
        printf("Enter name for contact %d: ", i + 1);
        scanf("%s", phonebook[i].name);
        printf("Enter phone number for contact %d: ", i + 1);
        scanf("%s", phonebook[i].phone);
    }

    // Sort the phonebook array by name.
    qsort(phonebook, numContacts, sizeof(contact), compare_contacts);

    // Loop for searching
    int choice;
    char name[32];
    do {
        printf("\n1. Search contact\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter a name to search for: ");
                scanf("%s", name);

                // Perform a binary search on the phonebook array.
                int low = 0;
                int high = numContacts - 1;
                int mid;
                while (low <= high) {
                    mid = (low + high) / 2;

                    if (strcmp(name, phonebook[mid].name) < 0) {
                        high = mid - 1;
                    } else if (strcmp(name, phonebook[mid].name) > 0) {
                        low = mid + 1;
                    } else {
                        // Found the contact.
                        printf("The phone number for %s is %s.\n", name, phonebook[mid].phone);
                        break;
                    }
                }
                if (low > high) {
                    printf("Contact not found.\n");
                }
                break;
            case 2:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter again.\n");
                break;
        }
    } while (choice != 2);

    // Free dynamically allocated memory
    free(phonebook);

    return 0;
    }
