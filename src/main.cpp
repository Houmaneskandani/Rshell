#include <sstream> 
#include <iostream>
#include <string>
#include <vector>
#include "../header/command.h"
#include "../header/and.h"
#include "../header/semicolon.h"
#include "../header/and.h"
#include "../header/or.h"
#include "../header/parse.h"
#include "../header/input_redirect.h"
#include "../header/output_redirect.h"
#include "../header/output_redirect_append.h"

using namespace std;

int main()
{
    int exit = 0; //use to get out of loop
    cout <<"welcome to rshell"<<endl;
    
    //continue parse user until exit
    while(exit !=1)
    { 
        Action job;   //contains all function
        cout << "$ ";
        string line;
        bool fail;
        //cout << line << endl;
        getline(cin,line);      //get user input 
        vector <string> token;  //store user input
        
        job.parsing(line);//parsing user input
        
        token = job.token;
        //////////////EXIT THE PROGRAM IF EXIT EXIST////////////////////////////
        for (int i = 0; i < token.size(); i++)
        {
            if ( token[i] == "exit")
            {
                exit = 1;
            }
        } 
        //do exit if exit in the parse       
        if (exit == 1)
        {
            break;
        }
        ///////////////END OF EXIT THE PROGRAM IF EXIT EXIST/////////////////////

        job.quotation(); //handle quotation 
        exit = job.exit;
        if (exit == 1)
        {
            break;
        }
        //check exit
        job.split_connector();//split connector into different vector  
        exit = job.exit;
        if (exit == 1)
        {
            break;
        }
        fail = job.is_order();
        if (fail == false)
        {
            cout << "uneven parenthesis" <<endl;
            continue;
        }
        /*
        for (int i = 0; i < job.input.size(); i++)
        {
            cout << job.input[i] <<endl;
        } 
        cout << "end of input " <<endl;
        for (int i = 0; i < job.connect.size(); i++)
        {
            cout << job.connect[i] <<endl;
        }
        cout << "end of connector" << endl; 
        */

        //check exit
        


        job.connector_operation(); //execute argument and quit if user wants
        exit = job.exit;
        //exit = 1;
    }    
    return 0;
}
