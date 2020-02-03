#include <sstream> 
#include <iostream>
#include <string>
#include <vector>
#include "../header/parse.h"
#include "../header/command.h"
//#include "../header/connector.h"
#include "../header/and.h"
#include "../header/semicolon.h"
#include "../header/and.h"
#include "../header/or.h"
#include "../header/parse.h"
#include "../header/input_redirect.h"
#include "../header/output_redirect.h"
#include "../header/output_redirect_append.h"
#include "../header/pipe.h"

using namespace std;

void Action::parsing(string input)
{
    //vector <string> token; 
    // stringstream class check1 
    stringstream check1(input); 
    string intermediate; 
    // Tokenizing w.r.t. space ' ' 
    // Vector of string used to save splitted user input string 
    while(getline(check1, intermediate, ' ')) 
    { 
        token.push_back(intermediate); 
    }   
}

void Action::quotation()
{
    string quotation;
    int switching = 0;
    int stop;
    int lock= 0;
    int i = 0;
    while(i != token.size())
    {

        lock = 0;
        size_t found3 = token[i].find("\"");
        size_t found5 = token[i].find("#");
        if (found3 != string::npos && switching == 0) //if find " and switch is off
        {
            lock = 1;
            //cout <<"delete left \"" <<endl;
            //turn on switching
            switching = 1;
            //remove the "
            token[i].erase(token[i].begin());
            //set stop
            //cout << "find left quotation: " << token[i] << endl; ///////this works
            lock = 1;
            stop = i;
        }
        found3 = token[i].find("\"");
        if (stop != i && found3 == string::npos && switching == 1) //if in next input and  didn't find " and switch is open
        {
          //  cout << "in middle, delete copy one" <<endl;
            //push element at the end of element that stop at
        //    cout << token[i] << endl;
            token[stop].append(" ");
            token[stop].append(token[i]);
            token.erase(token.begin()+i);
            lock = 1;
            i--;
        }
        found3 = token[i].find("\"");
        //handle # in the input
        //find # in the input and it is not a echo """ argument
        if (found5 != string::npos && switching == 0)
        {
            //cout <<" going here" << endl;
            int input_size = token[i].size();
            for(size_t h = found5; h < input_size; h++)
            {
                //take out everything after # in a input
                token[i].pop_back();
            }
            //remove everything after #
            input_size =  token.size();
            for(int q = i + 1; q < input_size; q++)
            {
                token.pop_back();
            }
        }
        if (found3 != string::npos && switching == 1) //if find " and switch is open 
        {
            //cout << "found quotation and switch is on: " << token[i] << endl;
            if (stop == i ) //if in same input
            {
                //cout << "stop = i" << endl;
                //cout << "\" \" in the same input" <<endl;
                switching = 0;
                //cout <<"this input is " << token[i] << endl;
                token[i].erase(token[i].begin()+found3);
                lock = 1;
                //cout << token[i] << endl;
                //token[i].erase(token[i].end()); // remove " at the end
                //cout <<"finish the erase in same input" << endl;
            }
            else // in differnt input
            {
                //cout << "at the end, delete right\"" <<endl;
                switching = 0;
                //cout << token[i].at(found3) << endl;
                //cout << token[i] << endl;
                token[i].erase(token[i].begin()+found3); // remove " at the end
                //cout << token[i] << endl;
                //cout << token[i].at(found3-1) << endl;
                //if (token[i].at(found3) != ')')
                //{
                //
                //cout << "now token after right delete is: " << token[i] << endl;
                token[stop].append(" ");
                //}
                token[stop].append(token[i]);
                //cout << "token[stop] is: " << token[stop] <<endl;
                token.erase(token.begin()+i);
                lock = 1;
                i--;
            }
        }

        i++;
        //else



    }
}

//void Action::test_command() {}

void Action::split_connector()
{
    int count = 0;
    int word = 0;
    for (int i = 0; i < token.size(); i++)
    {

        size_t found3 = token[i].find(";");
        if ((found3 != string::npos) || (token[i] == "&&") || (token[i] == "||") || (token[i] == "#" ) || (token[i] == ">") || (token[i] == "<") || (token[i] == ">>") || (token[i] == "|"))
        {
            //if encounter #
            if (token[i] == "#")
            {
                string temp;
                for (int j = word ; j < i; j++)
                {
                temp.append(token[j]);
                temp.append(" ");
                }
                input.push_back(temp);
                //exit = 1;
                break;
            }
            connect.push_back(token[i]);
            string temp;
            for (int j = word ; j < i; j++)
            {
                temp.append(token[j]);
                temp.append(" ");
            }
            input.push_back(temp);
            //count++;
            word = i;
            word +=1;
        }
        if (i == token.size()-1)
        {
            string temp;
            for (int z= word;  z < token.size();z++)
            {
                temp.append(token[z]);
                temp.append(" ");
            }
            input.push_back(temp);
        }
    }

}

