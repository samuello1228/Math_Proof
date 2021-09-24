//
//  expression.hpp
//  Math_Proof
//
//  Created by Samuel on 15/9/2021.
//  Copyright © 2021 Samuel. All rights reserved.
//

#ifndef expression_hpp
#define expression_hpp

#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

enum variable_type {LOGIC, SET};

class variable;
class expression
{
public:
    virtual ~expression();
    
    virtual string getLatex();
    static expression* createFromLatex(string, variable_type);
    //map<variable*, expression*> replacement;
    //set<variable*> dependence;
};

class variable
{
public:
    string latex;
    
    variable(const string&);
    virtual ~variable();
    
    virtual string getLatex();
};

class logic_value : public expression
{
public:
};

class elementary_logic : public logic_value
{
public:
};

class logic_element : public elementary_logic
{
public:
    bool value;
    
    logic_element(bool);
    string getLatex();
};

class logic_variable : public elementary_logic, public variable
{
public:
    logic_variable(const string&);
    string getLatex();
};

class compound_logic : public logic_value
{
public:
    virtual bool isIff();
    virtual bool isImplies();
};

class Set : public expression
{
public:
};

class elementary_set : public Set
{
public:
};

class emptySet : public elementary_set
{
public:
};

class set_variable : public elementary_set, public variable
{
public:
    set_variable(const string&);
    string getLatex();
};

class compound_set : public Set
{
public:
};

class quantifier : public compound_logic
{
public:
    variable* var;
    logic_value* operand;

    quantifier(variable*, logic_value*);
    virtual ~quantifier();
    
    string getLatex();
};

class universal_quantifier : public quantifier
{
public:
    universal_quantifier(variable*, logic_value*);
};

class existential_quantifier : public quantifier
{
public:
    existential_quantifier(variable*, logic_value*);
};

class logic_unary_operator_logic : public compound_logic
{
public:
    string operator_latex;
    logic_value* operand;
    
    logic_unary_operator_logic(const string&, logic_value*);
    ~logic_unary_operator_logic();
    
    string getLatex();
};

class logic_binary_operator_logic_logic : public compound_logic
{
public:
    string operator_latex;
    logic_value* operand1;
    logic_value* operand2;
    
    logic_binary_operator_logic_logic(const string&, logic_value*, logic_value*);
    ~logic_binary_operator_logic_logic();
    
    string getLatex();
    bool isIff();
    bool isImplies();
};

class set_unary_operator_set : public compound_set
{
public:
    string operator_latex;
    Set* operand;
};

class logic_binary_operator_set_set : public compound_logic
{
public:
    string operator_latex;
    Set* operand1;
    Set* operand2;
};

class set_binary_operator_set_set : public compound_set
{
public:
    string operator_latex;
    Set* operand1;
    Set* operand2;
};

#endif /* expression_hpp */