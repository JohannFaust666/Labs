#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum color {
    RED,
    BLACK
};

struct node *rotateRight(struct node *root);
struct node *rotateLeft(struct node *node);


struct node {
    int data;
    enum color color;
    struct node *left;
    struct node *right;
    struct node *parent;
};

struct node *newNode(int data) {
    struct node *node = (struct node *) malloc(sizeof(struct node));
    node->data = data;
    node->color = RED;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

struct node *insert(struct node *root, int data) {
    if (root == NULL) {
        return newNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
        root->left->parent = root;
    } else if (data > root->data) {
        root->right = insert(root->right, data);
        root->right->parent = root;
    } else {
        return root;
    }

    if (root->left != NULL && root->left->color == RED &&
        root->right != NULL && root->right->color == RED) {
        root->color = RED;
        root->left->color = BLACK;
        root->right->color = BLACK;
    }

    if (root->left != NULL && root->left->color == RED &&
        root->left->left != NULL && root->left->left->color == RED) {
        root = rotateRight(root);
    }

    if (root->right != NULL && root->right->color == RED &&
        root->right->right != NULL && root->right->right->color == RED) {
        root = rotateLeft(root);
    }

    if (root->left != NULL && root->left->color == RED &&
        root->right != NULL && root->right->color == RED) {
        root->color = RED;
        root->left->color = BLACK;
        root->right->color = BLACK;
    }

    return root;
}

struct node *rotateLeft(struct node *node) {
    struct node *right = node->right;
    node->right = right->left;
    if (node->right != NULL) {
        node->right->parent = node;
    }
    right->parent = node->parent;
    if (node->parent == NULL) {
        return right;
    }
    if (node == node->parent->left) {
        node->parent->left = right;
    } else {
        node->parent->right = right;
    }
    right->left = node;
    node->parent = right;
    return right;
}

struct node *rotateRight(struct node *node) {
    struct node *left = node->left;
    node->left = left->right;
    if (node->left != NULL) {
        node->left->parent = node;
    }
    left->parent = node->parent;
    if (node->parent == NULL) {
        return left;
    }
    if (node == node->parent->left) {
        node->parent->left = left;
    } else {
        node->parent->right = left;
    }
    left->right = node;
    node->parent = left;
    return left;
}

struct node *findMin(struct node *node) {
    if (node == NULL) {
        return NULL;
    }

    while (node->left != NULL) {
        node = node->left;
    }

    return node;
}

struct node *deleteNode(struct node *root, int data) {
    if (root == NULL) {
        return root;
    }

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        if (root->left == NULL || root->right == NULL) {
            struct node *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }

            free(temp);
        } else {
            struct node *temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL) {
        return root;
    }

    if (root->left != NULL && root->left->color == RED &&
        root->right != NULL && root->right->color == RED) {
        root->color = RED;
        root->left->color = BLACK;
        root->right->color = BLACK;
    }

    if (root->left != NULL && root->left->color == RED &&
        root->left->left != NULL && root->left->left->color == RED) {
        root = rotateRight(root);
    }

    if (root->right != NULL && root->right->color == RED &&
        root->right->right != NULL && root->right->right->color == RED) {
        root = rotateLeft(root);
    }

    if (root->left != NULL && root->left->color == RED &&
        root->right != NULL && root->right->color == RED) {
        root->color = RED;
        root->left->color = BLACK;
        root->right->color = BLACK;
    }

    return root;
}

struct node *search(struct node *root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return search(root->left, data);
    } else {
        return search(root->right, data);
    }
}

void printTree(struct node *node, int space) {
    if (node == NULL) {
        return;
    }
    space += 10;
    printTree(node->right, space);
    printf("\n");
    for (int i = 10; i < space; i++){
        printf(" ");
    }
    printf("%d%c\n", node->data, node->color == RED ? 'R' : 'B');
    printTree(node->left, space);
}



int main() {
    struct node *root = NULL;
    int choice, data;

    while (1) {
        printf("\nRed-Black Tree Operations:\n");
        printf("1. Insert a node\n");
        printf("2. Delete a node\n");
        printf("3. Search for a node\n");
        printf("4. Print the tree\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to be inserted: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;

            case 2:
                printf("Enter the value to be deleted: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                break;

            case 3:
                printf("Enter the value to be searched: ");
                scanf("%d", &data);
                if (search(root, data)) {
                    printf("Node with value %d found in the tree.\n", data);
                } else {
                    printf("Node with value %d not found in the tree.\n", data);
                }
                break;

            case 4:
                printf("Red-Black Tree:\n");
                printTree(root, 0);
                break;

            case 5:
                printf("Exiting program...\n");
                exit(0);
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
