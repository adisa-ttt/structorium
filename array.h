#pragma once
#include <string>
#include <vector>

struct Array {
    std::string* data;
    int size;
    int capacity;
};

void Minit(Array* arr);//+++
void Mpush_back(Array* arr, const std::string& str);//+++
bool Minsert(Array* arr, int index, const std::string& str);//++
bool MremoveAt(Array* arr, int index);//++
bool Mset(Array* arr, int index, const std::string& str);//+++
bool MgetAt(Array* arr, int index, std::string& out);//+++
std::vector<std::string> Mget(Array* arr);
int Msize(Array* arr);
void Mclear(Array* arr);