#include <iostream>
#include <sstream>
#include "stdlib.h"
//#include <boost/lexical_cast.hpp>

using namespace std;

// Function: return int to_int(string s)
// --------------------------------------
// Accepts: A string rep of a base 16 num
// Returns: The integer equevilant

int to_int(string& s)
{
    if (s[0] == '#')
    {
        s.erase(0, 1);
        return atoi(s.c_str());
    }
    else
    {
        char* end_ptr;
        s.insert(0, "0");	// Needed for strtol()
        return (int)strtol(s.c_str(), &end_ptr, 16);
    }
}

// Funtion: return string to_hex(int i)
// ------------------------------------
// Accepts: An integer
// Returns: The 16 bit hexadecimal
// representation as a string

string to_hex(int i)
{

    /* Need to account for negative numbers
    and hex of different lengths.
    */

    string s;
    string z = "0000";	// Filler string
    stringstream ss;	// String stream
    ss << hex << i;	// Use built in stream feature
    s = ss.str();	// Stream to string
    s.insert(0, z, 0, 4 - s.size());	// Pad to length 4
//    boost::to_upper(s);	// Convert to upper
    return s;
}

// Function: return string to_reg(string&);
// ----------------------------------------
// Accepts: Any string
// Returns: The string without the first char
// Notes: This is meant to remove the first
// char of a string representing a register

string to_reg(string& s)
{
    return s.erase(0, 1);
}
