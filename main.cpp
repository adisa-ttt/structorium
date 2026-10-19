#include <iostream>
#include <fstream>
#include <sstream>
#include "main.h"
#include <map>
#include <vector>
#include <string>
using namespace std;

map<string, Structure> registr;

vector<string> parseQuery (const string& query){
    vector<string> tokens;
    istringstream iss (query);
    string token;
    while (iss >> token){
        tokens.push_back(token);
    }
    return tokens;
}

StructType typeFromCode(char code) {
    switch (code) {
        case 'M': return ARRAY;
        case 'F': return LIST;
        case 'L': return DOUBLE_LIST;
        case 'Q': return QUEUE;
        case 'S': return STACK;
        case 'T': return TREE;
        default:  return LIST;
    }
}

bool ctreateStruct(const string& name, char typeCode){
    if (typeCode == 'S'){
        Stack* stack = new Stack;
        Sinit(stack);
        registr[name] = {STACK, stack};
    } else if (typeCode == 'Q') {
        Queue* que = new Queue;
        Qinit(que);
        registr[name] = {QUEUE, que};
    } else if (typeCode == 'F') {
        linkedList* ll = new linkedList;
        Finit(ll);
        registr[name] = {LIST, ll};
    } else if (typeCode == 'L') {
        double_linkedList* Dll = new double_linkedList;
        Linit(Dll);
        registr[name] = {DOUBLE_LIST, Dll};
    } else if (typeCode == 'M'){
        Array* arr = new Array;
        Minit(arr);
        registr[name] = {ARRAY, arr};
    } else if (typeCode == 'T'){
        Node** tree = new Node*;
        *tree = nullptr;
        registr[name] = {TREE, tree};
    } else return false;
    return true;
}

