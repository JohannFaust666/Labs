#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node // Doubly linked list structure
{
    int data; // Node data (int number)
    struct Node *next; // Next list node
    struct Node *prev; // Previous list node
};

void insertFront(struct Node **head, int data) // Insert new node in front
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = (*head);
    newNode->prev = NULL;
    if ((*head) != NULL)
    {
        (*head)->prev = newNode;
    }
    (*head) = newNode;
}

void insertAfter(struct Node *prev_node, int data) // Insert new node after
{
    if (prev_node == NULL)
    {
        printf("previous node cannot be null");
        return;
    }
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = prev_node->next;
    prev_node->next = newNode;
    newNode->prev = prev_node;
    if (newNode->next != NULL)
    {
        newNode->next->prev = newNode;
    }
}

void insertEnd(struct Node **head, int data) // Insert new node at the end
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    struct Node *temp = *head;
    if (*head == NULL)
    {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void deleteNode(struct Node **head, struct Node *del_node) // Delete selected node
{
    if (*head == NULL || del_node == NULL)
    {
        return;
    }
    if (*head == del_node)
    {
        *head = del_node->next;
    }
    if (del_node->next != NULL)
    {
        del_node->next->prev = del_node->prev;
    }
    if (del_node->prev != NULL)
    {
        del_node->prev->next = del_node->next;
    }
    free(del_node);
}

void displayList(struct Node *node) // Display the list
{
    struct Node *last;
    while (node != NULL)
    {
        printf("%d->", node->data);
        last = node;
        node = node->next;
    }
    if (node == NULL)
    {
        printf("NULL\n");
    }
}

void bubbleSort(struct Node **head) // Bubble sort
{
    struct Node *current1 = *head;
    for (struct Node *i = current1; i != NULL; i = i->next)
    {
        for (struct Node *j = current1; j->next != NULL; j = j->next)
        {
            if (j->data > j->next->data)
            {
                int temp = j->data;
                j->data = j->next->data;
                j->next->data = temp;
            }
        }
    }
}

void combSort(struct Node **head) // Comb sort
{
    int length = 0;
    struct Node *current1 = *head;
    while (current1 != NULL)
    {
        length++;
        current1 = current1->next;
    }
    int gap = length;
    int swapped = 1;
    while (gap > 1 || swapped)
    {
        if (gap > 1)
        {
            gap = (int)(gap / 1.3);
        }
        swapped = 0;
        struct Node *current2 = *head;
        struct Node *next = (*head)->next;
        for (int i = 0; i < length - gap; i++)
        {
            if (current2->data < next->data)
            {
                int temp = current2->data;
                current2->data = next->data;
                next->data = temp;
                swapped = 1;
            }
            current2 = current2->next;
            next = next->next;
        }
    }
}

int main() // main function
{
    struct Node *head = NULL;
    int operation;
    do
    {
        printf("Choose operation:\n");
        printf("1. Insert at front\n");
        printf("2. Insert after a node\n");
        printf("3. Insert at end\n");
        printf("4. Delete a node\n");
        printf("5. Fill the list randomly\n");
        printf("6. Bubble sort\n");
        printf("7. Comb sort (reversed)\n");
        printf("8. Display the list\n");
        printf("9. Exit\n");
        scanf("%d", &operation);
        switch (operation)
        {
            // Menu operation №1
            case 1: // Insert at front
            {
                int data;
                printf("Enter data: ");
                scanf("%d", &data);
                insertFront(&head, data);
                break;
            }
            // Menu operation №2
            case 2: // Insert after a node
            {
                int data;
                printf("Enter data: ");
                scanf("%d", &data);
                int index;
                printf("Enter index of node to insert after: ");
                scanf("%d", &index);
                struct Node *current = head;
                for (int i = 1; i < index && current != NULL; i++)
                {
                    current = current->next;
                }
                if (current == NULL)
                {
                    printf("Index out of bounds\n");
                }
                else
                {
                    insertAfter(current, data);
                }
                break;
            }
            // Menu operation №3
            case 3: // Insert at end
            {
                int data;
                printf("Enter data: ");
                scanf("%d", &data);
                insertEnd(&head, data);
                break;
            }
            // Menu operation №4
            case 4: // Delete a node
            {
                int index;
                printf("Enter index of node to delete: ");
                scanf("%d", &index);
                struct Node *current = head;
                for (int i = 0; i < index && current != NULL; i++)
                {
                    current = current->next;
                }
                if (current == NULL)
                {
                    printf("Index out of bounds\n");
                }
                else
                {
                    deleteNode(&head, current);
                }
                break;
            }
            // Menu operation №5
            case 5: // Fill the list randomly
            {
                srand(time(NULL));
                for (int i = 0; i < 10; i++)
                {
                    int data = rand() % 100;
                    insertFront(&head, data);
                }
                printf("List is filled\n");
                break;
            }
            // Menu operation №6
            case 6: // Bubble sort
            {
                bubbleSort(&head);
                break;
            }
            // Menu operation №7
            case 7: // Comb sort (reversed)
            {
                combSort(&head);
                break;
            }
            // Menu operation №8
            case 8: // Display the list
            {
                displayList(head);
                break;
            }
            // Menu operation №9
            case 9: // Exit
            {
                printf("Exiting...\n");
                break;
            }

            default: // Invalid menu command
            {
                printf("Invalid operation\n");
                break;
            }
        }
    }
    while (operation != 9);
    return 0;
}