void Action::connector_operation()
{
    bool determine; //determine next should run or not
    int origin = input.size();
    //erase the item in input and item in connector if it is used

    bool lp = true; //left parenthesis
    bool rp = true;//right parenthesis
    vector<bool> paren;  //left parenthesis vector
    vector<bool> rv;  //right parenthesis vector
    bool skip = false;
    //there is always a space at the end of each input after connecot_split, pop_back to take it out
    for(int i = 0; i < input.size(); i++)
    {
        input[i].pop_back();
    }

    while(input.size() != 0 && exit != 1)
    {   
        size_t found = (input.front()).find(";");
        size_t found2 = (input.front()).find("#");
        size_t found6 = -1;
        size_t found7 = -1;
        //handle test command
        if (input.front()[0] == 't')
        {
            if (input.front()[1] == 'e')
                {    
                    if (input.front()[2] == 's')
                    {
                        if (input.front()[3] == 't')
                        {
                           if (input.front()[4] == ' ')
                           {

                             //cout <<"found test" <<endl;
                             found6 = (input.front()).find("test");
                           }
                        }
                    }
                }
        }
        else if (input.front()[0] == '[')
        {

            found7 = (input.front()).find("[");
        }
        if ((found6 != string::npos) || (found7 != string::npos))
        {
            //cout << "command testing" << endl;
            Command* command1 = new TestCommand(input.front());
            determine = command1->execute();
            input.erase(input.begin());
        }
        //first execution
        else if ((found2 != string::npos) || (found != string::npos) || (input.size() == origin)) 
        {
            //cout << "first elemtn" << endl;
            if (!connect.empty())
            {
                if((connect.front() == ">") || (connect.front() == "<") || (connect.front() == ">>") || (connect.front() == "|") )
                {
                    //cout <<"special connect" << endl;
                    Command *command1 = new Command(input.front());
                    input.erase(input.begin());
                    Command *command2 = new Command(input.front());
                    string filename = input.front();
                    input.erase(input.begin());
                    if (connect.front() == ">") //output_redirect
                    {
                        Connector *oredirect = new OutputRedirect(command1, filename);
                        determine = oredirect->execute();
                        connect.erase(connect.begin());
                    }
                    else if (connect.front() == "<")
                    {
                        Connector *iredirect = new InputRedirect(command1, filename);
                        determine = iredirect->execute();
                        connect.erase(connect.begin());
                    }
                    else if (connect.front() == ">>")
                    {
                        Connector *oredirecta = new OutputRedirectAppend(command1, filename);
                        determine = oredirecta->execute();
                        connect.erase(connect.begin());
                    }
                    else if (connect.front() == "|")
                    {
                        Connector *pipe = new Pipe(command1, command2);
                        determine = pipe->execute();
                        connect.erase(connect.begin());
                    }
                }
                else
                {
                    size_t found3 = (input.front()).find("("); 
                while(found3 != string::npos)
                {
                // cout << "remove ( " <<endl;
                    bool run = true;
                    paren.push_back(run);
                    input.front().erase(input.front().begin());
                    found3 = (input.front()).find("("); 
                }
                if (found != string::npos)
                {
                    //cout <<"we found ; in the input and it is called " << input.front() <<endl;
                    string replace;
                    for (int i = 0 ; i < found; i++)
                    {
                        replace.push_back((input.front())[0]);
                        input.front().erase(input.front().begin());
                    }
                    input.front().erase((input.front().begin()));
                    Command *command = new Command(replace);
                    command->execute();
                    
                }
                else if (found2 != string::npos)
                {
                 //   cout <<"detect # in the input" <<endl;
                    string replace;
                    for (int u = 0 ; u < found2+1; u++)
                    {
                        replace.push_back((input.front())[0]);
                        input.front().erase(input.front().begin());
                    }
                    Command *command = new Command(replace);
                    command->execute();
                    //exit = 1;
                    break;
                }
                else
                {
                    //if one input is enclose with ()
                    size_t found8 = (input.front()).find(")");
                    if (found8 != string::npos)
                    {
                        while(found8 != string::npos)
                        {
                            input.front().pop_back();
                            paren.pop_back();
                            found8 = (input.front()).find(")");
                        }
                        Command *command = new Command(input.front());
                        determine = command->execute();
                        input.erase(input.begin());
                    }             
                    else
                    {
                        //cout << "it goes here" <<endl;
                        Command *command = new Command(input.front());
                        determine = command->execute();
                        input.erase(input.begin());
                    }
                    // cout << "determine is " << determine << endl;
                    //delete command;
                }
                }            
            }
            else
            {
                //cout << "the first element in the input: " << input.front() << endl;
                size_t found3 = (input.front()).find("("); 
                while(found3 != string::npos)
                {
                // cout << "remove ( " <<endl;
                    bool run = true;
                    paren.push_back(run);
                    input.front().erase(input.front().begin());
                    found3 = (input.front()).find("("); 
                }
                if (found != string::npos)
                {
                    //cout <<"we found ; in the input and it is called " << input.front() <<endl;
                    string replace;
                    for (int i = 0 ; i < found; i++)
                    {
                        replace.push_back((input.front())[0]);
                        input.front().erase(input.front().begin());
                    }
                    input.front().erase((input.front().begin()));
                    Command *command = new Command(replace);
                    command->execute();
                }
                else if (found2 != string::npos)
                {
                    //cout <<"detect # in the input" <<endl;
                    string replace;
                    for (int u = 0 ; u < found2+1; u++)
                    {
                        replace.push_back((input.front())[0]);
                        input.front().erase(input.front().begin());
                    }
                    Command *command = new Command(replace);
                    command->execute();
                    //exit = 1;
                    break;
                }
                else
                {
                    //cout <<" go in to nothing" <<endl;
                    //if one input is enclose with ()
                    size_t found8 = (input.front()).find(")");
                    if (found8 != string::npos)
                    {
                        while(found8 != string::npos)
                        {
                            input.front().pop_back();
                            paren.pop_back();
                            found8 = (input.front()).find(")");
                        }
                        Command *command = new Command(input.front());
                        determine = command->execute();
                        input.erase(input.begin());
                    }
                    else
                    {
                       // cout << "it goes here" <<endl;
                        Command *command = new Command(input.front());
                        determine = command->execute();
                        input.erase(input.begin());

                    }        
                    // cout << "determine is " << determine << endl;
                    //delete command;
                }
            }
        }
        //continued argument
        else if (connect.front() == "&&")
        {
         //   cout <<"in &&" <<endl;

            if ( rp == true)  //won't execute if previous () is not true
            {
                 //check if it end with )  
                size_t found4 = (input.front()).find(")");
                size_t found5 = (input.front()).find("(");
                //end it )
                if (found4 != string::npos)
                {
                    
                    while(found4 != string::npos)
                    {
                        paren.pop_back(); //remove parenthesis
                        input.front().pop_back();
                        found4 = (input.front()).find(")");
                    }
                    if (skip == true)
                    {
                        //cout << "skip the exec" <<endl;
                        determine = false;
                    }  
                    // remove )in here there is always a space at the end, so pop 

                    Command *command1 = new Command(input.front());
                    Connector *command2 = new And(determine, command1);
                    determine = command2->execute();
                    input.erase(input.begin());
                    connect.erase(connect.begin());
                    rp = determine;
                }
                else if(found5 != string::npos) // start with (
                {
                    while(found5 != string::npos)
                    {
                        paren.push_back(determine); //remove parenthesis
                        input.front().erase(input.front().begin());
                        found5 = (input.front()).find("(");
                    }  

                    Command *command1 = new Command(input.front());
                    Connector *command2 = new And(rp, command1);
                    determine = command2->execute();
                    input.erase(input.begin());
                    connect.erase(connect.begin());
                }
                else //normal
                {
                    connect.erase(connect.begin());
                    if (!connect.empty())
                    {   
                        if((connect.front() == ">") || (connect.front() == "<") || (connect.front() == ">>") || (connect.front() == "|") )
                        {
                            Command *command1 = new Command(input.front());
                            input.erase(input.begin());
                            Command *command2 = new Command(input.front());
                            string filename = input.front();
                            input.erase(input.begin());
                            if (connect.front() == ">") //output_redirect
                            {
                                Connector *oredirect = new OutputRedirect(command1, filename);
                                determine = oredirect->execute();
                                connect.erase(connect.begin());
                            }
                            else if (connect.front() == "<")
                            {
                                Connector *iredirect = new InputRedirect(command1, filename);
                                determine = iredirect->execute();
                                connect.erase(connect.begin());
                            }
                            else if (connect.front() == ">>")
                            {
                                Connector *oredirecta = new OutputRedirectAppend(command1, filename);
                                determine = oredirecta->execute();
                                connect.erase(connect.begin());
                            }
                            else if (connect.front() == "|")
                            {
                                Connector *pipe = new Pipe(command1, command2);
                                determine = pipe->execute();
                                connect.erase(connect.begin());
                            }

                        }
                        else
                        {
                            Command *command1 = new Command(input.front());
                            Connector *command2 = new And(determine, command1);
                            determine = command2->execute();
                            input.erase(input.begin());
                            //connect.erase(connect.begin());

                        }
                        
                    }
                    else
                    {
                        Command *command1 = new Command(input.front());
                        Connector *command2 = new And(determine, command1);
                        determine = command2->execute();
                        input.erase(input.begin());
                        //connect.erase(connect.begin());
                    }
                }
            }
            else
            {
                input.erase(input.begin());
                connect.erase(connect.begin());
                determine = false;
            }
            
        }
        else  if (connect.front() == ";")
        {
            cout << "in ;" <<endl;
            size_t found9 = (input.front()).find(")");
            if (found9 != string::npos)
            {
                while(found9 != string::npos)
                {
                    paren.pop_back(); //remove parenthesis
                    input.front().pop_back();
                    found9 = (input.front()).find(")");
                }
            }
            Command *command1 = new Command(input.front());
            Connector *command2 = new SemiColon(determine, command1);
            determine = command2->execute();
            rp = determine;
            input.erase(input.begin());
            //cout << "determine after ; is " << determine << endl;
            connect.erase(connect.begin());
            
        }
        else if (connect.front() == "||")
        {
            //cout << "in ||" <<endl;
             
            //cout <<"entering ||" << endl;
            if (  rp != true)  //won't execute if previous () is true
            {
                //cout << "in here" <<endl;
                //cout << "determine " << determine <<endl;
                //cout << "rp        " << rp <<endl;
               // cout << "previous deos not works" << endl;
                 //check if it end with )  
                size_t found4 = (input.front()).find(")");
                size_t found5 = (input.front()).find("(");
                //end it )
                if (found4 != string::npos)
                {
                    while(found4 != string::npos)
                    {
                        paren.pop_back(); //remove parenthesis
                        input.front().pop_back();
                        found4 = (input.front()).find(")");
                    }  
                    //remove ), in here there is always a space at the end, so pop twice

                    Command *command1 = new Command(input.front());
                    Connector *command2 = new Or(determine, command1);
                    determine = command2->execute();
                    input.erase(input.begin());
                    connect.erase(connect.begin());
             //       cout << "determin in || is " << determine << endl;
                    rp = determine;
                }
                else if(found5 != string::npos) // start with (
                {
                    //cout <<"before revmoe (" <<endl;
                    while(found5 != string::npos)
                    {
                        paren.push_back(determine); //remove parenthesis
                        input.front().erase(input.front().begin());
                        found5 = (input.front()).find("(");
                    }
                    if (rp == true)
                    {
                        skip = true;
                    }
                    //cout << "erase correctly" << endl;  
                    Command *command1 = new Command(input.front());
                    Connector *command2 = new Or(rp, command1);
                    determine = command2->execute();
                    input.erase(input.begin());
                    connect.erase(connect.begin());
                }
                else //normal
                {
                    connect.erase(connect.begin());
                    if (!connect.empty())
                    {   
                        if((connect.front() == ">") || (connect.front() == "<") || (connect.front() == ">>") || (connect.front() == "|") )
                        {
                            Command *command1 = new Command(input.front());
                            input.erase(input.begin());
                            Command *command2 = new Command(input.front());
                            string filename = input.front();
                            input.erase(input.begin());
                            if (connect.front() == ">") //output_redirect
                            {
                                Connector *oredirect = new OutputRedirect(command1, filename);
                                determine = oredirect->execute();
                                connect.erase(connect.begin());
                            }
                            else if (connect.front() == "<")
                            {
                                Connector *iredirect = new InputRedirect(command1, filename);
                                determine = iredirect->execute();
                                connect.erase(connect.begin());
                            }
                            else if (connect.front() == ">>")
                            {
                                Connector *oredirecta = new OutputRedirectAppend(command1, filename);
                                determine = oredirecta->execute();
                                connect.erase(connect.begin());
                            }
                            else if (connect.front() == "|")
                            {
                                Connector *pipe = new Pipe(command1, command2);
                                determine = pipe->execute();
                                connect.erase(connect.begin());
                            }

                        }
                        else
                        {
                            Command *command1 = new Command(input.front());
                            Connector *command2 = new Or(determine, command1);
                            determine = command2->execute();
                            input.erase(input.begin());

                        }
                    }
                    else
                    {
                        Command *command1 = new Command(input.front());
                        Connector *command2 = new Or(determine, command1);
                        determine = command2->execute();
                        input.erase(input.begin());
                    }
                }
            }
            else
            {

                //cout << "didn't go in " <<endl;
                size_t found4 = (input.front()).find(")");
                size_t found5 = (input.front()).find("(");
                //end it )
                if (found4 != string::npos)
                {
                    while(found4 != string::npos)
                    {
                        paren.pop_back(); //remove parenthesis
                        input.front().pop_back();
                        found4 = (input.front()).find(")");
                    }  
                    //remove ), in here there is always a space at the end, so pop twice

                    Command *command1 = new Command(input.front());
                    Connector *command2 = new Or(determine, command1);
                    determine = command2->execute();
                    input.erase(input.begin());
                    connect.erase(connect.begin());
             //       cout << "determin in || is " << determine << endl;
                    rp = determine;
                }
                else
                {
                    input.erase(input.begin());
                    connect.erase(connect.begin());
                    determine = true;
                }
                

            }
        }

    }

}


