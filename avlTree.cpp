#include <iostream>
#include <vector>
#include "avlTree.h"
#include <queue>
using namespace std;

unsigned char TgetHeight(Node* node) {
    if (node == nullptr) return 0;
    return node->height;
}

int TgetBalanceFactor(Node* node) {
    if (node == nullptr) return 0;
    return TgetHeight(node->left) - TgetHeight(node->right);
}

void fixHeight(Node* node) {
    unsigned char hL = TgetHeight(node->left);
    unsigned char hR = TgetHeight(node->right);
    if (hL > hR) node->height = hL + 1;
    else node->height = hR + 1;
}

Node* TrotateRight(Node* node){
    Node* tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;

    fixHeight(node);
    fixHeight(tmp);
    return tmp;
}

Node* TrotateLeft(Node* node) {
    Node* tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;

    fixHeight(node);
    fixHeight(tmp);
    return tmp;
}

Node* Tinsert(Node* node, int key) {
    if (node == nullptr) return new Node(key);
    if (key < node->key) node->left = Tinsert(node->left, key);
    else if (key > node->key) node->right = Tinsert(node->right, key);
    else return node;

    fixHeight(node);

    if (TgetBalanceFactor(node) == 2){
        if (TgetBalanceFactor(node->left) >= 0) {
            return TrotateRight(node);}
        else {
            node->left = TrotateLeft(node->left);
            return TrotateRight(node);}  
    }

    if (TgetBalanceFactor(node) == -2) {
        if (TgetBalanceFactor(node->right) <= 0) {
            return TrotateLeft(node);}
        else {
            node->right = TrotateRight(node->right);
            return TrotateLeft(node);}
    }

    return node;
}

bool Tfind(Node* node, int key){
    if (node == nullptr) return false;
    if (key == node->key) return true;
    if (key < node->key) return Tfind(node->left, key);
    return Tfind(node->right, key);
}

Node* findMin(Node* node) {
    if (node == nullptr) return nullptr;
    if (node->left == nullptr) return node;
    return findMin(node->left);
}

Node* Tremove(Node* node, int key) {
    if (node == nullptr) return nullptr;

    if (key < node->key) node->left = Tremove(node->left, key);
    else if (key > node->key) node->right = Tremove(node->right, key);
    else {
        if (node->left == nullptr) {
            Node* tmp = node->right;
            delete node;
            return tmp;}
        else if (node->right == nullptr) {
            Node* tmp = node->left;
            delete node;
            return tmp;}
        Node* min = findMin(node->right);
        node->key = min->key;
        node->right = Tremove(node->right, min->key);
    }

    fixHeight(node);
    
    if (TgetBalanceFactor(node) == 2) {
        if (TgetBalanceFactor(node->left) >= 0) {
            return TrotateRight(node);}
        else {
            node->left = TrotateLeft(node->left);
            return TrotateRight(node);}
    }
    if (TgetBalanceFactor(node) == -2) {
        if (TgetBalanceFactor(node->right) <= 0) {
            return TrotateLeft(node);}
        else {
            node->right = TrotateRight(node->right);
            return  TrotateLeft(node);}
    }
    return node;
}

void inorder(Node* node) {
    if (node == nullptr) return;
    inorder(node->left);
    cout << node->key << " ";
    inorder(node->right);
}

/*void preorder(Node* node) {
    if (node == nullptr) return;
    cout << node->key << " ";
    preorder(node->left);
    preorder(node->right);
}*/

void preorder(Node* node, vector<int>& result) {
    if (node == nullptr) return;
    result.push_back(node->key);
    preorder(node->left, result);
    preorder(node->right, result);
}

void postorder(Node* node, vector<int>& result) {
    if (node == nullptr) return;
    postorder(node->left, result);
    preorder(node->right, result);    
    result.push_back(node->key);
}

void bfs(Node* root, vector<int>& result) {
    if (root == nullptr) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        result.push_back(current->key);
        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
    }
}

void Tclear(Node* node) {
    if (node == nullptr) return;
    Tclear(node->left);
    Tclear(node->right);
    delete node;
}
