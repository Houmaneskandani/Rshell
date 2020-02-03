#include "../header/command.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

class Command;
class Connector;
class Interface;

bool Command::execute() {
   //int pipefd[2];
   int status;
   if (command == "exit") {
      exit(2);
      return false;
   }

   vector<char*> wordVector;
   char* token = strtok((char*)this->command.c_str(), " ");
   while (token != NULL) {
      wordVector.push_back(token);
      token = strtok(NULL, " ");
   }

   char** args = new char* [wordVector.size() + 1];
   for (int i = 0; i < wordVector.size(); i++) {
      args[i] = wordVector[i];
   }
   
   args[wordVector.size()] = NULL;
   pid_t pid = fork();
   if(pid == 0) {
       // close(pipefd[0]); //close read end
      if(execvp(args[0], args) == -1) {
         perror("exec");
         exit(EXIT_FAILURE);
        
      }
   } else if (pid >0) {
      waitpid(-1, &status,0);
      int exit_status = WEXITSTATUS(status);
      //   cout << exit_status<<endl;
      // exit_status = 1 if child process fail
      // = 0 if sucess
      if (exit_status == 1)
      {    
         return false;
      }
      else
      { 
         return true;
      }
   }
}

string Command::getCommand() {
   return command;
}
