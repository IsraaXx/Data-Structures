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
    TreeNode(T item) : data(item), left(nullptr), right(nullptr) {}
};
template <class T>
class BinarySearchTree {
private:
    TreeNode<T>* root;

    void addNode(TreeNode<T>*& node, T item){
        if (node == nullptr) {
            node = new TreeNode<T>(item);
        } else if (item < node->data) {
            addNode(node->left, item);
        } else {
            addNode(node->right, item);
        }
    }
    TreeNode<T>* DeleteNode(TreeNode<T>* node, T item){
        // Base case
        if (root == NULL)
            return root;
        // If the key to be deleted is smaller than the root's key,
        // then it lies in the left subtree
        if (k < root->data) {
            root->left = DeleteNode(root->left, k);
            return root;
        }
            // If the key to be deleted is greater than the root's key,
            // then it lies in the right subtree
        else if (root->data < k) {
            root->right = DeleteNode(root->right, k);
            return root;
        }
        // If key is same as root's key, then this is the node to be deleted
        // Node with only one child or no child
        if (root->left == NULL) {
            TreeNode<T>* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            TreeNode<T>* temp = root->left;
            delete root;
            return temp;
        }
        // Node with two children: Get the inorder successor (smallest
        // in the right subtree)
        TreeNode<T>* succParent = root;
        TreeNode<T>* succ = root->right;
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }
        // Copy the inorder successor's content to this node
        root->data = succ->data;
        // Delete the inorder successor
        if (succParent->left == succ)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;

        delete succ;
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

    TreeNode<T>* searchNode(TreeNode<T>* node, const T& item) {
        if (node == nullptr || node->data == item)
            return node;
        if (item < node->data)
            return searchNode(node->left, item);
        return searchNode(node->right, item);
    }
public:
    BinarySearchTree(): root(nullptr) {}
    void addItem(T item){
        addNode(root, item);
    }
    bool searchItem(const T& item) {
        return searchNode(root, item) != nullptr;
    }
    void deleteItem(T& item) {
        root = DeleteNode(root, item);
    }
    void displayPreorder() {
        cout << "Items by price in ascending order:" << "\n";
        displayPreorder(root);
    }
    void displayInorder(){
        cout << "Items by name in ascending order:" << "\n";
        displayInorder(root);
    }
    void displayPostorder(){
        cout<<"Displaying Items:"<<"\n";
        displayPostorder(root);
    }

};



int main() {
    BinarySearchTree<int> bst;

    cout << "Binary Search Tree Operations:\n";
    cout << "1. Insert\n";
    cout << "2. Delete\n";
    cout << "3. Search\n";
    cout << "4. Display Preorder\n";
    cout << "5. Display Inorder\n";
    cout << "6. Display Postorder\n";
    cout << "7. Exit\n";

    int choice, value;

    while (true) {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                bst.addItem(value);
                cout << "Value inserted.\n";
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                bst.deleteItem(value);
                cout << "Value deleted (if it existed).\n";
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                if (bst.searchItem(value))
                    cout << "Value found in the tree.\n";
                else
                    cout << "Value not found in the tree.\n";
                break;
            case 4:
                cout << "Preorder traversal:\n";
                bst.displayPreorder();
                cout << "\n";
                break;
            case 5:
                cout << "Inorder traversal:\n";
                bst.displayInorder();
                cout << "\n";
                break;
            case 6:
                cout << "Postorder traversal:\n";
                bst.displayPostorder();
                cout << "\n";
                break;
            case 7:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

