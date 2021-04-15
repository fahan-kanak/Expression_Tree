/* 
 * File:   tree.c
 * Author: farhan
 *
 * Created on April 14, 2021, 3:55 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct foo {
    char *ch;
    struct foo *lc;
    struct foo *rc;
};

typedef struct foo Node;

struct foo_2 {
    Node *node;
    struct foo_2 *next;
};

typedef struct foo_2 Stack;

void push(Node *n, Stack *head) {
    if (head->next == NULL) {
        head->next = (Stack *)malloc(sizeof(Stack));
        head->next->node = n;
        head->next->next = NULL;
        return;
    }
    push(n, head->next);
}

Node* pop(Stack *head) {
    if (head->next->next == NULL) {
        Node *tmp = head->next->node;
        head->next = NULL;
        return tmp;
    }
    return pop(head->next);
}

int isOperator(char *ch) {
    switch (*ch) {
        case '+':
        case '-':
        case '*':
        case '/':        
            return 1;
        default:
            return 0;
    }
}

void inorder(Node *root) {
    if (!root) return;
    inorder(root->lc);
    printf("%s ", root->ch);
    inorder(root->rc);
}

void preorder(Node *root) {
    if (!root) return;
    printf("%s ", root->ch);
    preorder(root->lc);
    preorder(root->rc);
}

void postorder(Node *root) {
    if (!root) return;
    postorder(root->lc);
    postorder(root->rc);
    printf("%s ", root->ch);
}

int evaluate(Node *root) {
    if (root) {
        if (!isOperator(root->ch)) return atoi(root->ch);
        int a = evaluate(root->lc);
        int b = evaluate(root->rc);        
        switch (*root->ch) {
            case '+':
                return a+b;                
            case '-':
                return a-b;
            case '*':
                return a*b;
            case '/':
                return a/b;
        }
    }
}

int main(int argc, char** argv) {
    char postfix[100], delim[2] = " ";
    printf("Enter (postfix) expression: ");
    scanf("%[^\n]", postfix);
    Stack *head = NULL;
    char *token = strtok(postfix, delim);
    while (token) {        
        if (isOperator(token)) {
            Node *a, *b;
            if (head) {                
                if (head->next == NULL) {
                    a = head->node;
                    head = NULL;
                }
                else a = pop(head);
            } else {
                printf("Trouble!!!\n");
                goto exit;
            }
            if (head) {
                if (head->next == NULL) {
                    b = head->node;
                    head = NULL;
                }
                else b = pop(head);
            } else {
                printf("Trouble!!!\n");
                goto exit;
            }
            Node *n = (Node *)malloc(sizeof(Node));
                n->ch = token;
                n->rc = a;
                n->lc = b;
                if (head == NULL) {
                    head = (Stack *)malloc(sizeof(Stack));
                    head->node = n;
                    head->next = NULL;
                } 
                else push(n, head);            
        }
        else {
            Node *ptr = (Node *)malloc(sizeof(Node));
            ptr->ch = token;
            ptr->lc = NULL;
            ptr->rc = NULL;
            if (head == NULL) {
                head = (Stack *)malloc(sizeof(Stack));
                head->node = ptr;
                head->next = NULL;
            }
            else push(ptr, head);
        }
        token = strtok(NULL, delim);
    }
    printf("The inorder traversal is: ");
    inorder(head->node);
    printf("\nThe preorder traversal is: ");
    preorder(head->node);
    printf("\nThe postorder traversal is: ");
    postorder(head->node);
    printf("\nThe result is %d\n", evaluate(head->node));

    exit: return 0;
}

