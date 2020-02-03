#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>
#include "interface.h"

using namespace std;

class Command: public Interface {
   public:
      Command() {};
      Command(string command) {
         this->command = command;
      }

      virtual bool execute();
      string getCommand();
   protected:
      //For Testing
      bool getIsExecute();
      string command;
};


#endif