bool Action::is_order()
{  
    vector<string> blank = this->token;
    //string blank = input;
    int lp=0;
    int rp=0;
    int total;
    bool fail = true;
    //end it )
    for (int i = 0 ; i < blank.size(); i ++)
    {
        size_t found4 = (blank[i].find(")"));
        size_t found5 = (blank[i].find("("));
        if (found4 != string::npos)
        {
            lp++;
        }
         if (found5 != string::npos)
        {
            rp++;
        }
    } 
    if ( rp > lp)
    {
        fail = false;
        return false;
    }
    if(rp != lp)
    {
        fail = false;   
    }
    return fail;   
    
}

bool Action::is_order(string input)
{  
    string blank = input;
    int lp=0;
    int rp=0;
    int total;
    bool fail = true;
    while(!blank.empty())
    {
        if(blank.front() == '(')
        {
            lp++;
        }
        else if (blank.front() == ')')
        {
            rp++;
        }
        blank.erase(blank.begin());
        if ( rp > lp)
        {
            fail = false;
            return false;
        }
    }
     if(rp != lp)
     {
        // cout <<"rp does not equal to lp" <<endl;
         fail = false;   
     }
    return fail;   
    
}

bool Action::new_connect()
{
    bool determine;
    Command *command1 = new Command(input.front());
    input.erase(input.begin());
    Command *command2 = new Command(input.front());
    string filename = input.front();
    input.erase(input.begin());
    if (connect.front() == ">") //output_redirect
    {
        Connector *oredirect = new OutputRedirect(command1, filename);
        determine = oredirect->execute();
        connect.erase(connect.begin());
    }
    else if (connect.front() == "<")
    {
        Connector *iredirect = new InputRedirect(command1, filename);
        determine = iredirect->execute();
        connect.erase(connect.begin());
    }
    else if (connect.front() == ">>")
    {
        Connector *oredirecta = new OutputRedirectAppend(command1, filename);
        determine = oredirecta->execute();
        connect.erase(connect.begin());
    }
    else if (connect.front() == "|")
    {
        Connector *pipe = new Pipe(command1, command2);
        determine = pipe->execute();
        connect.erase(connect.begin());
        
    }
    return determine;
}
/////////////////////////testing code///////////////////////////////////

        /* 
        cout << "connector is here"<<endl;
        for (int i = 0 ; i < connect.size(); i++)
        {
            cout << connect[i] <<endl;
        }
        cout << "size of connector is" <<endl;
        cout << connect.size() <<endl;
        cout << "input is here"<<endl;
        for (int i = 0 ; i < input.size(); i++)
        {
            cout << input[i] <<endl;
        }
        cout << "size of input is" <<endl;
        cout << input.size()<<endl;
        */
