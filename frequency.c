#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LETTERS 26
#define MAX_WORDS 250
#define WORD 30
#define LINE 250

int wordCount = 0;
int letterCount = 0;

typedef struct node {
    char letter;
    struct node *children[NUM_LETTERS];
    int endOfWord;
    int endOfWordCount;
} node;

node *rootNode;
node *newNode;

char letter_to_lower(char c);

void insert_to_trie(char c);

void print_trie(node *Node, char *String);

void print_trie_r(node *Node, char *String);


int main(int argc, char **argv) {

    char c;
    int i;
    newNode = (node *) malloc(sizeof(node));
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

    char *String = (char *) malloc(sizeof(char));
    if (argc >1){
    	if (!strcmp(argv[1],"r")){
    	print_trie_r(rootNode, String);	
    	}

    }
    else{
        print_trie (rootNode, String);
    }
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
    if (c == '~')
        return;

    if (c == ' ') {
        if (newNode->endOfWord) {
            newNode->endOfWordCount += 1;
        } else if (newNode != rootNode) {
            newNode->endOfWord = 1;
            newNode->endOfWordCount += 1;
        }
        newNode = rootNode;
        return;
    }
    if (newNode->children[numOfchar] != NULL) {
        newNode = newNode->children[numOfchar];

    } else {
        node *Node = (node *) malloc(sizeof(node));
        Node->letter = c;
        int i;
        for (i = 0; i <= NUM_LETTERS; ++i) {
            Node->children[i] = NULL;
        }
        newNode->children[numOfchar] = Node;
        Node->endOfWord = 0;
        Node->endOfWordCount = 0;
        newNode = Node;
    }
}

void print_trie(node *Node, char *String) {
    int j;

    if (Node == NULL) {
        return;
    }
    for (j = 0; j < NUM_LETTERS; ++j) {
        if (Node->children[j] != NULL) {

            String = (char *) realloc(String, sizeof(char) * (letterCount + 1));
            *(String + letterCount) = Node->children[j]->letter;
            letterCount += 1;
            if (Node->children[j]->endOfWord) {
                printf("%.*s\t%d\n", letterCount, String, Node->children[j]->endOfWordCount);
                Node->children[j]->endOfWord = 0;
                char *newString = (char *) malloc(sizeof(char) * (letterCount - 1));
                //strcpy(newString,String);
                memcpy(newString, String, letterCount - 1);
                String = "\0";

                //String = (char *)realloc(sizeof(char)*(letterCount+1));
                print_trie(Node->children[j], newString);
                letterCount -= 1;
            } else {
                print_trie(Node->children[j], String);
                letterCount -= 1;
            }
        }
    }

}

void print_trie_r(node *Node, char *String) {
    int j;

    if (Node == NULL) {
        return;
    }
    for (j = NUM_LETTERS - 1; j >= 0; --j) {
        if (Node->children[j] != NULL) {

            String = (char *) realloc(String, sizeof(char) * (letterCount + 1));
            *(String + letterCount) = Node->children[j]->letter;
            letterCount += 1;
            if (Node->children[j]->endOfWord) {
                printf("%.*s\t%d\n", letterCount, String, Node->children[j]->endOfWordCount);
                Node->children[j]->endOfWord = 0;
                char *newString = (char *) malloc(sizeof(char) * (letterCount - 1));
                //strcpy(newString,String);
                memcpy(newString, String, letterCount - 1);
                String = "\0";

                //String = (char *)realloc(sizeof(char)*(letterCount+1));
                print_trie_r(Node->children[j], newString);
                letterCount -= 1;
            } else {
                print_trie_r(Node->children[j], String);
                letterCount -= 1;
            }
        }
    }

}


