#include "helper.cpp"
#include "Pass2.h"
#include <map>
#include <string>
#include <queue>
#include <sstream>

int Pass2(valueTable values, map<string, string, string> symbolTable, queue<string> segments, queue<string> prog){

    //generate the program header record
    std::stringstream Stream;
    Stream << "H" << values.progName << values.IPLA << values.programSize;
    std::string s = Stream.str();
    prog.push(s);
    
    for (unsigned int i = 0; i < segments.size(); i++){
        for (unsigned int j = 0; j < segments.size(); j++){
            //get text record
            string str = segments.front();
            segments.pop();
            //if there is a symbol replace it with the value in the symbol table
            //else pull memory location out of text record
  /*          if (its absolute ){
                dont do anything;
            }
            else{
                add SLA;
            }
  */
            //put updated record back in segment queue
            segments.push(str);
        }
    }
    
    //generate the final program
    for (unsigned int i = 0; i < segments.size(); i++){
        for (unsigned int j = 0; j < segments.size(); j++){
            string str = segments.front();
            segments.pop();
            prog.push(str);
            segments.push(str);
        }
    }

return 0;
}

/*
 Pass 2 pseudo code
 
set IPLA;
for (each segment){
    calculate memory location;
    relcoate record (abs = do nothing, relative = add SLA, external = add symbol value);
 }
    
}*/