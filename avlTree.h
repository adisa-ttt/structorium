#pragma once
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    unsigned char height; 
    Node(int k) { key = k; left = right = nullptr; height = 1;}
};

unsigned char TgetHeight(Node* node);
int TgetBalanceFactor(Node* node);
void fixHeight(Node* node);
Node* TrotateRight(Node* node);
Node* TrotateLeft(Node* node);
Node* Tinsert(Node* node, int key);
bool Tfind(Node* node, int key);
Node* findMin(Node* node);
Node* Tremove(Node* node, int key);
void inorder(Node* node);
void preorder(Node* node, vector<int>& result);
void postorder(Node* node, vector<int>& result);
void bfs(Node* root, vector<int>& result);
void Tclear(Node* node);