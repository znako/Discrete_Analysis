#include <iostream>

using namespace std;

struct Node{
    int key;
    Node *left;
    Node *right;
    Node(int k) {key = k; left = right = nullptr;}
};
Node* find(Node *p, int k){
    while(p){
        if(k < p->key) p = p->left;
        else if(k > p->key) p = p->right;
        else return p;
    }
    return nullptr;
}

Node* insert(Node *p, int k){
    if (!p) return new Node(k);
    if(k < p->key) p->left = insert(p->left, k);
    else if(k > p->key) p->right = insert(p->right, k);

    return p;
}
Node* findMin(Node* p){
    while(p && p->left) p = p->left;
    return p;
}
Node* remove(Node*p, int k){
    while(p && p->key != k){
        if(k < p->key) p = p->left;
        else if (k > p->key) p =p->right;
    }
    if(p == nullptr) return nullptr;
    if(p->left && p->right){
        auto next = findMin(p->right);
        p->key = next->key;
        p->right = remove(p->right, next->key);
    }
    else if(p->left){
        auto tmp = p;
        p = p->left;
        delete tmp;
    }
     else {
        auto tmp = p;
        p = p->right;
        delete tmp;
    }
    return p;
}
void rotateRight(Node* x){
    if(!x) return;
    Node* y = x->left;

    if(!y) return;

    x->left = y->right;
    y->right = x;
}
void rotateLeft(Node* y){
    if(!y) return;
    Node* x = y->right;

    if( x == nullptr) return;
    y->right = x ->left;
    x->left = y;
}

int main()
{
    Node* root = nullptr;

    root = insert(root, 10);
    root = insert(root, 7);
    root = insert(root, 12);
    root = insert(root, 20);
    root = insert(root, 11);
    root = insert(root, 6);
    // root = remove(root, 6);
    cout << root->key << endl;
    return 0;
}
