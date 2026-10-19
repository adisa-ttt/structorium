#include "queue.h"
using namespace std;

void Qinit(Queue* que){
    que->head = nullptr;
    que->tail = nullptr;
}

bool Qempty(Queue* que){
    return que->head == nullptr;
}

void Qpush(Queue* que, const string& str){
    QNode* new_QNode = new QNode{str, nullptr};

    if (que->tail == nullptr){
        que->head = new_QNode;
        que->tail = new_QNode;
    } else {
        que->tail->next = new_QNode;
        que->tail = new_QNode;
    }
}

bool Qpop(Queue* que, string& out){
    if (Qempty(que)) return false;

    QNode* current_head = que->head;
    out = current_head->person;
    que->head = que->head->next;

    if (que->head == nullptr) que->tail = nullptr;
    delete current_head;
    return true;
}

vector<string> Qget(Queue* que){
    QNode* curr = que->head;
    vector<string> result;
    while (curr != nullptr){
        result.push_back(curr->person);
        curr = curr->next;
    }
    return result;
}

void Qclear(Queue* que){
    while (que->head != nullptr){
        QNode* popped = que->head;
        que->head = que->head->next;
        delete popped;
    }
    que->tail = nullptr;
}