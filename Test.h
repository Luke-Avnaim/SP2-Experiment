#ifndef TEST_H
#define TEST_H
#include <string>
#include <map>

using namespace std;

int is_valid_label(string& lbl);

int is_op_code(string& s);

int fwd_ref(string &s, map<string, int> m);

#endif