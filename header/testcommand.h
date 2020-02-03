#ifndef TESTCOMMAND_H
#define TESTCOMMAND_H

#include "command.h"

#include <string>

using namespace std;

class TestCommand: public Command {
   public:
      TestCommand() {}
      TestCommand(string command) {
         this->command = command;
      }
      virtual bool execute();
      string getCommand();

   protected:
      string command;
};

#endif
