#pragma once
#include <string>
#include <vector>

struct FNode {
    std::string data;
    FNode* next;
};

struct linkedList {
    FNode* head;
    FNode* tail;
};

void Finit(linkedList* ll);
bool Fempty(linkedList* ll);
int Fsize(linkedList* ll);
void Fclear(linkedList* ll);

void Fpush_front(linkedList* ll, const std::string& str);
void Fpush_back(linkedList* ll, const std::string& str);
bool Fpop_front(linkedList* ll, std::string& out);
bool Fpop_back(linkedList* ll, std::string& out);

FNode* Findex(linkedList* ll, int index);
bool FinsertBeforeValue(linkedList* ll, const std::string& value, const std::string& str);
bool FinsertAfterValue(linkedList* ll, const std::string& value, const std::string& str);
bool FremoveBeforeValue(linkedList* ll, const std::string& value);
bool FremoveAfterValue(linkedList* ll, const std::string& value);
bool FremoveValue(linkedList* ll, const std::string& value);
int Ffind(linkedList* ll, const std::string& value);

std::vector<std::string> Fget(linkedList* ll);
std::vector<std::string> FgetAfterValue(linkedList* ll, const std::string& value);
std::vector<std::string> FgetBeforeValue(linkedList* ll, const std::string& value);
bool FgetValue(linkedList* ll, const std::string& value, std::string& out);