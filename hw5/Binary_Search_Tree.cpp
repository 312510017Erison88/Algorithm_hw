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
node* successor(node* x);
node* predecessor(node* x);
void deleteTree(node* root);
node* deleteNode(node* root, int key);
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

    // test successor and predecessor
    node* succ = successor(myfind);
    cout << "40's successor is :";
    printNode(succ);
    cout << endl;

    node* pre = predecessor(myfind);
    cout << "40's predecessor is :";
    printNode(pre);
    cout << endl;

    deleteTree(root);

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
        rightChild->parent = root;
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

node* successor(node* x){
    if(x->right != NULL){
        return successor(x->right);
    }
    else{
        node* y = x->parent;
        while(y != NULL && x == y->right){
            x = y;
            y = y->parent;
        }
        return y;
    }
}

node* predecessor(node* x){
    if(x->left != NULL){
        return predecessor(x->left);
    }
    else{
        node* y = x->parent;
        while(y != NULL && x == y->left){
            x = y;
            y = y->parent;
        }
        return y;
    }
}

// delete the entire tree
void deleteTree(node* root){
    if (root == NULL){
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

//delete a node with given key
node* deleteNode(node* root, int key){
    if(root == NULL){
        return root;
    }
    // find the node to be deleted
    if(key < root->key){
        root->left = deleteNode(root->left, key);
    }
    else if(key > root->key){
        root->right = deleteNode(root->right, key);
    }
    else{
        // case 1: node has no children
        if(root->left == NULL && root->right == NULL){
            delete root;
            root = NULL;
        }
        // case 2: node has one child
        else if(root->left == NULL){
            node* temp = root;
            root = root->right;
            delete temp;
        }
        else if(root->right == NULL){
            node* temp = root;
            root = root->left;
            delete temp;
        }
        // case 3: node has two children
        else{
            node* temp = minimum(root->right);  // 找到右子樹中的最小節點
            root->key = temp->key;              // 將最小節點的值複製到要被刪除的節點
            root->right = deleteNode(root->right, temp->key);       // 刪除最小節點
        }
    }
    return root;
}

void printNode(node* root){
    if(root == NULL){
        return;
    }
    printNode(root->right);
    cout << root->key << " ";
    printNode(root->left);
}



