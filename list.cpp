#include "list.h"
#include <string>
#include <vector>
using namespace std;

void Finit(linkedList* ll){
    ll->head = nullptr;
    ll->tail = nullptr;
}

bool Fempty(linkedList* ll){
    return ll->head == nullptr;
}

int Fsize(linkedList* ll){
    int n = 0;
    for (FNode* c = ll->head; c != nullptr; c = c->next) n++;
    return n;
}

void Fclear(linkedList* ll){
    while (ll->head != nullptr){
        FNode* popped = ll->head;
        ll->head = popped->next;
        delete popped;
    }
    ll->tail = nullptr;
}

void Fpush_front(linkedList* ll, const string& str){
    FNode* new_FNode = new FNode{str, nullptr};
    if (ll->tail == nullptr) {
        ll->head = new_FNode;
        ll->tail = new_FNode;
    } else {
        new_FNode->next = ll->head;
        ll->head = new_FNode;
    }
}

void Fpush_back(linkedList* ll, const string& str){
    FNode* new_FNode = new FNode{str, nullptr};
    if (ll->head == nullptr) {
        ll->head = new_FNode;
        ll->tail = new_FNode;
    } else {
        ll->tail->next = new_FNode;
        ll->tail = new_FNode;
    }
}

bool Fpop_front(linkedList* ll, string& out){
    if (Fempty(ll)) return false;
    FNode* popped = ll->head;
    out = popped->data;
    ll->head = ll->head->next;
    if (ll->head == nullptr) ll->tail = nullptr;
    delete popped;
    return true;
}

bool Fpop_back(linkedList* ll, string& out){
    if (Fempty(ll)) return false;
    out = ll->tail->data;
    if (ll->head == ll->tail){
        delete ll->head;
        ll->head = nullptr;
        ll->tail = nullptr;
        return true;
    }
    FNode* prev_tail = ll->head;
    while (prev_tail->next != ll->tail) prev_tail = prev_tail->next;
    delete ll->tail;
    ll->tail = prev_tail;
    ll->tail->next = nullptr;
    return true;
}

FNode* Findex(linkedList* ll, int index){
    if (index < 0 || Fempty(ll)) return nullptr;
    FNode* index_node = ll->head;
    int n = 0;
    while (n != index && index_node != nullptr){
        index_node = index_node->next;
        n++;
    }
    return index_node;         
}

bool FinsertBeforeValue(linkedList* ll, const string& value, const string& str) {
    if (Fempty(ll)) return false;
    if (ll->head->data == value) {
        Fpush_front(ll, str);
        return true;
    }

    FNode* prev = ll->head;
    FNode* curr = ll->head->next;
    while (curr != nullptr && curr->data != value) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) return false;
    prev->next = new FNode{str, curr};
    return true;
}

bool FinsertAfterValue(linkedList* ll, const string& value, const string& str) {
    if (Fempty(ll)) return false;
    FNode* curr = ll->head;
    while (curr != nullptr && curr->data != value) {
        curr = curr->next;
    }

    if (curr == nullptr) return false;
    FNode* new_node = new FNode{str, curr->next};
    curr->next = new_node;

    if (new_node->next == nullptr) {
        ll->tail = new_node;}

    return true;
}

bool FremoveValue(linkedList* ll, const string& value) {
    if (Fempty(ll)) return false;
    if (ll->head->data == value) {
        string tmp;
        return Fpop_front(ll, tmp);
    }

    FNode* prev = ll->head;
    FNode* curr = ll->head->next;
    while (curr != nullptr) {
        if (curr->data == value) {
            if (curr == ll->tail) {
                string tmp;
                return Fpop_back(ll, tmp);
            }
            prev->next = curr->next;
            delete curr;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }

    return false;
}

bool FremoveBeforeValue(linkedList* ll, const string& value) {
    if (Fempty(ll) || ll->head == ll->tail) return false;
    if (ll->head->data == value) return false; 

    FNode* prev_prev = nullptr;
    FNode* prev = ll->head;
    FNode* curr = ll->head->next;
    while (curr != nullptr && curr->data != value) {
        prev_prev = prev;
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) return false; 
    if (prev_prev == nullptr) {
        string tmp;
        return Fpop_front(ll, tmp);
    }
    prev_prev->next = prev->next;
    delete prev;
    return true;
}

bool FremoveAfterValue(linkedList* ll, const string& value) {
    if (Fempty(ll)) return false;
    FNode* curr = ll->head;

    while (curr != nullptr && curr->data != value) {
        curr = curr->next;}
    if (curr == nullptr || curr == ll->tail) return false;

    FNode* to_delete = curr->next;
    if (to_delete == ll->tail) {
        ll->tail = curr;
        ll->tail->next = nullptr;
        delete to_delete;
        return true;
    }
    curr->next = to_delete->next;
    delete to_delete;
    return true;
}

int Ffind(linkedList* ll, const string& value){
    int n = 0;
    for (FNode* c = ll->head; c != nullptr; c = c->next, n++)
        if (c->data == value) return n;
    return -1;
}

vector<string> Fget(linkedList* ll){
    vector<string> result;
    FNode* curr = ll->head;
    while (curr != nullptr) {
        result.push_back(curr->data);
        curr = curr->next;
    }
    return result;
}

vector<string> FgetAfterValue(linkedList* ll, const string& value) {
    vector<string> result;
    
    if (Fempty(ll)) return result;
    FNode* curr = ll->head;
    while (curr != nullptr && curr->data != value) {
        curr = curr->next;
    }
    if (curr == nullptr) return result;
    for (FNode* c = curr->next; c != nullptr; c = c->next) {
        result.push_back(c->data);
    }
    return result;
}

vector<string> FgetBeforeValue(linkedList* ll, const string& value) {
    vector<string> result;
    if (Fempty(ll)) return result;

    FNode* curr = ll->head;
    while (curr != nullptr && curr->data != value) {
        result.push_back(curr->data); 
        curr = curr->next;
    }
    if (curr == nullptr) return vector<string>();
    return result;
}

bool FgetValue(linkedList* ll, const string& value, string& out) {
    FNode* curr = ll->head;
    while (curr != nullptr && curr->data != value) {
        curr = curr->next;
    }
    if (curr == nullptr) return false;
    out = curr->data; 
    return true;
}