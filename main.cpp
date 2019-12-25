//author Ronaldo Seranllari
//Programming Foundation 2 
//This homework includes 5 files. 2 files for expression class, 2 for token, and the main program
//The Token class, tokenizes an expression string
//The Expression class, takes a string and that parenthesizes, postfixes, prefixes, and evaluates 
//The main program gets user input, for expression, and pics from the menu 

#include <iostream>
#include <vector>
#include "Expression.h"
#include "Token.h"
#include <stack>
using namespace std; 


//I handled error checking using recursion. 
//This function takes as argument a string passed by reference
//And checks if it valid or not
void errorCheckExpress (string & seqExpress) {
	//Checks if the expression starts with ; 
	int size = seqExpress.size(); 
	int openBracket = 0, closeBracket = 0; 
	
	while ((seqExpress[openBracket] != '(') && (openBracket < size)) {
		openBracket++; 
	}
	
	while ((seqExpress[closeBracket] != ')') && (closeBracket < size)) {
		closeBracket++; 
	}
	
	if ((closeBracket < openBracket) || ((openBracket < size) && (closeBracket == size))){
		cout << "The expression is invalid. Please insert another one: " <<endl;  
				cout << "Bracket problem" <<endl;
				getline(cin, seqExpress); 
				errorCheckExpress(seqExpress); 
		
	}
		
		
		
	if ((seqExpress[0] == ';') || (seqExpress[0] == '/') || (seqExpress[0] == '*') || (seqExpress[0] == '+')) {
		cout << "The expression is invalid. Please insert another one: " <<endl; 
		cout << "The expression cannot start with a operand" <<endl; 
		getline(cin, seqExpress); 
		errorCheckExpress(seqExpress);
	}
	
	int i = 0; 
	while (i < seqExpress.size()) {
		
	//checks if after an integer or identifier there is an operand that follows. 
	//if it isnt followed by an operand than it is invalid
		if (isalpha(seqExpress[i]) || isdigit(seqExpress[i])) {
			int j = 0;
			j = i + 1; 
			if ((seqExpress[j] != '+') && (seqExpress[j] != '-') && (seqExpress[j] != '*') && (seqExpress[j] != '/') && (seqExpress[j] != ';') 
				&& !(isalpha(seqExpress[j])) && !(isdigit(seqExpress[j])) && (seqExpress[j] != ')' ) && (seqExpress[j] != '(' ) && (seqExpress[j] != '=' )) {
				cout << "The expression is invalid. Please insert another one: " <<endl;  
				cout << "The integer or identifier needs to be followed by an operand, or ;" <<endl;
				getline(cin, seqExpress); 
				errorCheckExpress(seqExpress); 
			}
		}
	//checks to see if there isnt double operands following each other, 
	//after each operand there should be either an integer or an identifier 
		if ((seqExpress[i] == '+') || (seqExpress[i] == '-') || (seqExpress[i] == '*') || (seqExpress[i] == '/') || (seqExpress[i] == '=')) {
			int j = 0;
			j = i +1; 
			if ( !(isdigit(seqExpress[j])) && !(isalpha(seqExpress[j])) && (seqExpress[j] != '(')) {
				cout << "The expression is invalid. Please insert another one: " <<endl;  
				cout <<"Cannot have a double operand" <<endl;
				getline(cin, seqExpress); 
				errorCheckExpress(seqExpress);
			}
		}
		
	// checks to see after the bracket there isnt any double bracket or ;, 
	//after the bracket there should only be an integer or identifier. 
		if ((seqExpress[i] == ')') ||(seqExpress[i] == '(')) {
			int j = 0;
			j = i +1; 
			if ( !(isdigit(seqExpress[j])) && !(isalpha(seqExpress[j])) && !(seqExpress[j] == ';') && !( seqExpress[j] == '(') && !( seqExpress[j] == ')')) {
				cout << "The expression is invalid. Please insert another one: " <<endl;  
				cout << "Invalid use of bracket" <<endl; 
				getline(cin, seqExpress); 
				errorCheckExpress(seqExpress);
			}
		}
	//checks to see if there isnt a double ;. 
	//checks to see if the expression starts with a number or identifier. 
		if ((seqExpress[i] == ';') && (i < size - 1)) {
			int j = 0;
			j = i + 1;
			if ( !(isdigit(seqExpress[j])) && !(isalpha(seqExpress[j])) && (seqExpress[j] != '(') || (seqExpress[j] == ';') ) {
				cout << "The expression is invalid. Please insert another one: " <<endl;  
				cout << "It cannot have a double ;" <<endl; 
				getline(cin, seqExpress); 
				errorCheckExpress(seqExpress);
			}
		}
		i++; 
	}
	
}