bool executeCmd (const std::string& query){
    vector<string> tokens = parseQuery(query);
    if (tokens.empty()) return false;

    string cmd = tokens[0];
    if (tokens.size() < 2){
        cout << "error: missing structure name." << endl;
        return false;
    }
    string name = tokens[1];
    char typeCode = cmd[0];
    if (cmd == "ISMEMBER") typeCode = 'T';
    StructType expectedType = typeFromCode(typeCode);
    bool exists = (registr.find(name) != registr.end());

    if (!exists) {
        if (cmd == "FPUSH" || cmd == "LPUSH" || cmd == "QPUSH" 
            || cmd == "SPUSH" || cmd == "MPUSH" || cmd == "TINSERT"){
                if (!ctreateStruct(name, typeCode)){
                    cout << "error:  unknown type code " << typeCode << "." << endl;
                    return false;
                }
                exists = true;
            } else {
                cout << "error: structure " << name << " not found." << endl;
                return false;
            }
    }

    Structure& str = registr[name];
    if (cmd != "PRINT" && str.type != expectedType) {
        cout << "error: " << name << "has wrong type." << endl;
        return false;
    }

//-------------------ARRAY--------------------------------------------------------------------------------ARRAY

if (cmd == "MPUSH") {
        Array* arr = static_cast<Array*>(str.data);
        if (tokens.size() == 3) {
            Mpush_back(arr, tokens[2]);
        } else if (tokens.size() == 4) {
            int idx = stoi(tokens[2]);
            if (!Minsert(arr, idx, tokens[3])) {
                cout << "error: index out of range." << endl;
                return false;
            }
        } else {
            cout << "error: invalid MPUSH syntax." << endl;
            return false;
        }
        return true;
    }
    if (cmd == "MGET") {
        Array* arr = static_cast<Array*>(str.data);
        if (tokens.size() == 2) {
            vector<string> vals = Mget(arr);
            for (const string& v : vals) cout << v << " ";
            cout << endl;
        } else if (tokens.size() == 3) {
            string val;
            int idx = stoi(tokens[2]);
            if (MgetAt(arr, idx, val)) cout << val << endl;
            else cout << "error: index out of range." << endl;
        }
        return true;
    }
    if (cmd == "MDEL") {
        if (tokens.size() == 3) {
            Array* arr = static_cast<Array*>(str.data);
            int idx = stoi(tokens[2]);
            if (MremoveAt(arr, idx)) cout << "success." << endl;
            else cout << "error: index out of range." << endl;
        }
        return true;
    }
    if (cmd == "MSET") {
        if (tokens.size() == 4) {
            Array* arr = static_cast<Array*>(str.data);
            int idx = stoi(tokens[2]);
            if (Mset(arr, idx, tokens[3])) cout << "success." << endl;
            else cout << "error: index out of range." << endl;
        }
        return true;
    }
    if (cmd == "MSIZE") {
        Array* arr = static_cast<Array*>(str.data);
        cout << Msize(arr) << endl;
        return true;
    }

//---------------------LIST-------------------------------------------------------------------------------ОДНОСВЯЗ СПИСОК

    if (cmd == "FPUSH") {
        if (tokens.size() < 4) {
            cout << "error: FPUSH requires mode and value." << endl;
            return false;}
        linkedList* ll = static_cast<linkedList*>(str.data);
        if (tokens.size() == 4){
            if (tokens[2] == "front") Fpush_front(ll, tokens[3]);
            else if (tokens[2] == "back") Fpush_back(ll, tokens[3]);
            else {
                cout << "error: invalid mode" << endl;
                return false;}
        } else if (tokens.size() == 5) {
            if (tokens[2] == "before") FinsertBeforeValue(ll, tokens[3], tokens[4]);
            else if (tokens[2] == "after") FinsertAfterValue(ll, tokens[3], tokens[4]);
            else {
                cout << "error: invalid mode" << endl;
                return false;}
        }
        return true;
    }
    if (cmd == "FDEL") {
        if (tokens.size() < 3) {
            cout << "error: FDEL reguires value." << endl;
            return false; }
        linkedList* ll = static_cast<linkedList*>(str.data);
        if (tokens.size() == 3){
            bool ok = FremoveValue(ll, tokens[2]);
            cout << (ok ? "success." : "ERROR: value not found.") << endl;}
        else if (tokens.size() == 4) {
            if (tokens[2] == "before") FremoveBeforeValue(ll, tokens[3]);
            else if (tokens[2] == "after") FremoveAfterValue(ll, tokens[3]);
            else {
            cout << "error: invalid mode" << endl;
            return false;}
        } 
        return true;
    }
    if (cmd == "FPOP") {
        if (tokens.size() < 3) {
            cout << "error: FPOP requires mode." << endl;
            return false;}
        linkedList* ll = static_cast<linkedList*>(str.data);
        string tmp;
        if (tokens[2] == "front") Fpop_front(ll, tmp);
        else if (tokens[2] == "back") {
            if (tokens.size() < 4) { 
            Fpop_back(ll, tmp);}}
        else {
            cout << "error: invalid mode" << endl;
            return false;}
        return true;
    }

    if (cmd == "FGET") {
        linkedList* ll = static_cast<linkedList*>(str.data);
        if (tokens.size() == 2){    
            vector<string> vals = Fget(ll);
            for (const string& v : vals) cout << v << " ";
            cout << endl;}
        else if (tokens.size() == 4) {
            if (tokens[2] == "before") {
                vector<string> vals = FgetBeforeValue(ll, tokens[3]);
                for (const string& v : vals) cout << v << " ";
                cout << endl;}
            else if (tokens[2] == "after"){ 
                vector<string> vals = FgetAfterValue(ll, tokens[3]);
                for (const string& v : vals) cout << v << " ";
                cout << endl;}
        }
        return true;
    }

//------------------DOUBLE LIST---------------------------------------------------------------------------------ДВУСВЯЗ СПИСОК

        if (cmd == "LPUSH") {
        if (tokens.size() < 4) {
            cout << "error: LPUSH requires mode and value." << endl;
            return false;}
        double_linkedList* dll = static_cast<double_linkedList*>(str.data);
        if (tokens.size() == 4){
            if (tokens[2] == "front") Lpush_front(dll, tokens[3]);
            else if (tokens[2] == "back") Lpush_back(dll, tokens[3]);
            else {
                cout << "error: invalid mode" << endl;
                return false;}
        } else if (tokens.size() == 5) {
            if (tokens[2] == "before") LinsertBefore(dll, tokens[3], tokens[4]);
            else if (tokens[2] == "after") LinsertAfter(dll, tokens[3], tokens[4]);
            else {
                cout << "error: invalid mode" << endl;
                return false;}
        }
        return true;
    }
    if (cmd == "LDEL") {
        if (tokens.size() < 3) {
            cout << "error: LDEL requires value." << endl;
            return false; }
        double_linkedList* dll = static_cast<double_linkedList*>(str.data);
        if (tokens.size() == 3){
            bool ok = LremoveValue(dll, tokens[2]);
            cout << (ok ? "success." : "ERROR: value not found.") << endl;}
        else if (tokens.size() == 4) {
            if (tokens[2] == "before") LremoveBeforeValue(dll, tokens[3]);
            else if (tokens[2] == "after") LremoveAfterValue(dll, tokens[3]);
            else {
                cout << "error: invalid mode" << endl;
                return false;}
        } 
        return true;
    }
    if (cmd == "LPOP") {
        if (tokens.size() < 3) {
            cout << "error: LPOP requires mode." << endl;
            return false;}
        double_linkedList* dll = static_cast<double_linkedList*>(str.data);
        string tmp;
        if (tokens[2] == "front") Lpop_front(dll, tmp);
        else if (tokens[2] == "back") Lpop_back(dll, tmp);
        else {
            cout << "error: invalid mode" << endl;
            return false;}
        return true;
    }
    if (cmd == "LGET") {
        double_linkedList* dll = static_cast<double_linkedList*>(str.data);
        if (tokens.size() == 2){    
            vector<string> vals = Lget(dll);
            for (const string& v : vals) cout << v << " ";
            cout << endl;}
        else if (tokens.size() == 4) {
            if (tokens[2] == "before") {
                vector<string> vals = LgetBeforeValue(dll, tokens[3]);
                for (const string& v : vals) cout << v << " ";
                cout << endl;}
            else if (tokens[2] == "after"){ 
                vector<string> vals = LgetAfterValue(dll, tokens[3]);
                for (const string& v : vals) cout << v << " ";
                cout << endl;}
        }
        return true;
    }

//-----------------------QUEUE-------------------------------------------------------------------------------------------ОЧЕРЕДЬ
    if (cmd == "QPUSH") {
        if (tokens.size() < 3) {
            cout << "error: QPUSH requires value." << endl;
            return false;}
        Queue* que = static_cast<Queue*>(str.data);
        Qpush(que, tokens[2]);
        return true;
    }
    if (cmd == "QPOP") {
        Queue* que = static_cast<Queue*>(str.data);
        string out;
        bool ok = Qpop(que, out);
        if (ok) {
            cout << out << endl;
            return true;}
        else {
            cout << "error: queue is empty." << endl;
            return false;}
    }
    if (cmd == "QGET") {
        Queue* que = static_cast<Queue*>(str.data);
        vector<string> vals = Qget(que);
        for (const string& v : vals) cout << v << " ";
        cout << endl;
        return true;
    }

//----------------------------STACK------------------------------------------------------------------------------------СТЕК

    if (cmd == "SPUSH") {
        if (tokens.size() < 3) {
            cout << "error: SPUSH requires value." << endl;
            return false;}
        Stack* stk = static_cast<Stack*>(str.data);
        Spush(stk, tokens[2]);
        return true;
    }
    if (cmd == "SPOP") {
        Stack* stk = static_cast<Stack*>(str.data);
        string out;
        bool ok = Spop(stk, out);
        if (ok) {
            cout << out << endl;
            return true;}
        else {
            cout << "error: stack is empty." << endl;
            return false;}
    }
    if (cmd == "SGET") {
        Stack* stk = static_cast<Stack*>(str.data);
        vector<string> vals = Sget(stk);
        for (const string& v : vals) cout << v << " ";
        cout << endl;
        return true;
    }

//-------------------------TREEE-------------------------------------------------------------------------------------------------AVL_NREEEEE

    if (cmd == "TINSERT") {
        if (tokens.size() < 3) {
            cout << "error: TINSERT requires value." << endl;
            return false;}
        Node** tree = static_cast<Node**>(str.data);
        int key = stoi(tokens[2]);
        *tree = Tinsert(*tree, key);
        str.data = tree;
        return true;
    }

    if (cmd == "TDEL") {
        if (tokens.size() < 3) {
            cout << "error: TDEL requires value." << endl;
            return false;}
        Node** tree = static_cast<Node**>(str.data);
        int key = stoi(tokens[2]);
        *tree = Tremove(*tree, key);
        str.data = tree;
        return true;
    }
    if (cmd == "TGET") {
        Node** tree = static_cast<Node**>(str.data);
        vector<int> vals;
        preorder(*tree, vals);
        for (int v : vals) cout << v << " ";
            cout << endl;
        return true;
}
    if (cmd == "ISMEMBER") {
        if (tokens.size() < 3) {
            cout << "error: ISMEMBER requires value." << endl;
            return false;}
        Node** tree = static_cast<Node**>(str.data);
        int key = stoi(tokens[2]);
        bool found = Tfind(*tree, key);
        cout << (found ? "TRUE" : "FALSE") << endl;
        return true;
    }

//-------------------------PRINT-------------------------------------------------------------------------------------------------PRINT

    if (cmd == "PRINT") {
        if (str.type == TREE) {
            Node** tree = static_cast<Node**>(str.data);
            vector<int> vals;
            preorder(*tree, vals);
            cout << endl;
            return true;
        }
        vector<string> vals;
        if (str.type == ARRAY) {
            vals = Mget(static_cast<Array*>(str.data));
        } else if (str.type == LIST) {
            vals = Fget(static_cast<linkedList*>(str.data));
        } else if (str.type == DOUBLE_LIST) {
            vals = Lget(static_cast<double_linkedList*>(str.data));
        } else if (str.type == QUEUE) {
            vals = Qget(static_cast<Queue*>(str.data));
        } else if (str.type == STACK) {
            vals = Sget(static_cast<Stack*>(str.data));
        }
        for (const string& v : vals) cout << v << " ";
        cout << endl;
        return true;
    }

    cout << "error: unknown command " << cmd << endl;
    return false;
}

