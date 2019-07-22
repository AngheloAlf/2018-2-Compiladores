#ifndef TREE_H
#define TREE_H

typedef char* node_value;

typedef struct node{
    struct node *left, *right, *root;
    node_value value;
} Node;

Node *Tree_init(node_value value);
void Tree_set_left(Node *node, node_value value);
void Tree_set_right(Node *node, node_value value);

void Tree_free(Node *node);

Node *tree_instance;

#endif /* TREE_H */