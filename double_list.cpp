#include "double_list.h"
#include <string>
#include <vector>
using namespace std;

void Linit(double_linkedList* Dll){
    Dll->head = nullptr;
    Dll->tail = nullptr;
}

bool Lempty(double_linkedList* Dll){
    return Dll->head == nullptr;
}

int Lsize(double_linkedList* Dll){
    int n = 0;
    for (LNode* c = Dll->head; c != nullptr; c = c->next) n++;
    return n;
}

void Lclear(double_linkedList* Dll){
    while (Dll->head != nullptr){
        LNode* popped = Dll->head;
        Dll->head = popped->next;
        delete popped;
    }
    Dll->tail = nullptr;
}

void Lpush_front(double_linkedList* Dll, const string& str){
    LNode* new_LNode = new LNode{str, Dll->head, nullptr};

    if (Dll->head == nullptr){
        Dll->tail = new_LNode;
    } else {
        Dll->head->prev = new_LNode;
    }
    Dll->head = new_LNode;
}

void Lpush_back(double_linkedList* Dll, const string& str){
    LNode* new_LNode = new LNode{str, nullptr, Dll->tail};

    if (Dll->tail == nullptr) {
        Dll->head = new_LNode;
    } else {
        Dll->tail->next = new_LNode;
    }
    Dll->tail = new_LNode;
}

bool Lpop_front(double_linkedList* Dll, string& out){
    if (Lempty(Dll)) return false;
    LNode* popped = Dll->head;
    out = popped->data;
    Dll->head = popped->next;
    if (Dll->head == nullptr) Dll->tail = nullptr;
    else Dll->head->prev = nullptr;
    delete popped;
    return true;
}

bool Lpop_back(double_linkedList* Dll, string& out){
    if (Lempty(Dll)) return false;
    LNode* popped = Dll->tail;
    out = popped->data;
    Dll->tail = popped->prev;
    if (Dll->tail == nullptr) Dll->head = nullptr;
    else Dll->tail->next = nullptr;
    delete popped;               
    return true;
}

LNode* Lindex(double_linkedList* Dll, int index){
    if (index < 0 || Lempty(Dll)) return nullptr;
    LNode* index_node = Dll->head;
    int n = 0;
    while (n != index && index_node != nullptr){
        index_node = index_node->next;
        n++;
    }
    return index_node;
}

bool LinsertBefore(double_linkedList* Dll, const string& value, const string& str){
    if (Lempty(Dll)) return false;
    LNode* value_node = Dll->head;
    while (value_node != nullptr && value_node->data != value) value_node = value_node->next;
    if (value_node == nullptr) return false;
    if (value_node == Dll->head){
        Lpush_front(Dll, str);
        return true;
    }
    LNode* left = value_node->prev;
    LNode* new_node = new LNode{str, value_node, left};
    left->next = new_node;
    value_node->prev = new_node;
    return true;
}

bool LinsertAfter(double_linkedList* Dll, const string& value, const string& str){
    if (Lempty(Dll)) return false;
    LNode* value_node = Dll->head;
    while (value_node != nullptr && value_node->data != value) value_node = value_node->next;
    if (value_node == nullptr) return false;
    if (value_node == Dll->tail){
        Lpush_back(Dll, str);
        return true;
    }
    LNode* right = value_node->next;
    LNode* new_node = new LNode{str, right, value_node};
    value_node->next = new_node;
    right->prev = new_node;
    return true;
}

bool LremoveValue(double_linkedList* Dll, const string& value){
    if (Lempty(Dll)) return false;
    string tmp;
    LNode* value_node = Dll->head;
    while (value_node != nullptr && value_node->data != value) value_node = value_node->next;
    if (value_node == nullptr) return false;
    if (value_node == Dll->head) return Lpop_front(Dll, tmp);
    if (value_node == Dll->tail) return Lpop_back(Dll, tmp);
    LNode* left = value_node->prev;
    LNode* right = value_node->next;
    left->next = right;
    right->prev = left;
    delete value_node;
    return true;
}

bool LremoveBeforeValue(double_linkedList* Dll, const string& value){
    if (Lempty(Dll) || Dll->head->data == value) return false;
    LNode* value_node = Dll->head;
    while (value_node != nullptr && value_node->data != value) value_node = value_node->next;
    if (value_node == nullptr) return false;
    LNode* to_remove = value_node->prev;
    if (to_remove == Dll->head){
        string tmp;
        return Lpop_front(Dll, tmp);
    }
    LNode* left = to_remove->prev;
    LNode* right = to_remove->next;
    left->next = right;
    right->prev = left;
    delete to_remove;
    return true;
}

bool LremoveAfterValue(double_linkedList* Dll, const string& value){
    if (Lempty(Dll)) return false;
    LNode* value_node = Dll->head;
    while (value_node != nullptr && value_node->data != value) value_node = value_node->next;
    if (value_node == nullptr || value_node->next == nullptr) return false;
    LNode* to_remove = value_node->next;
    if (to_remove == Dll->tail){
        string tmp;
        return Lpop_back(Dll, tmp);
    }
    LNode* left = to_remove->prev;
    LNode* right = to_remove->next;
    left->next = right;
    right->prev = left;
    delete to_remove;
    return true;
}

int Lfind(double_linkedList* Dll, const string& value){
    int n = 0;
    for (LNode* c = Dll->head; c != nullptr; c = c->next, n++)
        if (c->data == value) return n;
    return -1;
}

vector<string> Lget(double_linkedList* Dll){
    vector<string> result;
    LNode* current = Dll->head;
    while (current != nullptr){
        result.push_back(current->data);
        current = current->next;
    }
    return result;
}

vector<string> LgetReverse(double_linkedList* Dll){
    vector<string> result;
    LNode* current = Dll->tail;
    while (current != nullptr){
        result.push_back(current->data);
        current = current->prev;
    }
    return result;
}

vector<string> LgetAfterValue(double_linkedList* Dll, const string& value){
    vector<string> result;
    LNode* value_node = Dll->head;
    while (value_node != nullptr && value_node->data != value) value_node = value_node->next;
    if (value_node == nullptr) return result;
    for (LNode* c = value_node->next; c != nullptr; c = c->next)
        result.push_back(c->data);
    return result;
}

vector<string> LgetBeforeValue(double_linkedList* Dll, const string& value){
    vector<string> result;
    LNode* curr = Dll->head;
    while (curr != nullptr && curr->data != value){
        result.push_back(curr->data);
        curr = curr->next;
    }
    if (curr == nullptr) return vector<string>();
    return result;
}

bool LgetValue(double_linkedList* Dll, const string& value, string& out){
    LNode* value_node = Dll->head;
    while (value_node != nullptr && value_node->data != value) value_node = value_node->next;
    if (value_node == nullptr) return false;
    out = value_node->data;
    return true;
}