#include "Test.h"

using namespace std;

// Funtion: return int is_valid_label(string& s)
// ---------------------------------------------
// Usage: Accepts a string as input
// Returns 0 if the string is not a valid label
// Returns 1 if the string is a valid label

int is_valid_label(string& lbl)
{
    if ((lbl.size() > 6) || (lbl[0] == 'R') || (lbl[0] == 'x')) {
        return 0;
    } else {
        return 1;
    }
}

// Function: return int is_op_code(string& s)
// ------------------------------------------
// Usage: Accepts a string as input
// Returns a 1 if it is a valid OpCode
// Returns a 0 if it is not

int is_op_code(string& s)
{
    
    if ((s == "ADD") || (s == "NOT") || (s == "BRN") ||
        (s == "BRZ") || (s == "BRP") || (s == "BRNZ") ||
        (s == "BRZP") || (s == "BRNP") || (s == ".EQU") ||
        (s == ".FILL") || (s == ".STRZ") || (s == ".BLKW") ||
        (s == "JSR") || (s == "JMP") || (s == "LD") || (s == "ST") ||
        (s == "LDI") || (s == "STI") || (s =="LEA") ||
        (s == "JSSR") || (s == "RET") || (s == "TRAP") ||
        (s == "LDR") || (s == "STR") || (s =="DBUG") ||
        (s == "AND")) {
        return 1;
        
    } else {
        return 0;
    }
}

// Function: fwd_ref(string &, map<string, int>)
// ---------------------------------------------
// Accepts: A string and a map. Specifically
// a symolic reference and the symbol_table
// Returns: 1 if the symbol is in the table
// or a 0 if it is not.

int fwd_ref(string &s, map<string, int> m)
{
    return (m.find(s) == m.end());
}