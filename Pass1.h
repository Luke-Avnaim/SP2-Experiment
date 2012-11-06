// File: Pass1.h

#ifndef PASS1_H
#define PASS1_H

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

int Pass1(queue<string> oFiles, map<string, string, string> symbolTable, valueTable values, queue<string> segments);

#endif