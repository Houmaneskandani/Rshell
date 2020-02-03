#ifndef AND_H
#define AND_H

#include "interface.h"
#include "connector.h"

using namespace std;


class And: public Connector {
   public:
      And() {}
      And(Interface* left, Interface* right): Connector(left, right) {};
      //And(Interface* left, Interface* right);
      And(bool left_work, Interface* right): Connector(left_work, right) {};
      
        
      bool execute();
      string getCommand();
 
};

#endif
