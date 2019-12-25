#ifndef Expression_H
#define Expression_H

#include <iostream>
#include <vector>
#include "Token.h"
using namespace std; 

enum Exp_type {assignment = 1, arithmetic = 2, illegal = 3};
class Expression {
	private: 
	string original; 
	vector <Token> tokenized;
	vector <Token> postfix;
	vector <Token> prefix; 
	string parenthesized; 
	bool valid;
	Exp_type type; 
	
	public:
	Expression();
	Expression(const string& s);
	void set(const string& s);
	void postfixed();
	void prefixed(); 
	void parenthesize(); 
	void displayPost() const; 
	void displayPre() const; 
	void displayParenth () const; 
	void display() const;
	float evaluate (); 
	Exp_type get_type() const;
	string get_original() const;
	vector <Token> get_tokenized() const;
	
};
 
#endif
