#include "../header/and.h"
#include "../header/interface.h"
#include "../header/connector.h"

using namespace std;

class Interface;
class Connector;

bool And::execute() {
    //if the left argument works, the run the right one
    //int working;
    //working = left->execute();
   if (left_work == true || left_work == false)
   {
      if (left_work == true)
      {
         if(right->execute())
         {
            return true;
         }
      }
      return false;
      
   }
   else
   {
      if (left->execute()) {
            right->execute();
            return true;
         }

      return false;
   }
   

   // return (left->execute() && right->execute());
}

string And::getCommand() {
   return left->getCommand() + " && " + right->getCommand();
}


//And::And(Interface* left, Interface* right) : Connector(left, right) {} 
/*
And::And(Interface* left, Interface* right) {
   this->left = left;
   this->right = right;
} 

//If LHS execute, return rhs flag. If LHS doesn't return true, return false
bool And::execute() {
   this->setIsExecuted(false);
   
   if(this->left->execute()) {
       if(this->right->execute()) {
          this->setisExecuted(true);
          return true;
       }
   }
   return false;
}
*/
