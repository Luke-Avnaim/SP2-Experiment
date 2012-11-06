// File: SP3.cpp

//#include "SP3.h"

#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <map>
//#include <boost/lexical_cast.hpp>
#include "Convert.h"
#include "Pass1.h"
#include "Pass2.h"

using namespace std;

int main(int argc, char *argv[]){
    
	//create the valueTable values
	valueTable values;

    //------copy the input into data structures for passing to Pass1 and Pass2----------
    queue<string> oFiles;

    //get the object file names
    for (int i = 1; i < argc - 1; i++){
        string fileName = argv[i];
        oFiles.push(fileName);
    }
    //get the IPLA

    if (to_int(string(argv[argc])) % 2 == 0){
        values.IPLA = to_int(string(argv[argc]));
    }
    else {
        //error(code); /////////////Need to establish error subroutine and error codes
    }
    
    //-------------------------Pass 1---------------------
    //Create symbol table. Values: symbol, value, abs/rel/ext (convention: A/R/E)
    map<string, string, string> symbolTable;
    //Create array of queues of strings to hold each segment
    queue<string> segments;
    //Call pass 1
    Pass1(oFiles, symbolTable, values, segments);
          
    //-------------------------Pass 2---------------------
    //Create queue "prog" to hold the final output
    queue<string> prog;
    //call pass 2
    Pass2(values, symbolTable, segments, prog);
          
    //------------------Pretty print output---------------
    for (unsigned int i = 0; i < prog.size(); i++){
        printf("%s\n", prog.front());
        string temp = prog.front();
        prog.push(temp);
    }
    
    //-----------------Write output to file---------------
    //create and open output file
	string file_out = "textoutput1.txt";
    ofstream out_file (file_out.c_str(), ifstream::out);
    //check that the output file is open
    if (!out_file.is_open())
    {
        //error(code);////////////////////////////////needs attention
    }
    //write each line
    string line;
    for (unsigned int i = 0; i < prog.size(); i++){
        line = prog.front();
        prog.pop();
        out_file << line << "\n";
        prog.push(line);
    }
}
