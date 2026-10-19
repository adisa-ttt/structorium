#include "array.h"
using namespace std;
static const int CAPACITY = 4;
void Minit(Array* arr) {
    arr->capacity = CAPACITY;
    arr->size = 0;
    arr->data = new string[arr->capacity];

}

static void resize(Array* arr){
    int newCap = arr->capacity *2;
    string* newData = new string[newCap];

    for (int i = 0; i < arr->size; i++){
        newData[i] = arr->data[i];}
    delete[] arr->data;
    arr->data = newData;
    arr->capacity = newCap;
}

void Mclear(Array* arr){
    delete[] arr->data;
    arr->capacity = 0;
    arr->size = 0;
    arr->data = nullptr;
}

void Mpush_back(Array* arr, const string& str) {
    if (arr->size == arr->capacity) resize(arr);
    arr->data[arr->size] = str;
    arr->size++;
}

bool Minsert(Array* arr, int index, const string& str) {
    if (index < 0 || index > arr->size) return false;
    if (arr->size ==  arr-> capacity) resize(arr);
    for ( int i = arr->size; i > index; i--){
        arr->data[i] = arr->data [i-1];}
    arr->data[index] = str;
    arr->size++;
    return true;
}

bool MremoveAt(Array* arr, int index) {
    if (index < 0 || index > arr->size) return false;
    for (int i = index; i< arr->size - 1; i++){
        arr->data[i] = arr->data[i+1];}
    arr->size--;
    return true;
}

bool Mset(Array* arr, int index, const string& str) {
    if (index < 0 || index >= (arr->size)) return false;
    arr->data[index] = str;
    return true;
}

bool MgetAt(Array* arr, int index, string& out) {
    if (index < 0 || index >= arr->size) return false;
    out = arr->data[index];
    return true;
}

vector <string> Mget(Array* arr) {
    vector<string> result;
    for (int i = 0; i<arr->size; i++){
        result.push_back(arr->data[i]);}
    return result;
}

int Msize(Array* arr) {
    return arr->size;
}