bool loadFromFile (const string& filename){
    fstream fs;
    fs.open(filename);

    if (!fs.is_open()) return false;

    string line;
    while (getline(fs, line)){
        if (line.empty()) continue;

        executeCmd(line);
    }
    fs.close();
    return true;
}

bool saveToFile (const string& filename){
    ofstream out;
    out.open(filename);

    if (!out.is_open()) return false;

    for (auto& pair : registr) {
        string name = pair.first;
        Structure& str = pair.second;

        if (str.type == LIST) {
            linkedList* ll = static_cast<linkedList*>(str.data);
            vector<string> vals = Fget(ll);
            for (const string& v : vals)
                out << "FPUSH " << name << " back " << v << endl;
        }
        else if (str.type == DOUBLE_LIST) {
            double_linkedList* dll = static_cast<double_linkedList*>(str.data);
            vector<string> vals = Lget(dll);
            for (const string& v : vals)
                out << "LPUSH " << name << " back " << v << endl;
        }
        else if (str.type == QUEUE) {
            Queue* que = static_cast<Queue*>(str.data);
            vector<string> vals = Qget(que);
            for (const string& v : vals)
                out << "QPUSH " << name << " " << v << endl;
        }
        else if (str.type == STACK) {
            Stack* stk = static_cast<Stack*>(str.data);
            vector<string> vals = Sget(stk);
            for (int i = (int)vals.size() - 1; i >= 0; i--)
                out << "SPUSH " << name << " " << vals[i] << endl;
        } else if (str.type == ARRAY) {
            Array* arr = static_cast<Array*>(str.data);
            vector<string> vals = Mget(arr);
            for (const string& v : vals)
                out << "MPUSH " << name << " " << v << endl;
        } else if (str.type == TREE) {
            Node** tree = static_cast<Node**>(str.data);
            vector<int> vals;
            preorder(*tree, vals);
            for (int v : vals)
                out << "TINSERT " << name << " " << v << endl;
}}
    out.close();
    return true;
}

