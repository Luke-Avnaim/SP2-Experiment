#include "SP1.h"
#include "Tokenizer.h"
#include "Convert.h"
#include "Print.h"
#include "Test.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
#include <sstream>
//#include <boost/algorithm/string.hpp>


using namespace std;

// ---------------------------------------
// return int main(int argc, char *file_list[])
// ---------------------------------------

/*
bool SP1::is_valid_label(string label)
{
    bool successful = true;

    if((label.length() > 6) || (label.length() < 0))
    {
        successful = false;
    }

    for(unsigned int i = 0; i < label.length(); i++)
    {
        if(!isalnum(label[i]))
        {
            successful = false;
        }
    }

    if(label[0] == 'R' || label[0] == 'x')
    {
        successful = false;
    }

    return successful;
}
*/



SP1::SP1()
{
// default contstructor
}

int SP1::Run(int argc, string& file_in, string& file_out)
{

    // -----------------------------------------------------------------------------
    // Use a provided file names and attempt to open files to read from and write to
    // -----------------------------------------------------------------------------

    // *** Input file ***

    // Check that a file name was provided
    if (argc < 2)
    {
        cout << "No file name provided" << endl;
        return 1;	// If no file name exit program
    }

    // Try to open the file from agument passed

	ifstream in_file(file_in.c_str(), ifstream::in);//create and open input file

	ofstream out_file (file_out.c_str(), ifstream::out);//create and open output file

    // Check that we opened the file
	bool val = in_file.is_open();
    if (!val)
    {
        cout << "Error opening file: " << file_in << endl;
        return 1;	// If file not opened exit program
    }

	if (!out_file.is_open())
    {
        cout << "Error opening file: " << file_out << endl;
        return 1;	// If file not opened exit program
    }

    if(!in_file.eof())//only enter the file while there's still something there
        //should take care of empty files
    {

        // -----------------------------------------------------------------------
        // Thow away all comment lines until the first non comment line is reached
        // -----------------------------------------------------------------------

        string line;
        int ln = 0;
        getline(in_file, line);
        ln++;
        while (line.find_first_of(";") == 0)
        {
            // ***If there are spaces before the ";" this will be a problem.***
            getline(in_file, line);
            ln++;
        }

        // ------------------------------------------------------------
        // Check that the first non comment line is the psuedo op .ORIG
        // ------------------------------------------------------------

        string token;	// String to hold tokens
        queue<string> q;	// Queue to hold strings of tokens

        StringTokenizer token_test(line);
        // Read the first non comment line into a queue of tokens
        line = token_test.strip_line(line);	// Strip Comments

        q = token_test.get_tokens(line);	// Get a queue of token strings from the current line

        // Get the .ORIG label *** Manditory
        string orig_label;	// String for .ORIG label
        orig_label = q.front();	// .ORIG label should be at front of queue
        q.pop();	// pop to the next token, should be .ORIG

        // Check that the label valid
        if (!is_valid_label(orig_label))
        {
            cout << ln << " .ORIG does not have a valid label!\n" << endl;
            return 0;
        }

        // If the .ORIG op is not present exit program
        if (q.front() != ".ORIG")  	// .ORIG should now be in front of queue
        {
            cout <<ln << " First non comment line is NOT .ORIG: " << q.front() << endl;
            return 1;	// If not, exit the program
        }
        else     // If so, pop to next token
        {
            q.pop();	// If there is another value in the queue
        }	// it is the address for location counter

        // Testing stuffs
        //cout << to_hex(to_int(q.front()));
        //return 0;

        // -------------------------------------------------
        // Initalize Location Counter, 0 if no address given
        // -------------------------------------------------

        int lc = 0;	// Default value of 0
        if (!q.empty())  	// If there is an address given
        {
            lc = to_int(q.front());// Convert from string hex to int
            if (lc > 0xFFFF)
            {
                cout << ln <<" .ORIG out of range.\n";
                return 1;
            }
            q.pop();
        }

        // ------------------
        // Store segment info
        // ------------------

        // orig_label - done
        int origin_address = lc;

        // ------------------------------------------------------------------------
        // Read next line of input and store tokens in a queue
        // Process each queue of token into a record
        // Iterate over each line in the file doing this until a .END line is found
        // ------------------------------------------------------------------------

        getline(in_file, line);// Read the next line from the file
        ln++;
        while (line[0] == ';')
        {
            getline(in_file, line);
            ln++;
        }
        line = token_test.strip_line(line);	// Strip comments
        string orig_line = line; // Create duplicate line for printing user listing
        q = token_test.get_tokens(line);	// Get a queue of tokens from the line

        map<string, int> symbol_table;	// Create Symbol table
        map<string, int> literal_table;	// Create Literal table
        queue<string> records;	// Create queue for records

        string heading;
        heading += "H";
        heading += to_hex(lc);
        records.push(heading);

        // WHILE (not at .END line)
        while (q.front() != ".END")
        {

            string opcode;	// String to hold the OpCode
            string record;	// String to hold records

            // -----------------------------------------------
            // Check for a label at the front of the queue
            // If there is a label add it to the symbol table
            // If not, assume it is an OpCode
            // -----------------------------------------------
            string label; //declare a string to hold the label
            if (!is_op_code(q.front()))  	// If the front of the queue is not a OpCode
            {
                if (is_valid_label(q.front()))  	// It must be a symbol - but dbl check
                {

                    label = q.front();	// Get the label
                    q.pop();	// Pop to the next token
                    opcode = q.front();	// It should be a OpCode
                    q.pop();	// Pop to the next token

                    if (!symbol_table.count(label) && symbol_table.size()<99)  	// If the symbol is not already in the t
                    {
                        symbol_table[label] = lc;	// Insert the symbol and address
                    }
                    else  	// Else the symbol exists, exit program
                    {
                        cout << ln << " Duplicate symbol found or table too large\n" << endl;
                        return 1;
                    }
                }
                else     // Its not a valid label
                {
                    cout << ln << " Invalid label: " << q.front() << endl;
                    return 1;	// Exit program
                }
            }
            else
            {
                opcode = q.front();	// Else there was no label and the front of
                q.pop();	// queue is already the opcode
            }

            // ---------------------------------------------------------------
            // Match the OpCode of the current line and handle it appropriately
            // Whatever that means...
            // ---------------------------------------------------------------

            // IF (instruction in Machine Op Table or Pseudo Op Table)
            if (opcode == "AND")   // increment Location Counter appropriately
            {

                record += "T";	// Add T identifier
                record += to_hex(lc);	// Add Address
                record += "5";	// Add "AND" code
                record += to_reg(q.front());	// Add DR
                q.pop();
                record += to_reg(q.front());	// Add SR
                q.pop();
                string str = q.front();
                if (str[0] == 'R')
                {
                    record += to_reg(str);
                }
                else
                {
                    record += "1";	// Add a "1"
                    int address = to_int(str);	// Convert the address to integer
                    record += to_hex(address);	// Convert the address to padded hex
                }
                lc++;	// Increment the Location Counter
            }
            else if (opcode == "ADD")
            {

                record += "T"; // ADD T identifier
                record += to_hex(lc); // ADD Address
                record += "1"; // ADD "ADD" code
                record += to_reg(q.front()); //ADD DR
                q.pop();
                record += to_reg(q.front()); //ADD SR1
                q.pop();
                string str = q.front();
                if (str[0] == 'R')   //check if next token is register
                {
                    record += to_reg(str); //ADD SR2
                }
                else if (str[0] == '#' || str[0] == 'x')     // token is a immediate
                {
                    record += to_reg(str);
                }
                else  	// is a symbol
                {
                    record += "SYM_";
                    record += str;
                }
                lc++; //increment location counter
            }

            else if (opcode == "NOT")
            {
                record += "T"; // Add T identifier
                record += to_hex(lc); // Add Address
                record += "9"; // Add "ADD" code
                record += to_reg(q.front()); //Add DR
                q.pop();
                record += to_reg(q.front()); //Add SR
                q.pop();
            }
            else if (opcode == "BRN")
            {
                record += "T";
                record += "08";
                if ((q.front()[0] != 'x') && (q.front()[0] != '#'))
                {
                    record += "SYM_";
                }
                record += q.front();
                lc++;
            }
            else if (opcode == "BRZ")
            {
                record += "T";
                record += "04";
                if ((q.front()[0] != 'x') && (q.front()[0] != '#'))
                {
                    record += "SYM_";
                }
                record += q.front();
                lc++;
            }
            else if (opcode == "BRP")
            {
                record += "T";
                record += "02";
                if ((q.front()[0] != 'x') && (q.front()[0] != '#'))
                {
                    record += "SYM_";
                }
                record += q.front();
                lc++;
            }
            else if (opcode == "BRNZ")
            {
                record += "T";
                record += "0C";
                if ((q.front()[0] != 'x') && (q.front()[0] != '#'))
                {
                    record += "SYM_";
                }
                record += q.front();
                lc++;
            }
            else if (opcode == "BRNP")
            {
                record += "T";
                record += "0A";
                if ((q.front()[0] != 'x') && (q.front()[0] != '#'))
                {
                    record += "SYM_";
                }
                record += q.front();
                lc++;
            }
            else if (opcode == "BRZP")
            {
                record += "T";
                record += "05";
                if ((q.front()[0] != 'x') && (q.front()[0] != '#'))
                {
                    record += "SYM_";
                }
                record += q.front();
                lc++;
            }
            else if (opcode == "JSR")
            {

                record += "T";	// Add T identifier
                record += to_hex(lc);	// Add address
                record += "48";	// Add "JSR" code
                q.pop();	// get next token (immediate value)

                if ((q.front()[0] != 'x') && (q.front()[0] != '#'))
                {
                    record += "SYM_";
                }
                record += q.front();
                lc++; // increment location counter
            }
            else if (opcode == "LD")
            {
                record += "T"; // Add T identifier
                record += to_hex(lc);	// Add Address
                record += "2";	// Add "LD" code
                record += to_reg(q.front()); // Add DR

                q.pop(); // get next token
                if (q.front()[0] == '=')   // is a literal
                {
                    record += "LIT_"; // add "LIT_"
                    record += to_reg(q.front());	// get rid of '=' and add "#<number>"
                }
                else if ((q.front()[0] != 'x') && (q.front()[0] != '#'))
                {
                    record += "SYM_";
                    record += q.front();
                }
                else
                {
                    record += q.front();
                }
                lc++; // increment location counter
            }
            else if (opcode == "ST")
            {

                record += "T";	// Add T identifier
                record += to_hex(lc);	// Add address
                record += "3";	// Add "ST" code
                record += to_reg(q.front());	// ADD SR
                q.pop();	// get next token
                record += q.front();
                lc++; // increment location counter
            }
            else if (opcode == "LDI")
            {

                record += "T";	// Add T identifier
                record += to_hex(lc);	// Add address
                record += "A";	// Add "LDI" code
                record += to_reg(q.front());	// ADD DR
                q.pop();	// get next token
                if ((q.front()[0] != 'x') && (q.front()[0] != '#'))
                {
                    record += "SYM_";
                }
                record += q.front();
                lc++;	// increment location counter
            }
            else if (opcode == "STI")
            {

                record += "T";	// Add T identifier
                record += to_hex(lc);	// Add address
                record += "B";	// Add "STI" code
                record += to_reg(q.front());	// ADD SR
                q.pop();	// get next token
                if ((q.front()[0] != 'x') && (q.front()[0] != '#'))
                {
                    record += "SYM_";
                }
                record += q.front();
                lc++;	// increment location counter
            }
            else if (opcode == "LEA")
            {

                record += "T";	// Add T identifier
                record += to_hex(lc);	// Add address
                record += "E";	// Add "LEA" code
                record += to_reg(q.front());	// ADD DR
                q.pop();	// get next token
                if ((q.front()[0] != 'x') && (q.front()[0] != '#'))
                {
                    record += "SYM_";
                }
                record += q.front();
                lc++;	// increment location counter
            }
            else if (opcode == "JSRR")
            {

                record += "T";	// Add T identifier
                record += to_hex(lc);	// Add address
                record += "C4";	// Add "JSRR" code
                record += to_reg(q.front());	// ADD DR
                q.pop();	// get next token
                record += to_reg(q.front());	// ADD BR

                q.pop(); // get next token
                if ((q.front()[0] != 'x') && (q.front()[0] != '#'))
                {
                    record += "SYM_";
                }
                record += q.front();
                lc++; // increment location counter
            }
            else if (opcode == "RET")
            {
                record += "D";
                lc++;
            }
            else if (opcode == "TRAP")
            {
                record += "T";
                record += to_hex(lc);
                record += "F";
                if ((q.front()[0] != 'x') && (q.front()[0] != '#'))
                {
                    record += "SYM_";
                }
                record += q.front();
                lc++;
            }
            else if (opcode == "LDR")
            {

                record += "T";	// Add T identifier
                record += to_hex(lc);	// Add address
                record += "6";	// Add "LDR" code
                record += to_reg(q.front());	// ADD DR
                q.pop();	// get next token
                record += to_reg(q.front());	// ADD BR

                q.pop(); // get next token
                if ((q.front()[0] != 'x') && (q.front()[0] != '#'))
                {
                    record += "SYM_";
                }
                record += q.front();
                lc++; // increment location counter
            }
            else if (opcode == "STR")
            {

                record += "T";	// Add T identifier
                record += to_hex(lc);	// Add address
                record += "7";	// Add "STR" code
                record += to_reg(q.front());	// ADD DR
                q.pop();	// get next token
                record += to_reg(q.front());	// ADD BR

                q.pop(); // get next token
                if ((q.front()[0] != 'x') && (q.front()[0] != '#'))
                {
                    record += "SYM_";
                }
                record += q.front();
                lc++; // increment location counter
            }
            else if (opcode == ".EQU")
            {
                ////////////////////////////THIS SUCKS
                if (fwd_ref(q.front(), symbol_table))
                {
                    cout << ln << " Illegal forward reference";
                    return 1;
                }
                if ((to_int(q.front()) <- 32768) || (to_int(q.front()) > 32767))
                {
                    symbol_table[label] = to_int(q.front()); //Add the token following .EQU to the symbol table
                    q.pop(); //Get rid of the token
                }
                else
                {
                    cout << ln << " .EQU out of range.\n";
                    return 1;
                }
            }
            else if (opcode == ".FILL")
            {
                if (q.front()[0] == 'x')
                {
                    if (to_int(q.front()) < 0 || to_int(q.front()) > 65535)
                    {
                        cout << ln <<" .FILL out of range (hex)\n";
                        return 1;
                    }
                }
                else if (q.front()[0] == '#')
                {
                    if (to_int(q.front()) <- 32768 || to_int(q.front())>32767)
                    {
                        cout << ln <<" .FILL out of range (dec)\n";
                        return 1;
                    }
                }
                record += "T"; //Add T identifier
                record += to_hex(lc); //Add address
                record += q.front(); //Add immediate value
                q.pop(); //Get rid of immediate token
            }
            else if (opcode == ".STRZ")
            {
                record += "T"; //Add T identifier
                string str = q.front(); //Copy front token into a string
                q.pop(); //Get rid of front token
                int ascii;
                string ascii_string;
                for (unsigned int i = 1; i < str.length(); i++)
                {
                    record += to_hex(lc); //Add address
                    ascii = int(str[i]); //Get the ascii value at position i and convert to int
                    ascii_string = to_hex(ascii); //Convert the ascii int to hex
                    record += "x00"; //First half of each word is filled with 0's
                    record += ascii; //Second half of the word is the hex ASCII value
                    records.push(record); // Push the record into the queue
                    record.clear(); //Clear the record to start a new record
                    lc++; //Increment the location counter
                }

                record += to_hex(lc); //Add adrress
                record += "x0000"; //Follow the last character with NULL
                lc++; //Increment the location counter
            }
            else if (opcode == ".BLKW")
            {
                record += to_hex(lc);
                symbol_table[label] = lc; //Set label to current value of location counter
                for (int numberOfWords = to_int(q.front()); numberOfWords>0; numberOfWords--)
                {
                    //Increment the location counter once for every word reserved
                    lc++;
                }
            }
            else if (opcode == "DBUG")
            {
                record += "x8000";
            }
            else     // No OpCode matched
            {
                cout << ln << "OpCode not matched: " << opcode << endl;
                return 1; // Exit program, invalid instruction
            }

            record += " ";
            record += orig_line;
            records.push(record); // Push the record into the queue

            // IF (operand contains a literal
            // add literal to Literal Table:
            // -- avoid duplicat entries
            // -- set the name and value
            // END IF

            // --------------------------------------------------------------
            // Get next set of tokens and return to the top of the while loop
            // --------------------------------------------------------------
            getline(in_file, line);// Read the next line from the file
            ln++;
            while (line[0] == ';')
            {
                getline(in_file, line);
                ln++;
            }
            line = token_test.strip_line(line);	// Remove comments
            orig_line = line; // Duplicate line for printing user listing
            q = token_test.get_tokens(line);	// Get a queue of tokens from the line

        } // END WHILE

        // -------------------------
        // set addresses of literals
        // -------------------------

        // blah
        //-------------------------------
        //Outputs symbol and literal tables
        //---------------------------------

        print_map(symbol_table);
        print_map(literal_table);

        int segment_length = lc - origin_address + literal_table.size();
        cout << "Segment Length: " << segment_length << endl;
        // --------------------------------
        // Write lines to intermediate file
        // --------------------------------

        // out_file << data;

        // use Location Counter to calculate program length

        print_records(records);

    }

    else
    {
        cout << "Error. Possibly empty file.\n";
        return 1;
    }

    in_file.close(); // Close files
    // out_file.close();

    return 0;	// Exit program
}
