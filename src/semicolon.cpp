#include "../header/semicolon.h"
#include "../header/interface.h"
#include "../header/connector.h"

using namespace std;

bool SemiColon::execute() {
   if (left_work == true || left_work == false)
   {
      return right->execute();
   }
   else
   {
      left->execute();
      return right->execute();
   }

}

string SemiColon::getCommand() {
   return left->getCommand() + " ; " + right->getCommand();
}
