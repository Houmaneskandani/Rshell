
#include "../header/output_redirect.h"
#include "../header/interface.h"
#include "../header/connector.h"
#include "../header/parse.h"
#include <sstream> 
#include <iostream>
#include <string>
#include <vector>
#include<stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 
using namespace std;

class Interface;
class Connector;

bool OutputRedirect::execute() {
    //put everything in filename to file_desc
    // O_Creat is used to create file if it doesnt' exist
    class Action act;
    act.file_desc = open(filename.c_str(), O_WRONLY | O_CREAT);
    //stdout into output
    act.dup_input = dup(1);

    //checking error, sends things filename into the stdin
    if(dup2(act.file_desc,1) == -1)
    {
       perror("error on create dup");
       return false;
    }
    //use to return bool
    bool determine = left->execute();
    //reset stdin back to original
    dup2(act.dup_input, 1);
    //close the file
    close(act.file_desc);
    return determine;
} 


   // return (left->execute() && right->execute());

string OutputRedirect::getCommand() {
   return left->getCommand() + " > " + filename;
}

