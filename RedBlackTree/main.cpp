#include <iostream>
#include <bits/stdc++.h>
using namespace std;
// Node structure for the Red-Black Tree
struct Node {
    int data;
    string color;
    Node *left, *right, *parent;

    Node(int data) : data(data), color("RED"), left(nullptr), right(nullptr), parent(nullptr){}
};

class RedBlackTree{
    private:
    Node* Root;
    Node* NIL ;
    void fixInsert(Node* x){
        while (x!= Root && x->parent->color=="RED"){
            if(x->parent == x->parent->parent->left){
                Node* uncle = x->parent->parent->right;

                if(uncle->color=="RED"){
                    x->parent->color = "BLACK";
                    uncle->color = "BLACK";
                    x->parent->parent->color = "RED";
                    x = x->parent->parent;
                }
                else{
                    if(x == x->parent->right){
                        x = x->parent;
                        LeftRotate(x);}
                    x->parent->color = "BLACK";
                    x->parent->parent->color = "RED";
                    RightRotate(x->parent->parent); }
            }
            else {
                Node* uncle = x->parent->parent->left;
                if(uncle->color=="RED"){
                    x->parent->color = "BLACK";
                    uncle->color = "BLACK";
                    x->parent->parent->color = "RED";
                    x = x->parent->parent;   }

                else {
                    if(x == x->parent->left){
                        x = x->parent;
                        RightRotate(x);}
                    x->parent->color = "BLACK";
                    x->parent->parent->color = "RED";
                    LeftRotate(x->parent->parent);  }
            }
        }
        Root->color = "BLACK";
    }

    void fixDelete(Node* x) {
        Node* s;
        while (x != Root && x->color == "BLACK") {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == "RED") {
                    s->color = "BLACK";
                    x->parent->color = "RED";
                    LeftRotate(x->parent);
                    s = x->parent->right;
                }
                if (s->left->color == "BLACK" && s->right->color == "BLACK") {
                    s->color = "RED";
                    x = x->parent;
                } else {
                    if (s->right->color == "BLACK" && s->left->color == "RED") {
                        s->left->color = "BLACK";
                        s->color = "RED";
                        RightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = "BLACK";
                    s->right->color = "BLACK";
                    LeftRotate(x->parent);
                    x = Root;
                }
            } else {
                s = x->parent->left;
                if (s->color == "RED") {
                    s->color = "BLACK";
                    x->parent->color = "RED";
                    RightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == "BLACK" && s->right->color == "BLACK") {
                    s->color = "RED";
                    x = x->parent;
                } else {
                    if (s->left->color == "BLACK"&&s->right->color == "RED") {
                        s->right->color = "BLACK";
                        s->color = "RED";
                        LeftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = "BLACK";
                    s->left->color = "BLACK";
                    RightRotate(x->parent);
                    x = Root;
                }
            }
        }
        x->color = "BLACK";
    }



    Node* deleteNode(Node *&root, int data) {
        if (root == NIL || root == nullptr) return NIL;

        if (data < root->data)
            root->left = deleteNode(root->left, data);

        else if (data > root->data)
            root->right = deleteNode(root->right, data);

        else {
            // Node to delete is found
            if (root->left == NIL) { // Only right child or no child
                Node* temp = root->right;
                if (temp != NIL)
                    temp->parent = root->parent;
                return temp; }
            else if (root->right == nullptr) { // Only left child
                Node* temp = root->left;
                if (temp != NIL)
                    temp->parent = root->parent;
                return temp; }

            // Node has two children, find the successor
            Node* temp = successor(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data); // Delete the successor
        }
        return root;
    }

    Node* predecessor(Node *&node) { // max in left subtree
        Node *ptr = node;
        while (ptr->right != NIL)
            ptr = ptr->right;

        return ptr;
    }

    Node* successor(Node *&node) { // min in right subtree
        Node *ptr = node;
        while (ptr->left != NIL)
            ptr = ptr->left;

        return ptr;
    }

    void LeftRotate(Node* x){
        Node* y = x->right;
        x->right= y->left;
        if(y->left!= NIL){
            y->left->parent = x;
        }
        y->parent= x->parent;
        if(x->parent== nullptr){
            Root = y ;}
        else if(x == x->parent->left){
            x-> parent->left = y ;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y ;
    }
    void RightRotate(Node* x){
        Node* y = x->left;
        x->left= y->right;
        if(y->right!= NIL){
            y->right->parent = x;
        }
        y->parent = x->parent;
        if(x->parent== nullptr){
            Root = y ;}
        else if(x == x->parent->right){
            x-> parent->right = y ;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y ;
    }

    void InorderHelper(Node* node){
        if(node != NIL){
            InorderHelper(node->left);
            cout<<"( "<<node->data<<" -> "<<node->color<<" ) ";
            InorderHelper(node->right);
        }
    }

public:
    RedBlackTree(){
        NIL = new Node (0);
        Root = NIL;
        NIL->color = "BLACK";
        NIL->left = NIL->right = NIL;
    }
    void insert(int data){
        Node* x = new Node(data);
        x->left = NIL; x->right=NIL;
        Node* parent = nullptr;
        Node* current = Root;
        while(current!= NIL){
            parent = current;
            if(x->data < current->data)
                current = current->left;
            else
                current = current->right; }
        x->parent = parent;
        if(parent== nullptr){
            Root = x ;
            x->color = "BLACK";
            return; }
        else if( x->data < parent->data){
            parent->left = x; }
        else {
            parent->right = x; }

        if (x->parent->parent == nullptr) {
            return; }
        fixInsert(x);  }

    void deleteValue(int data) {
        Node* node = deleteNode(Root, data);
        if (node == NIL) return;
        if (node->color == "BLACK") {
            fixDelete(node);
        }
    }

    void Inorder(){
        InorderHelper(Root);}

};
int main() {
    RedBlackTree r;
    r.insert(4);
    r.insert(22);
    r.insert(31);
    r.insert(6);
    r.insert(3);
    cout<<"Inorder Traversal of the tree after Insertion:\n";
    r.Inorder();
    cout<<"\n";
    cout<<"\n";
    r.deleteValue(4);
    cout<<"Inorder Traversal of the tree after Deletion:\n";
    r.Inorder();
}
