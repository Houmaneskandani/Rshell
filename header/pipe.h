#ifndef PIPE_H
#define PIPE_H

#include "interface.h"
#include "connector.h"
#include <string>

using namespace std;

class Pipe : public Connector {
   public:
      Pipe() {}
      Pipe(Interface* left, Interface* right): Connector(left, right) {};

      bool execute();
      string getCommand();
};

#endif
