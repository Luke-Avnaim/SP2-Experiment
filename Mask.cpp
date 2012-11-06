// File: masking.cpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

enum { BRx, ADD, LD, ST, JSR, AND,
       LDR, STR, DBUG, NOT, LDI,
       STI, JSSR, RET, LEA, TRAP
     };


string formatA(string);
string formatB(string);
string formatC(string);
string formatD(string);
string formatE(string);

string masking(string record)
{
    int OPCODE;

    string rout;

    record = "Tx302121x3026";
    OPCODE = atoi(record.substr(6, 1).c_str());

    switch (OPCODE)
    {
    case BRx:
        rout = formatD(record);
        //cout << "BRx: " << formatD(record) << endl;
        break;
    case ADD:

        if (atoi(record.substr(9, 1).c_str()) == 0)
        {
            rout = formatA(record);
            //cout << "ADD: " << rout << endl;
        }

        if (atoi(record.substr(9, 1).c_str()) == 1)
        {
            rout = formatB(record);
            //cout << "ADD: " << rout << endl;
        }

        break;
    case LD:
        rout = formatD(record);
        //cout << "LD: " << rout << endl;
        break;
    case ST:
        rout = formatD(record);
        //cout << "ST: " << rout << endl;
        break;
    case JSR:
        rout = formatD(record);
        //cout << "JSR: " << rout << endl;
        break;
    case AND:
        rout = formatA(record);
        //cout << "AND: " << rout << endl;
        //formatB(record);
        break;
    case LDR:
        rout = formatA(record);
        //cout << "LDR: " << rout << endl;
        break;
    case STR:
        rout = formatC(record);
        //cout << "STR: " << rout << endl;
        break;
    case DBUG:
        //cout << "DBUG: " << record << endl;
        //...
        break;
    case NOT:
        //cout << "NOT: " << record << endl;
        //...
        break;
    case LDI:
        rout = formatD(record);
        //cout << "LDI: " << rout << endl;
        break;
    case STI:
        rout = formatD(record);
        //cout << "STI: " << rout << endl;
        break;
    case JSSR:
        rout = formatC(record);
        //cout << "JSSR: " << rout << endl;
        break;
    case RET:
        rout = record;
        //cout << "RET: " << record << endl;
        //...
        break;
    case LEA:
        rout = formatD(record);
        //cout << "LEA " << rout << endl;
        break;
    case TRAP:
        rout = formatE(record);
        //cout << "TRAP: " << rout << endl;
        break;
    default:
        rout = record;
        //...
        break;
    }

    return rout;

}

/* Format A
* -------------------------------------------------------------
* | 15 14 13 12 | 11 10 09 | 08 07 06 | 05 | 04 03 | 02 01 00 |
* |-------------|----------|----------|----|-------|----------|
* | OPCODE | R | R | 0 | X X | R |
* -------------------------------------------------------------
*/

string formatA(string s)
{
    string address = s.substr(2, 4);
    string opcode = s.substr(6, 1);
    string reg1 = s.substr(7, 1);
    string reg2 = s.substr(8, 1);
    string reg3 = s.substr(10, 1);
    return address + opcode + reg1 + reg2 + reg3;
}

/* Format B
* -----------------------------------------------------------
* | 15 14 13 12 | 11 10 09 | 08 07 06 | 05 | 04 03 02 01 00 |
* |-------------|----------|----------|----|----------------|
* | OPCODE | R | R | 1 | IMM5 |
* -----------------------------------------------------------
*/

string formatB(string s)
{
    string address = s.substr(2, 4);
    string opcode = s.substr(6, 1);
    string reg1 = s.substr(7, 1);
    string reg2 = s.substr(8, 1);
    string imm5 = s.substr(9, s.size());
    return address + opcode + reg1 + reg2 + imm5;
}

/* Format C
* ---------------------------------------------------------
* | 15 14 13 12 | 11 10 09 | 08 07 06 | 05 04 03 02 01 00 |
* |-------------|----------|----------|-------------------|
* | OPCODE | R | R | INDEX6 |
* ---------------------------------------------------------
*/

string formatC(string s)
{
    string address = s.substr(2, 4);
    string opcode = s.substr(6, 1);
    string reg1 = s.substr(7, 1);
    string reg2 = s.substr(8, 1);
    string index6 = s.substr(9, s.size());
    return address + opcode + reg1 + reg2 + index6;
}

/* Format D
* -------------------------------------------------------
* | 15 14 13 12 | 11 10 09 | 08 07 06 05 04 03 02 01 00 |
* |-------------|----------|----------------------------|
* | OPCODE | R | PGOFFSET9 |
* -------------------------------------------------------
*/

string formatD(string s)
{
    string address = s.substr(2, 4);
    string opcode = s.substr(6, 1);
    string reg = s.substr(7, 1);
    string pgoffset = s.substr(8, s.size());
    return address + opcode + reg + pgoffset;
}

/* Format E
* -------------------------------------------------------
* | 15 14 13 12 | 11 10 09 08 | 07 06 05 04 03 02 01 00 |
* |-------------|-------------|-------------------------|
* | OPCODE | X X X X | TRAPVECTOR8 |
* -------------------------------------------------------
*/

string formatE(string s)
{
    string address = s.substr(2, 4);
    string opcode = s.substr(6, 1);
    string trapvector8 = s.substr(7, s.size());
    return address + opcode + trapvector8;
}
