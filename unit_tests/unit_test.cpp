#include <iostream>
#include <string>
#include "../header/interface.h"
#include "../header/command.h"
#include "../header/connector.h"
#include "../header/and.h"
#include "../header/or.h"
#include "../header/semicolon.h"
#include "../header/parse.h"
#include "gtest/gtest.h"
#include "../header/testcommand.h"


#include "../header/output_redirect_append.h" 
#include "../header/output_redirect.h"
#include "../header/pipe.h"
#include "../header/input_redirect.h"
using namespace std;


//==========================CommandTestSet==================================

TEST(CommandTestSet, Echo) {
   string command = "echo";
   Command *ls = new Command(command);
   bool test = ls->execute();
   EXPECT_EQ(test, true);  
}

TEST(CommandTestSet, cd) {
   string command = "cd";
   Command *ls = new Command(command);
   bool test = ls->execute();
   EXPECT_EQ(test, true);
}

TEST(CommandTestSet, ls) {
   string command = "ls";
   Command *ls = new Command(command);
   bool test = ls->execute();
   EXPECT_EQ(test, true);
}

TEST(CommandTestSet, quotation) {
   string command = "echo \"What am I doing here\"";
   Command *quote = new Command(command);
   bool test = quote->execute();
   EXPECT_EQ(test, true);
}


//==========================ConnectorTestSet==================================
TEST(ConnectorTestSet, And_test) {
   string command1 = "ls";
   string command2 = "ly";

   Interface* left = new Command(command1);
   Interface* right = new Command(command2);
   Interface* test = new And(left, right);
   EXPECT_EQ(test->execute(), false);
}


TEST(ConnectorTestSet, or_test) {
   string command1 = "ls";
   string command2 = "ly";

   Interface* left = new Command(command1);
   Interface* right = new Command(command2);
   Interface* test = new Or(left, right);
   EXPECT_EQ(test->execute(), true);
}



//==========================================TestCommandTest==================================

TEST(TestCommandTest, test_command_test_0) {
   
   string command1 = "test -e names.txt";
   Command *data = new TestCommand(command1);
   bool test = data->execute();
   EXPECT_EQ(test, true);
}

TEST(TestCommandTest, test_command_test_1) {
   string command1 = "test -f names.txt";
   Command *data  = new TestCommand(command1);
   bool test = data->execute();
   EXPECT_EQ(test, true);
}


TEST(TestCommandTest, test_command_test_2) {
   string command1 = "test -d names.txt";
   Command *data  = new Command(command1);
   bool test = data->execute();
   EXPECT_EQ(test, false);
}


TEST(TestCommandTest, test_command_test_3) {
   string command1 = "[ -e names.txt ]";
   Command *data  = new Command(command1);
   bool test = data->execute();
   EXPECT_EQ(test, true);
}

TEST(TestCommandTest, test_command_test_4) {
   string command1 = "[ -e src/main.cpp ]";
   Command *data  = new Command(command1);
   bool test = data->execute();
   EXPECT_EQ(test, true);
}


//===========================================================================


TEST(parenthesisConnectorTest, UnevenParenthesis_test) {
   string command1 = "(((echo A && echo B)";
   string command2 = "((echo B && echo A) || echo c)";

   bool even, even2;
   Action job;
   even = job.is_order(command1); 
   even2 = job.is_order(command2);
   EXPECT_EQ(even, false); 
   EXPECT_EQ(even2, true);
}


TEST(parenthesisConnectorTest, UnevenParenthesis_test2) {
   string command1 = "(((echo A && echo B))))";
   string command2 = "((echo B && echo A)) || echo c))))";

   bool even, even2;
   Action job;
   even = job.is_order(command1); 
   even2 = job.is_order(command2);
   EXPECT_EQ(even, false); 
   EXPECT_EQ(even2, false);
}

//============================pipe_test=============================================

TEST(Pipe_tests, Pipe_1_Test) {
   string command1 = "ls";
   string command2 = "more";

   Command *left = new Command(command1);
   Command *right = new Command(command2);
   Connector *test = new Pipe(left, right);

   EXPECT_EQ(test->execute(), true);
}

TEST(Pipe_tests, Pipe_2_Test) {
   string command1 = "ls";
   string command2 = "head -3";

   Command *left = new Command(command1);
   Command *right = new Command(command2);
   Connector *test = new Pipe(left, right);

   EXPECT_EQ(test->execute(), true);
}

TEST(Pipe_tests, Pipe_3_Test) {
   string command1 = "ps aux";
   string command2 = "wc -l";

   Command *left = new Command(command1);
   Command *right = new Command(command2);
   Connector *test = new Pipe(left, right);

   EXPECT_EQ(test->execute(), true);
}





//============================redirection_tests======================================


TEST(redirection_tests, InputRedirection_Test) {
   string command1 = "cat";
   string command2 = "test.txt";   
   Command *cat = new Command(command1);
   Connector *iredirect = new InputRedirect(cat, command2);
   
   EXPECT_EQ(iredirect->execute(), true);

}



TEST(redirection_tests, OutputRedirection_Test) {
   string command1 = "ls";
   string command2 = "test.txt";


   Command *cat = new Command(command1);
   Connector *iredirect = new OutputRedirect(cat, command2);

   EXPECT_EQ(iredirect->execute(), true);

}


TEST(redirection_tests, OutputRedirect_Append_Test) {
   string command1 = "echo hello";
   string command2 = "test.txt";


   Command *cat = new Command(command1);
   Connector *iredirect = new OutputRedirectAppend(cat, command2);

   EXPECT_EQ(iredirect->execute(), true);

}









int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
