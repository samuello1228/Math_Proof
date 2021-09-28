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
#include <vector>
using namespace std;

enum variable_type {LOGIC, SET};
class substitution;
class expression;
class variable;
class compound_logic;
class logic_binary_operator_logic_logic;

#include "statement.hpp"

class substitution
{
public:
    variable* x;
    expression* y;
    
    substitution(variable*, expression*);
    ~substitution();
};

class expression
{
public:
    virtual ~expression() {}
    
    virtual string getLatex()=0;
    static expression* createFromLatex(string, variable_type);
    
    virtual bool isEqual(expression*)=0;
    virtual expression* getCopy()=0;
    virtual void replace_variable(vector<substitution*>)=0;
    static expression* substitute_forall_variable(expression* ,vector<substitution*>);
    
    virtual bool check_variable(variable_type, vector<variable*>)=0;
    virtual expression* getPart(vector<int>)=0;
    virtual void getPartExternalDependence(vector<int>, vector<variable*>&)=0;
    virtual void getInternalDependence(vector<variable*>&)=0;
    
    static void assemble(statement*, expression*, int);
};

class variable : virtual public expression
{
public:
    string latex;
    
    variable(const string&);
    virtual ~variable() {}
    
    void replace_variable(vector<substitution*>);
    bool check_variable(variable_type, vector<variable*>);
};

class logic_value : virtual public expression
{
public:
};

class elementary_logic : public logic_value
{
public:
    expression* getPart(vector<int>) {return this;}
    void getPartExternalDependence(vector<int>, vector<variable*>&) {}
    void getInternalDependence(vector<variable*>&) {return;}
};

class logic_element : public elementary_logic
{
public:
    bool value;
    
    logic_element(bool);
    
    string getLatex();
    bool isEqual(expression*);
    expression* getCopy();
    void replace_variable(vector<substitution*>) {return;}
    
    bool check_variable(variable_type, vector<variable*>);
};

class logic_variable : public elementary_logic, public variable
{
public:
    logic_variable(const string&);
    
    string getLatex();
    bool isEqual(expression*);
    expression* getCopy();
};

class compound_logic : public logic_value
{
public:
};

class Set : virtual public expression
{
public:
};

class elementary_set : public Set
{
public:
    expression* getPart(vector<int>) {return this;}
    void getPartExternalDependence(vector<int>, vector<variable*>&) {}
    void getInternalDependence(vector<variable*>&) {return;}
};

class set_element : public elementary_set
{
public:
    string latex;
};

class set_variable : public elementary_set, public variable
{
public:
    set_variable(const string&);
    
    string getLatex();
    bool isEqual(expression*);
    expression* getCopy();
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
    void replace_variable(vector<substitution*>);
    
    bool check_variable(variable_type, vector<variable*>);
    expression* getPart(vector<int>);
    void getPartExternalDependence(vector<int>, vector<variable*>&);
    void getInternalDependence(vector<variable*>&);
};

class universal_quantifier : public quantifier
{
public:
    universal_quantifier(variable*, logic_value*);
    
    bool isEqual(expression*);
    expression* getCopy();
};

class existential_quantifier : public quantifier
{
public:
    existential_quantifier(variable*, logic_value*);
    
    bool isEqual(expression*);
    expression* getCopy();
};

class logic_unary_operator_logic : public compound_logic
{
public:
    string operator_latex;
    logic_value* operand;
    
    logic_unary_operator_logic(const string&, logic_value*);
    ~logic_unary_operator_logic();
    
    string getLatex();
    bool isEqual(expression*);
    expression* getCopy();
    void replace_variable(vector<substitution*>);
    
    bool check_variable(variable_type, vector<variable*>);
    expression* getPart(vector<int>);
    void getPartExternalDependence(vector<int>, vector<variable*>&);
    void getInternalDependence(vector<variable*>&);
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
    bool isEqual(expression*);
    expression* getCopy();
    void replace_variable(vector<substitution*>);
    
    bool check_variable(variable_type, vector<variable*>);
    expression* getPart(vector<int>);
    void getPartExternalDependence(vector<int>, vector<variable*>&);
    void getInternalDependence(vector<variable*>&);
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
