#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "interface.h"
#include "command.h"

using namespace std;

class Connector: public Interface {
   public:
      Connector() {};
      Connector(Interface* left, Interface* right) {
         this->left = left;
         this->right = right;
      }
      Connector(bool left_work, Interface* right)
      {
         this->left_work = left_work;
         this->right = right;
      }
      Connector(Interface* left, string filename)
      {
         this->left = left;
         this->filename = filename;
      }
      virtual bool execute() = 0;
      virtual string getCommand() = 0;
   protected:
      Interface* left;
      Interface* right;
      string filename;
      bool left_work;
};

#endif
