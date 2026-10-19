#pragma once
#include <string>
#include <vector>

struct SNode {
    std::string data;
    SNode* next;
};

struct Stack {
    SNode* head;
};

void Sinit(Stack* stack);
bool Sempty(Stack* stack);
void Spush(Stack* stack, const std::string& str);
bool Spop(Stack* stack, std::string& out);
std::vector<std::string> Sget(Stack* stack);
void Sclear(Stack* stack);