#include "../header/pipe.h"
#include "../header/interface.h"
#include "../header/connector.h"

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>

using namespace std;

bool Pipe::execute() {
    
     // Initialize some variable
     // - we need a pipe fds https://www.geeksforgeeks.org/pipe-system-call/
     // - we will need a pid using pid_t or int?

     // - if pipe = -1 the pipe fails.
     // - Do error checking
     // - do the same for left and right
     // - use dup2 instead of dup
     
   int fds[2];
   pid_t pid;

   //Error check to see if pipe fails first
   if (pipe(fds) == -1) {
      perror("The pipe has failed, call a plumber");
      exit(1);
      return false;
   }

   pid = fork();

   //Error check for fork
   if (pid == -1) {
      perror("The fork has failed, it turned into a spoon");
      exit(1);
      return false;
   }

   if (pid == 0) {
      //Use dup2 https://www.geeksforgeeks.org/dup-dup2-linux-system-call/     
      //dup2 MUST happen before close or else it won't work
      if (dup2(fds[1], 1) == -1) {
         perror("Dup has failed");
         exit(1);
         return false;
      }

      //This is necessary for it to work, also fixed infinite loop problem
      //https://stackoverflow.com/questions/1720535/practical-examples-use-dup-or-dup2      
      int copy_desc1 = dup(1); 
      close(fds[0]);

      if (left->execute() != true) {
         exit(1);
         return false;
      }

      dup2(copy_desc1, 0);
      close(fds[1]);
      exit(0);
   } else {
      //Wait for your mama, child
      pid_t p;
      int status;

      p = waitpid(pid, &status, 0);
       
      if (p == pid) {
         if (WEXITSTATUS(status) == 1) {
            perror("Child didn't wait for it's mom");
            exit(1);
         } else {
            //Child waited for it's mom!
            //Now do the same thing, but do it to the right side
            int copy_desc0 = dup(0);

            //dup2 MUST happen before close or else it won't work
            if (dup2(fds[0], 0) == -1) {
               perror("Dup has failed");
               exit(1);
               return false;
            }
            
            close(fds[1]);

            if (right->execute() != true) {
               exit(1);
               return false;
            }

            dup2(copy_desc0, 0);
            close(fds[0]);
            return true;
         }
      }
  } 

   return false;
}

//bool Pipe::execute() {
   /*
      Initialize some variable
      - we need a pipe fds https://www.geeksforgeeks.org/pipe-system-call/
      - we will need a pid using pid_t or int?

      - if pipe = -1 the pipe fails.
      - Do error checking
      - do the same for left and right
      - use dup2 instead of dup
   */
/*
   int fds[2];
   pid_t pid;

   //Error check to see if pipe fails first
   if (pipe(fds) == -1) {
      perror("The pipe has failed, call a plumber");
      exit(1);
      return false;
   }

   pid = fork();

   cout << pid << endl;
   if (pid == -1) {
      perror("The fork has failed, it turned into a spoon");
      exit(1);
      return false;
   } else {
      if (pid == 0) {
         close(fds[0]);
         dup2(fds[1], 1);
         cout << "TOUCHED" << endl;
         return true;
      }
   }
}

   switch(pid) {
      case -1:
         //Do error checking for fork
         perror("The fork has failed, it turned into a spoon");
         exit(1);
         return false;
      case 0:
         cout << "INSIDE: " << pid << endl;
         if (pid == 0) {
            //Close up the child process first           
            close(fds[0]);
            cout << "TESTING: " << pid << endl;
            //Use dup2 https://www.geeksforgeeks.org/dup-dup2-linux-system-call/
            //int file_desc = dup2(fds[1], 1);
            //Error checking first
                 
            if (left->execute() != true) {
               //Left execution failed
               exit(1);
               return false;
            }
            close(fds[1]); //close the output pipe
            exit(0);
         } else {
            //Wait for your mama, child
            pid_t p;
            int status;

            p = waitpid(pid, &status, 0);
            cout << p  << " and " << pid << endl;
            if (p == pid) {
               if (WEXITSTATUS(status) == 1) {
                  perror("Child didn't wait for it's mom");
                  exit(1);
               }
            } else {
               //Child waited for it's mom!
               //Now do the same thing, but do it to the right side
               close(fds[1]);
               int file_desc = dup2(fds[0], 0);

               if (file_desc == -1) {
                  perror("Dup has failed");
                  exit(1);
                  return false;
               }

               if (right->execute() != true) {
                  exit(1);
                  return false;
               }
               exit(0);
               close(fds[0]); //Also, close the input pipe
            }
         }
         return true;
      //default:
        // cout << pid << endl;
         //cout << "NO I'm not done." << endl;
        // return false;
   }
}
*/

string Pipe::getCommand() {
   return left->getCommand() + " | " + right->getCommand();
}
