
#ifndef Token_H
#define Token_H

#include <iostream>
using namespace std; 

enum Token_type{ID, INT, OP, EQ, Openbrace, Closebrace, INVALID};
class Token{
	private: 
	Token_type type;
	string token;
	int priority; 
	
	public: 
	Token();
	Token(string s);
	void set(string s);
	int value() const;
	void display() const; 
	Token_type get_type() const; 
	string get_token() const;
	int get_priority () const;
	
};

#endif 
