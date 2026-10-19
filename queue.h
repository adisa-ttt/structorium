#pragma once
#include <string>
#include <vector>

struct QNode {
    std::string person;
    QNode* next;
};

struct Queue {
    QNode* head;
    QNode* tail;
};

void Qinit(Queue* que);
bool Qempty(Queue* que);
void Qpush(Queue* que, const std::string& str);
bool Qpop(Queue* que, std::string& out);
std::vector<std::string> Qget(Queue* que);
void Qclear(Queue* que);