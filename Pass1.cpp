#include "helper.h"
#include "Convert.h"
#include "Pass1.h"

#include <map>
#include <string>
#include <queue>
#include <fstream>

int Pass1(queue<string> oFiles, map<string, string, string> symbolTable, valueTable values, queue<string> segments){
    
   /* //open all of the object files
    for (int i = 0; i < oFiles.size(); i++){
        string filename = "in_file";
        filename += i;

        ifstream file_in(filename.c_str(), ifstream::in);
    }
    */ //not necessary at all?


    //get program name for first segment. put in valueTable->progName
    
    //read them all into the segments data structure
    for (unsigned int i = 0; i < oFiles.size(); i++){
        string filename = "in_file";
        filename += i;
		filename += ".o";

		ifstream file_in(filename.c_str(), ifstream::in);//open the i-th oFile
        while (!file_in.eof()){
			string line;
            getline(file_in, line);
            segments.push(line);
        }
    }
    
    //check that they are all relocatable
    for (unsigned int i = 0; i < oFiles.size(); i++){
 //       check that load address is 0;
    }
    
    //calculate program size
    int segSize = 0;
    for (unsigned int i = 0; i < oFiles.size(); i++){
 //       segSize = length in header record of segment//////////////////
        values.programSize += segSize;
    }
    
    //caluclate page
    string page = segments.front(); //get header record from first segment
    //do some manipulation to get page value out/////////////////////////
    values.page = to_int(page);
    /*
    detect page boundary errors;
    for (each segment){
        calculate PLA;
        add ENT symbols to symbol table;
        warn id duplicates found;
    }*/
	return 0;
}