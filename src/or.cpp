#include "../header/or.h"
#include "../header/interface.h"
#include "../header/connector.h"
#include <iostream>
using namespace std;
//Or::Or(Interface* left, Interface* right) : Connector(left, right) {};

bool Or::execute() {
    //If left works, return true. Otherwise continue to check if right works, return true.
    //If both doesn't work return false.

    if (left_work == true || left_work == false) {
       //cout << "comes here" <<endl;
      if (left_work == true)
      {
         //cout << "|| not here" <<endl;
         return true;
      }
      else
      {
          if(right->execute())
          {
              return true;
          }
          if(left->execute()) {
              return true;
          }
          return false;
      }

      /*
      if(left->execute()) {
         return true;
      }
      if(right->execute()) {
         return true;
      }
      return false;
      */
   }
   /*
   else {
        if(left->execute()) {
             return true;
        }
        if(right->execute()) {
            return true;
        }

        return false;
   }
   */
   
  
//   return (left->execute() || right->execute());
}

string Or::getCommand() {
   return left->getCommand() + " || " + right->getCommand();
}
