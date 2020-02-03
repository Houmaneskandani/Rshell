# CS100 RShell

Summer 2019
* Clifford Wen Loong Ng, 862154819
* Kai Wen Tsai, 861261944
* Houman Eskandani, 862092169

# Introduction

We predict that our program will be able to accomplish simple tasks that is echo, ls, cd, and mkdir. We plan to design our program using composite pattern. The echo
command will output any string of text back on the screen. The ls command will ls any files in the current directory that the user is in. The cd command will change
the current directory of user's location to the one that the user typed as the argument. The mkdir command will be able to make a new directory in the current
directory that the user is currently in. These four commands will inherit from a command class. We also have Connector classes which determine if the connected 
command argument should execute or not.  

# Diagram

![Image of OMT Diagram](https://github.com/cs100/assignment-team/blob/master/images/OMT%20Diagram.png?raw=true)

# Classes

#### Interface
The interface class will be the base of all our other classes. Every other class will inherit from this class which contains only one pure virtual execute function.

#### Command
The command class will be a leaf in our pattern. It will inherit the function(s) from the parent class, which is the interface. After execution, it will get the user's input and execute the correct command.

#### Connectors
The Connectors class will be a composite in our pattern. it will inherit the function(s) from the parent class. After execution it call the boolean function for the specific child class. 

* Connector Class
  * `;`
    - ; mark the ends the statement. 
  * `&&`
    - the command argument executes only if the previous command argument executes successfully.
    - command argument after `&&` executes only if command argument before `&&` works
  * `||`
    - the command argument executes only if the previous command argument not executes successfully.
    - command argument after `||` executes only if command argument before `||` works
  * `#`
    - ignore any text after `#`.
     

# Prototypes/Research
We will use fork(), execvp, waitpid() to do parsing in our assignment. For parsing from user input with connector && and ||, we will implement fork() and waitpid() to create similar situation with connectors. We will put treat each argument as different process (forking). Process only will execute if previous process(argument) work correctly. In each process, we will use execvp() to execute the argument.

# Development Issues and Testing Roadmap

### Assignment 1
1. Check if parsing from user is working properly
[#1](../../issues/1)

* execvp()

2. Determine what is command and what is argument based on user input
[#2](../../issues/2)

* `echo`
* `cd`
* `mkdir`
* `ls`

3. Create connectors
[#3](../../issues/3)

* `exit`
  * exit program
* `;`
  * end of statement
* `#`
  * ignore preceding texts

4. Ensure program is able to read and execute command
[#4](../../issues/4)

 * execute fork(), execvp(), waitpid(), and pipe() correctly.

### Assignment 2
1. Created a command class and connector class along with its subclasses for connector

2. We created a main.cpp file with parsing code

3. We started on creating unit test and integration test for our commands and connector
* The quatation for argument  has some issue that it can't combine argument properly as expected

### Assignment 3
1. The quatation problem for argument has been modified and fixed.

2. Started by adding test command  and it's symbolic equivalent [ ] to our rshell.  
[NOTE] Assuming there is a space between symbolic equivalent [ ] and no space for parentheses ().
* `test -e test/file/path` checks if the file directory exist and then it'll print (True) or (False).
* `test -f test/file/path` checks if the file directory exist and is a regular file, then it'll print (True) or (False). 
* `test -d test/file/path` checks if the file directory exist and is a directory, then it'll print (True) or (False). 

* `[ -e test/file/path ]` checks if the file directory exist and then it'll print (True) or (False).
* `[ -f test/file/path ]` checks if the file directory exist and is a regular file, then it'll print (True) or (False).
* `[ -d test/file/path ]` checks if the file directory exist and is a directory, then it'll print (True) or (False).

* `test -e main.cpp || echo hello`             combined test_comand with connectors.

* `(echo a && echo b) || (echo c && echo d)`   decides execution priority by parenthesis.
* `((echo a && echo b) || echo c)`             decides execution priority by nested parenthesis.


3. Created sufficient unit tests and integration tests for our new commands. 

### Assignment 4
1. We extend our rshell program by implementing input redirection <, output redirection >, >>, and piping |.
* `<` - will redirects the stdin to the existing file. 
* `>` - will redirects stdout to create a file or overwrite the file. 
* `>>`- will redirects stdout to append to a file.
* `|` - will take stdout of any command and redirects as stdin for other command.

Example:
* `cat < file_1 | tr A-Z a-z | tee outputfile_1 | tr a-z A-Z > outputfile_2` 

2. Created sufficient unit tests and integration tests for our new commands. 










