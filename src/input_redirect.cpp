#include "../header/input_redirect.h"
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

bool InputRedirect::execute() {
    //put everything in filename to file_desc
    class Action act; 
    act.file_desc = open(filename.c_str(), O_RDONLY);
    //stdin into input
    act.dup_input = dup(0);

    //checking error, sends things filename into the stdin
    if(dup2(act.file_desc,0) == -1)
    {
       perror("error on create dup");
       return false;
    }
    //use to return bool
    bool determine = left->execute();
    //reset stdin back to original
    dup2(act.dup_input, 0);
    //close the file
    close(act.file_desc);
    return determine;
} 

string InputRedirect::getCommand() {
   return left->getCommand() + " < " + filename;
}

