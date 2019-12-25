#include <sstream> 
#include "Token.h"
#include "Expression.h"

Token::Token() {
	type = INVALID; 
	token = " "; 
	priority  = -1; 
}

Token::Token(string s) {
	
	set(s); 
	
}

void Token::set(string s) {
	token = s;
	priority = -1; 
	 
	if ((s.at(0) == '=') && (s.size() == 1)){
		type  = EQ; 
		priority = -2; 
	}
	else if ((s.at(0) == '(') && (s.size() == 1)){
		type = Openbrace;
		priority = 0; 
	}
	else if ((s.at(0) == ')') && (s.size() == 1)){
		type = Closebrace;
		priority = -2;
	}
	else if ((s.at(0) == '+') ||(s.at(0) == '-') && (s.size() == 1)) {
		type = OP; 
		priority = 1; 
	}
	else if  ((s.at(0) == '*') || (s.at(0) =='/') && (s.size() == 1)){
		type = OP;
		priority = 2;
	}
	else if (isalpha(s.at(0)) != 0) {
		int i = 0; 
		while (((i < s.size()) && (isalpha(s.at(i)) != 0)) || ((i < s.size()) && (isdigit(s.at(i))!= 0))) {
			i++; 
		}
		if (i == s.size()) 
			type = ID;
		else {
			type = INVALID;
			priority = -2;  
		}
	}
	else if (isdigit(s.at(0)) != 0) {
		int i = 0; 
		while ((i < s.size()) && (isdigit(s.at(i)) != 0)) {
			i++;
		}
		
		if (i == s.size()) {
			type = INT;
			stringstream change (token);
			int x = 0;
			change >> x;
			priority = x;
		}
		else {
			type = INVALID; 
			priority = -2; 
		}
	}
	else {
		type = INVALID;
		priority = -2;  
	}
	
}

int Token::value() const{
	
	if (type == INT) {
		stringstream change (token);
		int x = 0;
		change >> x;
		return x; 
	}
	else if (type == ID){
		return -1;
	}
	else {
		return -2; 
	}

}

void Token::display() const {

	cout << token << " ";
}

Token_type Token::get_type() const {
	return type;

}

string Token::get_token() const {
	return token;

}

int Token::get_priority() const {
	return priority; 

}

