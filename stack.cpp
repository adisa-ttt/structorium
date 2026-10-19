#include<iostream>
#include <vector>
#include "stack.h"
using namespace std;

void Sinit(Stack* stack){
    stack->head = nullptr;
}

bool Sempty(Stack* stack){
    return stack->head == nullptr;
}

void Spush(Stack* stack, const string& str){
    SNode* new_SNode = new SNode{str, nullptr};
    new_SNode->next = stack->head;
    stack->head = new_SNode;

}

bool Spop(Stack* stack, string& out){
    if (Sempty(stack)) return false;
 
    SNode* old_head = stack->head;
    out = old_head->data;
    stack->head = old_head->next;
    delete old_head;
    return true;
}

vector<string> Sget(Stack* stack){
    vector<string> result;
    SNode* curr = stack->head;
    while (curr != nullptr){
        result.push_back(curr->data);
        curr = curr->next;
    }
    return result;
} 

void Sclear(Stack* stack){
    while (stack->head != nullptr){
        SNode* popped = stack->head;
        stack->head = stack->head->next;
        delete popped;
    }
}