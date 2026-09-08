#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
};

struct Node* createNode(char ch, int freq) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->ch = ch;
    newNode->freq = freq;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void findMin(struct Node* nodes[], int size, int *min1, int *min2) {
    int i;

    *min1 = -1;
    *min2 = -1;

    for (i = 0; i < size; i++) {
        if (nodes[i] == NULL)
            continue;

        if (*min1 == -1 || nodes[i]->freq < nodes[*min1]->freq) {
            *min2 = *min1;
            *min1 = i;
        }
        else if (*min2 == -1 || nodes[i]->freq < nodes[*min2]->freq) {
            *min2 = i;
        }
    }
}

void generateCodes(struct Node* root, char code[], int depth) {
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL) {
        code[depth] = '\0';
        printf("%c : %s\n", root->ch, code);
        return;
    }

    code[depth] = '0';
    generateCodes(root->left, code, depth + 1);

    code[depth] = '1';
    generateCodes(root->right, code, depth + 1);
}

int main() {
    char str[MAX];
    int freq[256] = {0};
    int i, count = 0;

    printf("Enter a string: ");
    scanf("%s", str);

    for (i = 0; str[i] != '\0'; i++)
        freq[(unsigned char)str[i]]++;

    struct Node* nodes[MAX];

    for (i = 0; i < 256; i++) {
        if (freq[i] > 0)
            nodes[count++] = createNode((char)i, freq[i]);
    }

    int size = count;

    while (size > 1) {
        int min1, min2;

        findMin(nodes, size, &min1, &min2);

        struct Node* left = nodes[min1];
        struct Node* right = nodes[min2];

        struct Node* parent =
            createNode('$', left->freq + right->freq);

        parent->left = left;
        parent->right = right;

        nodes[min1] = parent;
        nodes[min2] = nodes[size - 1];

        size--;
    }

    char code[MAX];

    printf("\nHuffman Codes:\n");
    generateCodes(nodes[0], code, 0);

    return 0;
}