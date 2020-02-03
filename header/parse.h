#ifndef __PARSE_H__
#define __PARSE_H__

#include <sstream> 
#include <iostream>
#include <string>
#include <vector>

#include "testcommand.h"

using namespace std;

//vector<string> parsing(string input);

//quotation(vector<std::string> *token);

class Action
{
    public:
        ////shared variable
        vector<string> token;
        vector<string> input; //argument
        vector<string> connect; //connector
        //redirection
        int file_desc; 
        int dup_input;

        
        int exit = 0; 
        ////working function
        //parse user input into vector of strings
        //example:  ls && echo "hello world"  ->    vector = {ls, &&, echo, "hello, world"}
        void parsing(string input);

        //handle quotation
        //  ;   #   are also handled here if it is not seperate by space such as   ls#hello      ls;ls
        //example:  vector = {ls, &&, echo, "hello, world"}   ->    vector = {ls, &&, echo, hello world}  
        void quotation();

	//This function should handle any test command including it's flags.	
	void test();

        //seperate connector from argument
        //example:  vector = {ls, &&, echo, hello world}    ->        
        //                       vector input = {ls, echo hello word}
        //                       vector connnect = {&&,}
        void split_connector();
        
        //do connector operation from input and connect, also end the loop if needed
        //handle connector such as &&   ||  ;   #
        //example: vector input = {ls, echo hello word}
        //         vector connnect = {&&,}     ->
        //              execvp(ls)
        //              execvp(echo hello world)
        void connector_operation();

        bool is_order();
        bool is_order(string input);

        bool new_connect();

        
    private:
        
};



#endif
