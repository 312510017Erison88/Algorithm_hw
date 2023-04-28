#include <iostream>

using namespace std;

struct node{
    int key;
    node* parent;
    node* left;
    node* right;
};

//method (.h file)
node* createNode(int key);
node* insert(node* root, int key);
node* search(node* x, int key);
node* maximum(node* x);
node* minimum(node* x);
void printNode(node* root);


int main(){
    node* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    cout << "Binary Search Tree: ";
    printNode(root);
    cout << endl;
    
    // test max and min
    node* max = maximum(root);
    node* min = minimum(root);
    cout << "Maximum is ";
    printNode(max);
    cout << endl;
    cout << "Minimum is ";
    printNode(min);
    cout << endl;

    // test searching function
    node* myfind = search(root, 40);
    cout << "What I search is: ";
    printNode(myfind);
    cout << endl; 

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

void printNode(node* root){
    if(root == NULL){
        return;
    }
    printNode(root->right);
    cout << root->key << " ";
    printNode(root->left);
}

