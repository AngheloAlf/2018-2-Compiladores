#include <stdlib.h>

#include "tree.h"

Node *Tree_init(node_value value){
    Node *root = malloc(sizeof(Node));
    root->left = NULL;
    root->right = NULL;
    root->root = NULL;
    root->value = value;
    return root;
}

void Tree_set_left(Node *node, node_value value){
    // Maybe free left?
    node->left = Tree_init(value);
    node->left->root = node;
}
void Tree_set_right(Node *node, node_value value){
    // Maybe free left?
    node->right = Tree_init(value);
    node->right->root = node;
}

void Tree_free(Node *node){
    // TODO
}
