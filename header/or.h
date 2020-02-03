#ifndef OR_H
#define OR_H

#include "connector.h"

class Or: public Connector {
   public:
      Or() {};
      //Or(Connector* left, Connector* right): Connector(left, right) {};
      //Or(Interface* left, Interface* right);
      Or(Interface* left, Interface* right): Connector(left, right) {};
      Or(bool left_work, Interface* right) : Connector(left_work, right) {};

      bool execute();
      string getCommand();
 
};

#endif
