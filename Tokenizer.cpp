#include "Tokenizer.h"

#include <iostream>

using namespace std;

// ----------------------
// Class: StringTokenizer
// ----------------------

StringTokenizer::StringTokenizer(string& s)
{
    str_ = s;
    count_ = -1;
    begin_ = 0;
    end_= 0;
    delim_ = " \f\n\r\t\v,";	// Delimiters
    begin_ = str_.find_first_not_of(delim_);
    end_ = str_.find_first_of(delim_, begin_);
}

bool StringTokenizer::hasMoreTokens( )
{
    return(begin_ != end_);
}

void StringTokenizer::nextToken(string& s)
{
    if (begin_ != string::npos && end_ != string::npos)
    {
        s = str_.substr(begin_, end_-begin_);
        begin_ = str_.find_first_not_of(delim_, end_);
        end_ = str_.find_first_of(delim_, begin_);
    }
    else if (begin_ != string::npos && end_ == string::npos)
    {
        s = str_.substr(begin_, str_.length( )-begin_);
        begin_ = str_.find_first_not_of(delim_, end_);
    }
}


// Function: return queue<string> get_tokens(string& s)
// ----------------------------------------------------
// Usage: Accepts a string as input
// Returns a queue of strings

queue<string> StringTokenizer::get_tokens(string& line)
{
    string token; // String for holding a token
    queue<string> q; // Queue to hold many tokens
    StringTokenizer tk(line); // Initialize tokenizer

    while (tk.hasMoreTokens())  	// While there are tokens left
    {
        tk.nextToken(token);	// Get the next token
        q.push(token);	// Push the token into the queue
    }
    return q;	// Return the queue of tokens
}

// Function: return string strip_line(string& s)
// ---------------------------------------------
// Accepts: string as input
// Returns: Returns the string with out chars after and incuding ;

string StringTokenizer::strip_line(string& s)
{
    int p = s.find_first_of(";");
    if (p > -1)
    {
        s.erase(p);
    }
    return s;
}
