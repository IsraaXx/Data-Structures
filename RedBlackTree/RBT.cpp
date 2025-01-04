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
                if (s->left->color == "BLACK" ) {
                    s->color = "RED";
                    x = x->parent;
                } else {
                    if (s->right->color == "BLACK" ) {
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

    void rep_parent(Node* u, Node* v) {
        if (u->parent == nullptr) {
            Root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void DeleteNode(Node* x,int value){
        Node* pNode = x;
        while (pNode != NIL) {
            if (pNode->data == value)
                break;
             else if (value < pNode->data)
                pNode = pNode->left;
             else
                pNode = pNode->right;
        }
        if (pNode == NIL) {
            return; }
        Node *y = pNode;
        string yColor = y->color;
        Node *n; /// x
        if (pNode->left == NIL) {
            n = pNode->right;
            rep_parent(pNode, n);
        } else if (pNode->right == NIL) {
            n = pNode->left;
            rep_parent(pNode, n);
        } else {
            y = successor(pNode->right);
            yColor = y->color;
            n = y->right;
            if (y->parent == pNode) {
                n->parent = y;
            } else {
                rep_parent(y, y->right);
                y->right = pNode->right;
                y->right->parent = y;
            }
            rep_parent(pNode, y);
            y->left = pNode->left;
            y->left->parent = y;
            y->color = pNode->color;
        }
        delete pNode;
        if (yColor == "BLACK") {
            fixDelete(n);
        }
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
        DeleteNode(Root, data);
    }

    void Inorder(){
        InorderHelper(Root);}

};
int main() {
    RedBlackTree r;
    r.insert(10);
    r.insert(5);
    r.insert(1);
    r.insert(7);
    r.insert(20);
    r.insert(15);
    r.insert(30);
    r.insert(25);
    r.insert(40);
    cout<<"Inorder Traversal of the tree after Insertion:\n";
    r.Inorder();
    cout<<"\n";
    cout<<"\n";
    r.deleteValue(15);
    cout<<"Inorder Traversal of the tree after Deletion:\n";
    r.Inorder();
}

