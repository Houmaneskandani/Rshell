#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>

using namespace std;

class Interface {
   public:
      Interface() {};
            
      //Pure Virtual Functions
      virtual bool execute() = 0;
      virtual string getCommand() = 0;
};

#endif
