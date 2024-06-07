#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *left, *right, *parent;
} node;

typedef struct tree {
    struct node *root;
} tree;

node* create_node(int key) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->key = key;
    new_node->left = new_node->right = new_node->parent = NULL;
    return new_node;
}

void right_rotate(tree* t, node* x) {
    node* y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        t->root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void left_rotate(tree* t, node* x) {
    node* y = x->right;
    x->right = y->left;
    
    if (y->left != NULL)
        y->left->parent = x;
    
    y->parent = x->parent;
    
    if (x->parent == NULL)
        t->root = y;
    
    else if (x == x->parent->left)
        
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void splay(tree* t, node* x) {
    while(x->parent != NULL) {
        if(x->parent->parent == NULL) {
            if (x->parent->left == x)
                right_rotate(t, x->parent);
            else
                left_rotate(t, x->parent);
        }
        else if (x->parent->left == x && x->parent->parent->left == x->parent) {
            right_rotate(t, x->parent->parent);
            right_rotate(t, x->parent);
        }
        else if (x->parent->right == x && x->parent->parent->right == x->parent) {
            left_rotate(t, x->parent->parent);
            left_rotate(t, x->parent);
        }
        else if (x->parent->left == x && x->parent->parent->right == x->parent) {
            right_rotate(t, x->parent);
            left_rotate(t, x->parent);
        }
        else {
            left_rotate(t, x->parent);
            right_rotate(t, x->parent);
        }
    }
}

void insert(tree* t, int key) {

    node* new_node = create_node(key);
    node* y = NULL;
    node* x = t->root;

    while(x != NULL){
        y = x;
        if(new_node->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    new_node->parent = y;

    if (y == NULL){
        t->root = new_node;
    }
    else if(new_node->key < y->key) {
        y->left = new_node;
    }
    else{
        y->right = new_node;
    }

    splay(t, new_node);
}

node* search(tree* a, int key) {
    node* x = a->root;
    while (x != NULL && x->key != key) {
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    if(x != NULL)
        splay(a, x);

    return x;
}

void preorder_rec(node* root) {
    if(root != NULL) {
        printf("%d ", root->key);
        preorder_rec(root->left);
        preorder_rec(root->right);
    }
}
void preorder(tree a) {
    preorder_rec(a.root);
}

int main(){
    tree a;
    a.root = NULL;
    node *n;
    int i = 0,x;
    while(i < 5){
        scanf("%d", &x);
        i++;
        insert(&a, x);
    }
    n = search(&a, 1);
    printf("%s\n", n == a.root ? "True" : "False");
    preorder(a);
    printf("\n");
    n = search(&a, 3);
    printf("%s\n", n == a.root ? "True" : "False");
    preorder(a);

}
