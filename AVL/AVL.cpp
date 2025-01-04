#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
template <class T>
class TreeNode {
public:
    T data;
    TreeNode *left;
    TreeNode *right;
    int height;
    TreeNode(T item) : data(item), left(nullptr), right(nullptr) , height(1) {}
};
template <class T>
class AVL{
private:
TreeNode<T> *root;
int height(TreeNode<T> *node) {
    if (node == nullptr)
        return 0;
    return node->height;
}
int balanceFactor(TreeNode<T>*node){
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}
TreeNode<T> *rightRotate(TreeNode<T> *node){
    TreeNode<T> *leftChild = node->left;
    TreeNode<T> *rightOfleftSub = leftChild->right;
    leftChild->right = node;
    node->left = rightOfleftSub;
    node->height = max(height(node->left), height(node->right)) + 1;
    leftChild->height = max(height(leftChild->left), height(leftChild->right)) + 1;

    return leftChild;
}
TreeNode<T> *leftRotate(TreeNode<T> *node){
        TreeNode<T>* rightChild = node->right;
        TreeNode<T>* leftChildOfSub = rightChild->left;
        rightChild->left = node;
        node->right = leftChildOfSub;
        node->height = max(height(node->left), height(node->right)) + 1;
        rightChild->height = max(height(rightChild->left), height(rightChild->right)) + 1;

        return rightChild;
    }
TreeNode<T> *additem(TreeNode<T> *node, T item){
    if (node == nullptr)
        return new TreeNode<T>(item);

    if (item < node->data)
        node->left = additem(node->left, item);
    else
        node->right = additem(node->right, item);
    // Update the balance factor of each node and balance the tree
    node->height = 1 + std::max(height(node->left), height(node->right));
    int balance = balanceFactor(node);
    if (balance > 1 && item < node->left->data)
        return rightRotate(node);

    if (balance < -1 && node->right->data < item)
        return leftRotate(node);

    if (balance > 1 && node->left->data < item) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && item < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}
TreeNode<T> *minValueNode(TreeNode<T> *node){
    TreeNode<T> *current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}
TreeNode<T> *deletenode(TreeNode<T> *root, T key) {
    if (root == nullptr)
        return root;

    if (key < root->data)
        root->left = deletenode(root->left, key);
    else if (root->data < key)
        root->right = deletenode(root->right, key);
    else {
        // If the node has one or no child
        if (root->left == nullptr || root->right == nullptr) {
            TreeNode<T>* temp = (root->left == nullptr) ? root->right : root->left;
            delete root;
            return temp;
        }
        // If the node has two children
        TreeNode<T>* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deletenode(root->right, temp->data);
    }
    // Update height of the current node
    root->height = 1 + max(height(root->left), height(root->right));

    // Get the balance factor of this node
    int balancevalue = balanceFactor (root);

    // Perform rotations if needed
    if (balancevalue > 1) {
        if (balanceFactor(root->left) >= 0)
            return rightRotate(root);
        else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balancevalue < -1) {
        if (balanceFactor(root->right) <= 0)
            return leftRotate(root);
        else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

    void displayPreorder(TreeNode<T>* node){
        if (node != nullptr) {
            cout<<node->data;
            displayPreorder(node->left);
            displayPreorder(node->right);
        }
    }
    void displayInorder(TreeNode<T>* node) {
        if (node != nullptr) {
            displayInorder(node->left);
            cout << node->data;
            displayInorder(node->right);
        }
    }
    void displayPostorder(TreeNode<T>* node){
        if (node != nullptr) {
            displayPostorder(node->left);
            displayPostorder(node->right);
            cout<<node->data;
        }
    }
public:
 AVL(): root(nullptr) {}
void insertitem(T item){
    root = additem(root, item);
}
void deletenode(T &item) {
    root = deletenode(root, item);

}
    void displayPreorder() {
        cout << "Items in ascending order:" << "\n";
        displayPreorder(root);
    }
    void displayInorder(){
        cout << "Items in ascending order:" << "\n";
        displayInorder(root);
    }
    void displayPostorder(){
        cout<<"Displaying Items:"<<"\n";
        displayPostorder(root);
    }
};


int main() {
    AVL<int> avlTree;
    
    avlTree.insertitem(50);
    avlTree.insertitem(30);
    avlTree.insertitem(70);
    avlTree.insertitem(20);
    avlTree.insertitem(40);
    avlTree.insertitem(60);
    avlTree.insertitem(80);
  
    cout << "Inorder Traversal:" << "\n";
    avlTree.displayInorder();
    cout << "\n";

    int valueToDelete = 70;
    cout << "Deleting value " << valueToDelete << " from the AVL tree." << "\n";
    avlTree.deletenode(valueToDelete);

    cout << "Inorder Traversal after deletion:" << "\n";
    avlTree.displayInorder();
    cout << "\n";
}
