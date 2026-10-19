#pragma once
#include <string>
#include <vector>
#include <map>
#include "list.h"
#include "queue.h"
#include "stack.h"
#include "double_list.h"
#include "avlTree.h"
#include "array.h"

enum StructType {
    STACK, QUEUE, LIST, DOUBLE_LIST, TREE, ARRAY
};

struct Structure {
    StructType type;
    void* data;
};

extern std::map<std::string, Structure> registr;
bool loadFromFile(const std::string& filename);
bool saveToFile(const std::string& filename);
bool executeCmd(const std::string& query);
bool isModified(const std::string& query);
std::vector<std::string> parseQuery(const std::string& query);
void clearRegistr();