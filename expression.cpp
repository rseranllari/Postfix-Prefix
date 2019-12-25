#include "Expression.h"
#include <stack>

//constructor 
Expression::Expression() {
	original = " ";
	valid = false; 
	type = illegal; 
}

//copy contructor 
Expression::Expression(const string& s) {
	
	set(s); 
	
}

//set method, used to set the private variables 
void Expression::set(const string& s) {
	
	original = s; //original string
	string str = ""; 
	int i = 0; 
	
	while (i < s.size()){ //until the end of the string
		//if the char at i is equal to =, /, *, -, +, (, ), or ; they is a space added between them
		if ((s.at(i) == '=') || (s.at(i) == '/') || (s.at(i) == '*') || (s.at(i) == '-') || (s.at(i) == '+') || (s.at(i) == '(') || (s.at(i) == ')') || (s.at(i) ==';')) {
			str.push_back(' '); 
			str.push_back(s.at(i));
			str.push_back(' ');
		}
		else {
			str.push_back(s.at(i)); 
		}
		i++;
	}
	
	string set;
	int j; 
	i = 0; 
	while (i < str.size()) {
	//if there is a space, we have found a token added into the tokenized vector 
		while ((str[i] == ' ') && (str[i] != '\0')) {
			i++;
		}	
		 
		j = i; 
		
		while ((str[j] != ' ' ) && (str[j] != '\0')){
			j++;
		} 
	
		for (i; i < j; i++) {
			set.push_back(str[i]);
		}
		
		i = j + 1; 
	
		tokenized.push_back(set); 
		set.clear(); 
	}
	
	i = 0, j = 0;
	
	// check if there is any = signs 
	while (s[i] != '=') {
		i++; 
	}
	
	
	//check if there isnt any = signs
	while ((s[j] == '+') || (s[j] == '-') || (s[j] == '*') || (s[j] == '/') || (isdigit(s[j])) || (isalpha(s[j]))) {
		j++;
	}
	
	//if there is an = sign, type is assignment
	if (i < s.size()) {
		type = assignment; 
		valid = true; 
	}
	
	//else is an arithmetic 
	else if (j == s.size()) {
		type = arithmetic; 
		valid = true;
	}
	//if neither applies it is an illegal type
	else {
		type = illegal;
		valid = false; 
	}
	
	
}

//we postfix the tokenized expression earlier. 
void Expression::postfixed(){
		stack <Token> ops; 
	
		int i = 0;
		for (i; i < tokenized.size(); i++) {
	
			if ((tokenized[i].get_type() == ID ) || (tokenized[i].get_type() == INT)) {
				postfix.push_back(tokenized[i]);
			}
	
			else if (tokenized[i].get_type() == Openbrace) {
				ops.push(tokenized[i]);
			}
	
			else if (tokenized[i].get_type() == Closebrace) {
				while (ops.top().get_type() != Openbrace) {
					postfix.push_back(ops.top());
					ops.pop();
				}
				ops.pop(); 
			}
			else  if (tokenized[i].get_type() == OP) {
				while ((!ops.empty()) && (ops.top().get_priority() >= tokenized[i].get_priority())){
					postfix.push_back(ops.top());
					ops.pop(); 
				}
				ops.push(tokenized[i]);
			}
		}
		while (!ops.empty()) {
			postfix.push_back(ops.top());
			ops.pop(); 
		}
}

