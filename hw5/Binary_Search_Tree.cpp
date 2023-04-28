#include <iostream>

using namespace std;

struct node{
    int key;
    node* parent;
    node* left;
    node* right;
    node* parent;
};

//method (.h file)
node* createNode(int key);
node* insert(node* root, int key);
node* search(node* x, int key);
node* maximum(node* x);
node* minimum(node* x);


int main(){
    
    cout << "this is the last line!" << endl;
    return 0;
}

node* createNode(int key){
    node* newNode = new node();
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

node* insert(node* root, int key){
    // if tree is empty initially
    if(root == NULL){
        root = createNode(key);
        return root;
    }
    // if key < root.key, put into left subtree
    if(key < root->key){
        node* leftChild = insert(root->left, key);
        root->left = leftChild;
        leftChild->parent = root;
    }
    // if key >= root.key, put into right subtree
    else{
        node* rightChild = insert(root->right, key);
        root->right = rightChild;
        rightChild = root;
    }
    return root;
}

node* search(node* x, int key){
    if(x == NULL || key == x->key){
        return x;
    }
    if(key > x->key){
        return search(x->right, key);
    }
    else{
        return search(x->left, key);
    }
}

node* maximum(node* x){
    while(x->right != NULL){
        x = x->right;
    }
    return x;
}

node* minimum(node* x){
    while(x->left != NULL){
        x = x->left;
    }
    return x;
}