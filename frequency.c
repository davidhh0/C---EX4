#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LETTERS 26
int letterCount = 0;

typedef struct node {
    char letter;
    struct node *children[NUM_LETTERS];
    int endOfWord;
    int endOfWordCount;
} node;

node *rootNode;
node *newNode;

int MAX=0;
int MAXcounterForWord=0;

char letter_to_lower(char c);

void insert_to_trie(char c);

void print_trie(node *Node, char[MAX] , int );

void print_trie_r(node *Node, char[MAX] , int);

void free_mem(node **Node);

void ifree(node *root);


int main(int argc, char **argv) {

    char c;
    int i;
    newNode = (node *) malloc(sizeof(node)*1);
    if (newNode == NULL){
    	printf("Error allocating memory! \n");
    	exit(1);
    }
    rootNode = newNode;
    
    for (i = 0; i <= NUM_LETTERS; ++i) {
        newNode->children[i] = NULL;
    }
    newNode->endOfWord = 0;
    newNode->endOfWordCount = 0;
    do {
        c = fgetc(stdin);
        if (feof(stdin) || c == '0') {
            if (newNode != rootNode) {
                if (newNode->endOfWord) {
                    newNode->endOfWordCount += 1;
                } else if (newNode != rootNode) {
                    newNode->endOfWord = 1;
                    newNode->endOfWordCount += 1;
                }
            }
            break;
        }
        c = letter_to_lower(c);
        insert_to_trie(c);
    } while (1);

    char David[MAX];


    if (argc > 1) {
        if (!strcmp(argv[1], "r")) {
            print_trie_r(rootNode, David,0);
        }

    } else {
        print_trie(rootNode, David , 0);
    }


    free_mem(&rootNode);



    return 0;


}

char letter_to_lower(char c) {
    if (c < 123 && c > 96) {
        return c;
    }
    if (c > 64 && c < 91) {
        return c + 32;
    }
    if (c == ' ' || c == '\n') {
        return ' ';
    }


    return '~';
}


void insert_to_trie(char c) {

    int numOfchar = c - 97;
    if (c == '~') {
        return;
    }
    if (c == ' ') {
        if (newNode->endOfWord) {
            newNode->endOfWordCount += 1;
        } else if (newNode != rootNode) {
            newNode->endOfWord = 1;
            newNode->endOfWordCount += 1;
        }
        if(MAXcounterForWord > MAX){
            MAX = MAXcounterForWord;
        }
        MAXcounterForWord=0;
        newNode = rootNode;
        return;
    }
    if (newNode->children[numOfchar] != NULL) {
        newNode = newNode->children[numOfchar];
        MAXcounterForWord++;

    } else {
        node *Node = (node *) malloc(sizeof(node));
        if (Node==NULL){
            printf("Error allocating memory! \n");
            exit(1);
        }
        Node->letter = c;
        int i;
        for (i = 0; i <= NUM_LETTERS; ++i) {
            Node->children[i] = NULL;
        }
        newNode->children[numOfchar] = Node;
        Node->endOfWord = 0;
        Node->endOfWordCount = 0;
        newNode = Node;
        MAXcounterForWord++;
    }
}

void print_trie(node *Node, char David[MAX],int index) {
    int j;
    if (Node == NULL) {
        return;
    }
    for (j = 0; j < NUM_LETTERS; ++j) {
        if (Node->children[j] != NULL) {
            David[index] = Node->children[j]->letter;
            if (Node->children[j]->endOfWord) {
                David[index+1] = '\0';
                printf("%s %d\n", David, Node->children[j]->endOfWordCount);
                Node->children[j]->endOfWord = 0;
                print_trie(Node->children[j], David , (index+1));
            } else {
                print_trie(Node->children[j], David, index+1);
            }
        }
    }

}

void print_trie_r(node *Node, char David[MAX],int index) {
    int j;

    if (Node == NULL) {
        return;
    }
    for (j = NUM_LETTERS - 1; j >= 0; --j) {
        if (Node->children[j] != NULL) {
            David[index] = Node->children[j]->letter;
            if (Node->children[j]->endOfWord) {
                David[index+1] = '\0';
                printf("%s %d\n", David, Node->children[j]->endOfWordCount);
                Node->children[j]->endOfWord = 0;
                print_trie_r(Node->children[j], David , (index+1));
            } else {
                print_trie_r(Node->children[j], David, index+1);
            }
        }
    }

}

void ifree(node *root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < NUM_LETTERS; ++i) {
            if (root->children[i] != NULL) {
                ifree(root->children[i]);
                root->children[i] = NULL;
                free(root->children[i]);
            }
        }
        free(root);


    }


}

void free_mem(node **Node) {
    if (*Node != NULL) {
        for (int i = 0; i < NUM_LETTERS; i++) {
            if ((*Node)->children[i] != NULL) {
                free_mem(&((*Node)->children[i]));
            } else {
                continue;
            }
        }
        free(*Node);
    }

}

