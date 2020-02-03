#ifndef SEMICOLON_H
#define SEMICOLON_H

#include "interface.h"
#include "connector.h"

using namespace std;

class SemiColon: public Connector {
   public:
      SemiColon() {};
      SemiColon(Interface* left, Interface* right) : Connector(left, right) { };
      SemiColon(bool left_work, Interface* right) : Connector(left_work, right){};

      bool execute();
      string getCommand();

};

#endif
