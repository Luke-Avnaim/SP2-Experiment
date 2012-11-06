// File: SP2.cpp

#include "SP2.h"

#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <map>
//#include <boost/lexical_cast.hpp>


using namespace std;

//begin

int SP2::Run(queue<string> q, map<string, int> sym,
        map<string, int> lit, int lc)
{
//output header record to object file

    ofstream obj_file("objects.txt");

    obj_file << q.front() << endl;

//read in first line from intermediate file

    q.pop();

//while (not done with intermediate file)

    while(!q.empty())
    {

        string base = q.front();

//if (there are symbols in the operands)

        size_t s = base.find("SYM_");
        if(s != string::npos)
        {

            std::string symbol;
            symbol.assign(base, s+4, 10);

//replace symbols with their value from Symbol Table

            if(sym.count(symbol))
            {

                map<string,int>::iterator it;
                it = sym.find(symbol);

//                symbol.assign(boost::lexical_cast<std::string>(it->second));
            }
            else //- report an error if not present
                cout << "Symbol not present in table." << endl;

        } //endif

//if (there are literals in the operands)

        s = base.find("LIT_");
        if(s != string::npos)
        {

            string literal;
            literal.assign(base, s+4, 10);

//replace literal with its address from Literal Table

            if(lit.count(literal))
            {

                map<string,int>::iterator it;
                it = lit.find(literal);

//                literal.assign(boost::lexical_cast<std::string>(it->second));
            }
            else //- report an error if not present
                cout << "Literal not present in table." << endl;

        } //endif


//assemble line


//output line (text record) to object file

        obj_file << base << endl;

//output line to listing file

        ofstream list_file("user_listing.txt");

//read in next line from intermediate file

        q.pop();

    } //end while
return 0;
} //end
