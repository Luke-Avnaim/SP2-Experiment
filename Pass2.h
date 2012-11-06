// File: Pass2.h

#ifndef PASS2_H
#define PASS2_H

#include <string>
#include <queue>
#include <map>

using namespace std;

#ifndef TABLES
#define TABLES

typedef struct{
	int programSize;
    int IPLA;
    int page;
    queue<int> PLA;
    string progName;
} valueTable;

#endif

int Pass2(valueTable values, map<string, string, string> symbolTable, queue<string> segments, queue<string> prog);

#endif