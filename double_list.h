#pragma once
#include <string>
#include <vector>

struct LNode {
    std::string data;
    LNode* next;
    LNode* prev;
};

struct double_linkedList {
    LNode* head;
    LNode* tail;
};

void Linit(double_linkedList* Dll);
bool Lempty(double_linkedList* Dll);
int Lsize(double_linkedList* Dll);
void Lclear(double_linkedList* Dll);

void Lpush_front(double_linkedList* Dll, const std::string& str);
void Lpush_back(double_linkedList* Dll, const std::string& str);
bool Lpop_front(double_linkedList* Dll, std::string& out);
bool Lpop_back(double_linkedList* Dll, std::string& out);
LNode* Lindex(double_linkedList* Dll, int index);

bool LinsertBefore(double_linkedList* Dll, const std::string& value, const std::string& str);
bool LinsertAfter(double_linkedList* Dll, const std::string& value, const std::string& str);
bool LremoveBeforeValue(double_linkedList* Dll, const std::string& value);
bool LremoveAfterValue(double_linkedList* Dll, const std::string& value);
bool LremoveValue(double_linkedList* Dll, const std::string& value);
int Lfind(double_linkedList* Dll, const std::string& value);

std::vector<std::string> Lget(double_linkedList* Dll);
std::vector<std::string> LgetReverse(double_linkedList* Dll);
std::vector<std::string> LgetAfterValue(double_linkedList* Dll, const std::string& value);
std::vector<std::string> LgetBeforeValue(double_linkedList* Dll, const std::string& value);
bool LgetValue(double_linkedList* Dll, const std::string& value, std::string& out);