bool isModified(const string& query) {
    return query.find("PUSH") != string::npos 
    || query.find("DEL") != string::npos 
    || query.find("POP") != string::npos 
    || query.find("INSERT") != string::npos;
}

void clearRegistr(){
    for (auto& pair : registr) {
        Structure& str = pair.second;
        if (str.type == LIST) {
            linkedList* ll = static_cast<linkedList*>(str.data);
            Fclear(ll);
            delete ll;
        } else if (str.type == DOUBLE_LIST) {
            double_linkedList* dll = static_cast<double_linkedList*>(str.data);
            Lclear(dll);
            delete dll;
        } else if (str.type == QUEUE) {
            Queue* que = static_cast<Queue*>(str.data);
            Qclear(que);
            delete que;
        } else if (str.type == STACK) {
            Stack* stk = static_cast<Stack*>(str.data);
            Sclear(stk);
            delete stk;
        } else if (str.type == TREE) {
            Node** tree = static_cast<Node**>(str.data);
            Tclear(*tree);
            delete tree;
        } else if (str.type == ARRAY) {
            Array* arr = static_cast<Array*>(str.data);
            Mclear(arr);
            delete arr;}
    }
    registr.clear();
}

int main(int argc, char* argv[]) {
    string filename = "file.data";
    string query = "";

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            filename = argv[++i];
        }
        else if (arg == "--query" && i + 1 < argc) {
            query = argv[++i];
        }
        else {
            cout << "error: unknown argument " << arg << endl;
            return 1;
        }
    }
    loadFromFile(filename);

    if (!query.empty()) {
        bool ok = executeCmd(query);
        if (ok && isModified(query)) {
            saveToFile(filename);
        }
    } else {
        cout << "no query provided. use --query \"COMMAND\"." << endl;
    }

    clearRegistr();
    return 0;
}