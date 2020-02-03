#include "../header/testcommand.h"

#include <iostream>
#include <sstream>
#include <sys/stat.h>

using namespace std;

bool TestCommand::execute() {
   string input, tempString;
   size_t testIndex = command.find("test");
   size_t eIndex = command.find("-e");
   size_t fIndex = command.find("-f");
   size_t dIndex = command.find("-d");
   size_t dashIndex = command.find("-");

   struct stat comparator;

   if (dashIndex != -1) {
      if (eIndex == -1 && fIndex == -1 && dIndex == -1) {
         cout << "(False)" << endl;
         return false;
      }
   }

   if (eIndex == -1 && fIndex == -1 && dIndex == -1) {
      //Take in account for whether or not user enters something in [ ]
      if (command.at(0) == '[' && command.at(command.size() - 1 == ']')) {
         input = command.substr(dIndex + 3, command.size() - 2);
         stringstream ss(input);
         ss >> tempString;
         input = tempString;
      } else {
         input = command.substr(5);
         cout << input << endl;
      }

      if (stat(input.c_str(), &comparator) == 0) {
         cout << "(True)" << endl;
         return true;
      } else {
         cout << "(False)" << endl;
         return false;
      }
   }

   if (eIndex != -1) {
      if (command.at(0) == '[' && command.at(command.size() - 1 == ']')) {
         input = command.substr(eIndex + 3, command.size() - 2);
         stringstream ss(input);
         ss >> tempString;
         input = tempString;
      } else {
         input = command.substr(eIndex + 3);
      }

      if (stat(input.c_str(), &comparator) == 0) {
         cout << "(True)" << endl;
         return true;
      } else {
         cout << "(False)" << endl;
         return false;
      }
   }

   if (fIndex != -1) {
      if (command.at(0) == '[' && command.at(command.size() - 1== ']')) {
         input = command.substr(fIndex + 3, command.size() - 2);
         stringstream ss(input);
         ss >> tempString;
         input = tempString;
      } else {
         input = command.substr(fIndex + 3);
      }

      if (stat(input.c_str(), &comparator) == 0) {
         if (S_ISREG(comparator.st_mode)) {
            cout << "(True)" << endl;
            return true;
         } else {
            cout << "(False)" << endl;
            return false;
         }
      } else {
         cout << "(False)" << endl;
         return false;
      }
   }

   if (dIndex != -1) {
      if (command.at(0) == '[' && command.at(command.size() - 1 == ']')) {
         input = command.substr(dIndex + 3, command.size() - 2);
         stringstream ss(input);
         ss >> tempString;
         input = tempString;
      } else {
         input = command.substr(dIndex + 3);
      }

      if (stat(input.c_str(), &comparator) == 0) {
         if (S_ISDIR(comparator.st_mode)) {
            cout << "(True)" << endl;
            return true;
         } else {
            cout << "(False)" << endl;
            return false;
         }
      } else {
         cout << "(False)" << endl;
         return false;
      }
   }

   return false;

}

string TestCommand::getCommand() {
   return command;
}

