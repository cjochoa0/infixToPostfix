// University of Arkansas at Little Rock
// Department of Computer Science
// CPSC 2380: Data Structures and Algorithms
// Fall 2018
// Project 2: infix to Postfix conversion
// Due Date: October 4, 2018
// Name: Carlos Just Ochoa
// T-number (Last 4 Digits): 9463
// Description of the Program (2-3 sentences): Using stacks to contain the infix, operator, and postfix expression
// then using them in a funtion to return a string of postfix.
// Date Written: 11 / 5 / 18
// Date Revised: 11 / 26 / 18
#pragma warning (disable : 4996)
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool checkOperand(string sta);
bool checkOperPrec(string tok, string sta);
string InfixToPostfix(char* str);

int main()
{
	char *str = new char[100]; //infix string
	char *newStr = new char[300];// postifx sting

	while (1) {
		cout << "Enter an infix arithmetic expression: " << endl;
		cin.getline(str, 80);

		int j = 0;
		for (int i = 0; i < 100; i++)
		{
			if (str[i] == '(' || str[i] == ')' || str[i] == '+' ||
				str[i] == '-' || str[i] == '*' || str[i] == '/')
			{
				newStr[j] = ' ';
				j = j + 1;
				newStr[j] = str[i];
				j = j + 1;
				newStr[j] = ' ';
				j = j + 1;
			}
			else
			{
				newStr[j] = str[i];
				j = j + 1;
			}
		}

		cout << "Infix string with spaces: " << newStr << endl;

		cout << "Postfix string: " << InfixToPostfix(newStr) << endl;
	}
	system("PAUSE");
	return 0;
}

//returning a letter or digit thats not a operator or ( )
bool checkOperand(string sta)
{
	if (!sta.compare("(") || !sta.compare(")") 
		|| !sta.compare("+") || !sta.compare("-")
		|| !sta.compare("/") || !sta.compare("*"))
		return false;

	return true;
}

//Function to return precedence of operators 
bool checkOperPrec(string tok, string sta)
{
	if (tok == "*" || tok == "/")
		if (sta == "+" || sta == "-")
			return true;
	   return false;
}

//function to convert infix to postfix
string InfixToPostfix(char *str) {
	char *token = strtok(str," "); 
	string element_c = ""; //string that holds current token
	string postfixExpression = ""; //string holds postfix expression
	stack<string> infix_stack; //stack holds infix expression
	stack<string> postfix_stack; //stack holds postfix expression
	stack<string> stack_expression; //stack holds the reverse expressions
	stack<string> op_stack; //stack holds the operators

	//Putting the tokens into a stack
	while (token != NULL) {
		stack_expression.push(token);
		token = strtok(NULL, " ");
	}
	
	//flipping the stack by putting into another
	while (!stack_expression.empty()) {
		infix_stack.push(stack_expression.top());
		stack_expression.pop();
	}
	
	//Psuedocode algorithm
	while (!infix_stack.empty()) {
		element_c = infix_stack.top();
		infix_stack.pop();
		// checks if token is equaivalent to (
		if (!element_c.compare("(")) { 
			op_stack.push(element_c); // puts the ( into the op stack
		}
		//checks if its a letter or digit
		else if (checkOperand(element_c)) {
			postfix_stack.push(element_c); //the operand token is pushed in the stack
		}
		//checks if token is equaivalent to )
		else if (!element_c.compare(")")) { 
			//temporay token made to get the top
			//of the opeartor stack
			string t_token = op_stack.top();
			op_stack.pop();
			//goes thru the stack until its
			//equivalent to (
			while (t_token.compare("(")) {
				postfix_stack.push(t_token);
				t_token = op_stack.top();
				op_stack.pop();
			} //end while
		}
		else { //the token must be an operator
			if (op_stack.empty() || op_stack.top() == "("){
				op_stack.push(element_c);
			}
			else {
				while (!op_stack.empty() && checkOperPrec(op_stack.top(), element_c)) {
					string t_token;
					t_token = op_stack.top();
					op_stack.pop();
					postfix_stack.push(t_token);
				}
				op_stack.push(element_c);
			}
		}
	}

	//emptying the operator stack 
	//while putting the remaining operators into the postfix stack
	while (!op_stack.empty()) {
		postfix_stack.push(op_stack.top());
		op_stack.pop();
	}
	
	//reversing the postfix stack
	//while emptying the stack
	while (!postfix_stack.empty()) {
		stack_expression.push(postfix_stack.top());
		postfix_stack.pop();
	}

	//putting the stack into a postfix string 
	//while emptying the stack
	while (!stack_expression.empty()) {
		postfix_stack.push(stack_expression.top());
		postfixExpression += stack_expression.top() + " ";
		stack_expression.pop();
	}
	return postfixExpression;
}