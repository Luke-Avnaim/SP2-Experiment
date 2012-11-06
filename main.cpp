/* ----------------------------------------------------------
* File: main.cpp
*
* Class: CSE3903 Proj: Sys Software
*
* Authors: Aaron Russell, russell.701@buckeyemail.osu.edu
* Grant Michalski, michalski.26@buckeyemail.osu.edu
* Luke Avnaim, avnaim.1@osu.edu
* Mike McDonald, mcdonald.346@buckeyemail.osu.edu
* ----------------------------------------------------------
*/

#include "Convert.h"
#include "Print.h"
#include "SP1.h"
#include "SP2.h"
#include "Tokenizer.h"

using namespace std;

int main()
{

//test_charstar[0] is self, [1] is input file, [2] is output file
    string file_in, file_out;
    queue<string> test_queue;
    int test_int = 2; //where does this number come from? size of argv[]?
    map<string, int> test_map;

    file_in = "testinput1.txt";
    file_out = "testoutput1.txt";


    SP1 sp1;
    if(sp1.Run(test_int, file_in, file_out) != 1)
    {
        //SP2 sp2;
        //sp2.Run(test_queue, test_map, test_map, test_int);
    }
    else
    {
        return 1;
    }

//SP3();
    return 0;
}