//the functions checks to see if the user doesnt input a char from the list. 
void checkMenu(string & menu) {
	
	if ((menu != "=") && (menu != ">") && (menu != "<") && (menu != "f") && (menu != "F") && (menu != "q") && (menu != "Q") 
	&& (menu != "c") && (menu != "C") && (menu != "s") && (menu != "S")) {
		cout << "Please, select again from the following options: " <<endl; 
		cout << "Press '=' to evaluate" <<endl; 
		cout << "Press '>' to convert each expression in the sequence of expressions to the equivalent prefix expression" <<endl;
		cout << "Press '<' to convert each expression in the sequence of expressions to the equivalent postfix expression" <<endl;
		cout << "Press 'f' to convert each expression in the sequence of expressions to the equivalent fully parenthesized expression" <<endl;
		cout << "Press 'q' to quit the program" <<endl;
		cout << "Press 'c' to continue inputting a sequence of expressions" <<endl;
		cout << "Press 's' to start over for a new sequence" <<endl;
		getline (cin, menu); 
		checkMenu(menu); 
	}
}
int main () {
	string seqExpress, menu; //get the sequence of expression, get input for the menu
	cout <<"Please, enter the sequence of expressions (DO NOT INCLUDE SPACES): " <<endl; 
	vector <Expression> sequences; 
	getline(cin, seqExpress); 
	string subSeq; 
 	errorCheckExpress(seqExpress); 
 	
	for (int i = 0; i < seqExpress.size(); i++) {
		if (seqExpress[i] != ';') {
			subSeq.push_back(seqExpress[i]); 
		}
		else {
			Expression temp; 
			temp.set(subSeq); 
			sequences.push_back(temp);  
			subSeq.clear(); 
		}
	}
	
	cout << "Please, select one of the following options: " <<endl; 
	cout << "Press '=' to evaluate" <<endl; 
	cout << "Press '>' to convert each expression in the sequence of expressions to the equivalent prefix expression" <<endl;
	cout << "Press '<' to convert each expression in the sequence of expressions to the equivalent postfix expression" <<endl;
	cout << "Press 'f' to convert each expression in the sequence of expressions to the equivalent fully parenthesized expression" <<endl;
	cout << "Press 'q' to quit the program" <<endl;
	cout << "Press 'c' to continue inputting a sequence of expressions" <<endl;
	cout << "Press 's' to start over for a new sequence" <<endl; 
	
	
	getline(cin, menu);
	checkMenu(menu); 
	while ((menu != "q") || (menu != "Q")) {
		if (menu == "=") { 
			for (int i = 0; i < sequences.size(); i++) {
				if (sequences[i].get_type() == 1) {
					cout << "Cannot evaluate, " <<sequences[i].get_original() <<" it is not an arithmetic expression, but assignment!" <<endl; 
				}
				else {
					cout <<	sequences[i].get_original() << sequences[i].evaluate() <<endl; 
				}
			}	
		}
		else if (menu == ">") {
			for (int i = 0; i < sequences.size(); i++) {
				sequences[i].prefixed(); 
			}
			
			for (int i = 0; i < sequences.size(); i++) {
				if(sequences[i].get_type() == 1) {
					cout << "No prefix of " <<sequences[i].get_original() << " which is not an arithmetic expression, but assignment!" <<endl; 
				}
				else {
			
					cout << "Prefix of " <<sequences[i].get_original() << " is "; 
					sequences[i].displayPre(); 
					cout << endl; 
				}
			}
		}
		else if (menu == "<") {
			for (int i = 0; i < sequences.size(); i++) {
				sequences[i].postfixed();
			}
			
			for (int i = 0; i < sequences.size(); i++) {
				if (sequences[i].get_type() == 1) {
					cout << "No postfix of " <<sequences[i].get_original() << " which is not an arithmetic expression, but assignment!" <<endl; 
				}
				else {
					cout << "Postfix of " <<sequences[i].get_original() << " is "; 
					sequences[i].displayPost(); 
					cout << endl; 
				}
			}	
		}
		else if ((menu == "f") || (menu == "F")) {
			for (int i = 0; i < sequences.size(); i++) {
				sequences[i].parenthesize();
			}
			
			for (int i = 0; i < sequences.size(); i++) {
				if (sequences[i].get_type() == 1) {
					cout << "No postfix of " <<sequences[i].get_original() << " which is not an arithmetic expression, but assignment!" <<endl; 
				}
				else {
					cout << "Postfix of " <<sequences[i].get_original() << " is "; 
					sequences[i].displayParenth(); 
					cout << endl; 
				}
			}
			
		}
		else if ((menu == "c") || (menu == "c")) {
			string append; 
			cout << "Insert the expressions you want to add (DO NOT INCLUDE SPACES): "; 
			getline(cin, append);
			errorCheckExpress(append); 
			
			for (int i = 0; i < append.size(); i++) {
				if (append[i] != ';') {
					subSeq.push_back(append[i]); 
				}
				else {
					Expression temp; 
					temp.set(subSeq); 
					sequences.push_back(temp);  
					subSeq.clear(); 
				}
			}
		}
		else if ((menu == "s") || (menu == "S")) {
			cout << "Please, enter the sequence of expressions (DO NOT INCLUDE SPACES): "; 
			sequences.clear(); 
			getline(cin, seqExpress); 
			errorCheckExpress(seqExpress);
			
			for (int i = 0; i < seqExpress.size(); i++) {
				if (seqExpress[i] != ';') {
					subSeq.push_back(seqExpress[i]); 
				}
				else {
					Expression temp; 
					temp.set(subSeq); 
					sequences.push_back(temp);  
					subSeq.clear(); 
				}
			}
		}
		
	cout << "Please, select one of the following options: " <<endl; 
	cout << "Press '=' to evaluate" <<endl; 
	cout << "Press '>' to convert each expression in the sequence of expressions to the equivalent prefix expression" <<endl;
	cout << "Press '<' to convert each expression in the sequence of expressions to the equivalent postfix expression" <<endl;
	cout << "Press 'f' to convert each expression in the sequence of expressions to the equivalent fully parenthesized expression" <<endl;
	cout << "Press 'q' to quit the program" <<endl;
	cout << "Press 'c' to continue inputting a sequence of expressions" <<endl;
	cout << "Press 's' to start over for a new sequence" <<endl; 
		
	getline(cin, menu);
	checkMenu(menu); 
		
	}
	return 0; 
}
