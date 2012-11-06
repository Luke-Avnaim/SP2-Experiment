#include "Print.h"
#include <map>
#include <string>
#include <iostream>
#include <queue>

using namespace std;

// Function: return void print_symbol_table(map<string, int>)
// ----------------------------------------------------------
// Accepts: A map of string and int
// Returns: void
// Note: Formatted printing of the map

void print_map(map<string, int> m)
{
    map<string, int>::iterator it;
    for (it = m.begin(); it != m.end(); it++)
    {
        cout << (*it).first << " => " << (*it).second << endl;
    }
}

// Function: return void print_records(queue<string>)
// --------------------------------------------------
// Accepts: A queue of strings
// Return: void
// Note: Prints and destroys the contents of the queue

void print_records(queue<string> q)
{
    while (!q.empty())
    {
        cout << q.front() << endl;
        q.pop();
    }
}

