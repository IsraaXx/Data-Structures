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
        Node* y = x->left; //
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
            cout<<node->data<<" "<<node->color<<" ";
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
    void Inorder(){
        InorderHelper(Root);}

};
int main() {
    RedBlackTree r ;
    r.insert(4);
    r.insert(22);
    r.insert(31);
    r.insert(6);
    r.insert(3);
    r.Inorder();
}