//we prefix the expression
void Expression::prefixed() {
	
	int index; 
	while ((tokenized[index].get_type() != EQ) && index < tokenized.size()) {
		index++; 
	}
	
	if (index == tokenized.size()) {

		stack <Token> ops;

		int i = 0; 
		while (i < tokenized.size()) {
			if (tokenized[i].get_type() == Openbrace) {
				ops.push(tokenized[i]); 
			}
			else if (tokenized[i].get_type() == Closebrace) {
				while (!ops.empty() && ops.top().get_type() != Openbrace) {
					Token op1 = prefix.back(); 
					prefix.pop_back(); 
				
					Token op2 = prefix.back();
					prefix.pop_back(); 
				
					Token op = ops.top();
					ops.pop(); 
				
					string temp = op.get_token() + " " + op2.get_token() + " " + op1.get_token();
					prefix.push_back(temp);  
				}
			ops.pop(); 
			}
		
			else if ((tokenized[i].get_type() == ID) || (tokenized[i].get_type() == INT)){
				prefix.push_back(tokenized[i]); 
			}
			else {
				while (!ops.empty() && tokenized[i].get_priority() <= ops.top().get_priority()) {
				
					Token op1 = prefix.back();
					prefix.pop_back();
				
					Token op2 = prefix.back();
					prefix.pop_back();
				
					Token op = ops.top();
					ops.pop(); 
				
					string temp = op.get_token() + " " + op2.get_token() + " " + op1.get_token();
					prefix.push_back(temp); 
				} 
			ops.push(tokenized[i]); 
			}
			i++; 
		}
	
		while (!ops.empty()) {
			Token op1 = prefix.back();
			prefix.pop_back(); 
		
			Token op2 = prefix.back();
			prefix.pop_back(); 
		
			Token op = ops.top();
			ops.pop();
			
			string temp = op.get_token() + " " + op2.get_token() +" " +op1.get_token();
			prefix.push_back(temp); 
		}
}
}

void Expression::parenthesize() {
	
//	postfixed(); //make sure the vector isnt empty
	stack <string> ops; 
	
	string a, b;  
	string parenthesis; 
	for (int i = 0; i < postfix.size(); i++) {
		if (postfix[i].get_type() == OP) {
			a = ops.top(); //get the top
			ops.pop(); //pop the top
			b= ops.top(); //get the top
			ops.pop();  // pop the top
			parenthesis= "(" + b + postfix[i].get_token() + a + ")";
			ops.push(parenthesis); //push the result back in the sa
		}
		else if((postfix[i].get_type() == INT) || (postfix[i].get_type() == ID)) { //if is an operand
			ops.push(postfix[i].get_token());//push the operand on the stack
		}
	}
	
	parenthesized = ops.top(); 
}


//methods used to print out the orignal, parenthesized, postfixed, prefixed. 
void Expression::displayPost() const {
	
	for (int i = 0; i < postfix.size(); i++) {
		cout << postfix[i].get_token() <<" "; 
	}
}

void Expression::displayPre() const {

	for (int i = 0; i < prefix.size(); i++) {
		cout << prefix[i].get_token() <<" "; 
	}
}

void Expression::displayParenth() const {

		cout << parenthesized; 

}

void Expression::display() const {
	
	for (int i = 0; i < tokenized.size(); i++) {
		cout << tokenized[i].get_token() <<" ";
	}

}

//used to calculate for the evaluation method
float calculate (float a, float b, string op) {
    if (op ==  "+")
		return a + b; 
    else if (op == "-")
		return a - b; 
    else if (op == "*")
		return a * b; 
    else if (op == "/")
		return a / b;
}

float Expression::evaluate() {

	postfixed(); //calling the function to make sure parenthesized isnt empty
	float a, b;

	stack <float> ops; //stack for operands

	for (int i = 0; i < postfix.size(); i++) {
		if(postfix[i].get_type() == OP) {
			a = ops.top(); //get the top
			ops.pop(); //pop the top
			b = ops.top(); //get the top
			ops.pop(); //pop the top
			ops.push(calculate(b, a, postfix[i].get_token())); //push the val on the stack
		}
		else if (postfix[i].get_type() == INT) {
			ops.push(postfix[i].value()); //if an operand push it on the stack
		}
	}
	return ops.top(); 
}


Exp_type Expression::get_type() const {
	return type; 
}

string Expression::get_original() const {
	return original; 

}

vector <Token> Expression::get_tokenized() const{
	return tokenized; 

}

