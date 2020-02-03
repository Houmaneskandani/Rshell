#include <unistd.h>
//Prototype example for parsing from user input using connector

//use argv to read each argument or command
main(argc, char* argv[])
{
    //take example of  user input: ls -a || echo "hello" 
    //we first create process using fork based on the process
    //we will execute  echo "hello" in parent process, ls in child process
    //if parent received fail signal(-1) from child then will execute the command
    //
    char * child = {argv[2],0}; // -a
    char * parent = {argv[5], 0}; //"hello"
    int error; //check if child process fail or not 
    int fd[2]; //use pipe to send messae from child to parent, fd[1] is read, fd[2] is write
    pid_t child_pid = fork();
    if (child_pid < 0):
    {
        perror("fork error");
        exit(-1);
    }
    if (child_pid >0): //in parent process
    {
        close(fd[1]); //turn off write end
        waitpid(child_pid); //wait until child process finish
        read(fd[0], error); //read signal from child
        close(fd[0]);
        
        if (error == -1): //execute if first command fail
        {
            execvp("echo", parent);
        }
    }
    if (child_pid = 0): //in child process 
    {
        error = execvp("ls", child); //error  = -1 if fail
        write(fd[1], error); //send signal to parent
        close(fd[1]);
           
    }
          

    return 0;
}
