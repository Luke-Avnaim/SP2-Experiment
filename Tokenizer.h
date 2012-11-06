#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <queue>

// ----------------------
// Class: StringTokenizer
// ----------------------

using namespace std;

class StringTokenizer
{

private:

    string delim_;
    string str_;
    int count_;
    int begin_;
    int end_;

public:

    StringTokenizer(string& line);
    queue<string> get_tokens(string& line);
    string strip_line(string& s);
    StringTokenizer(const string& s);
    bool hasMoreTokens();
    void nextToken(string& s);
};

#endif // TOKENIZER_H
