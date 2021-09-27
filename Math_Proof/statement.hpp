//
//  statement.hpp
//  Math_Proof
//
//  Created by Samuel on 14/9/2021.
//  Copyright © 2021 Samuel. All rights reserved.
//

#ifndef statement_hpp
#define statement_hpp
#include <iostream>
#include <fstream>
using namespace std;

class statement;

#include "expression.hpp"

vector<substitution*> createReplacement(vector<variable*>, vector<variable*>);
vector<substitution*> createSubstitution(vector<variable*> ,expression*, vector<vector<int> >);

class statement
{
public:
    string label;
    compound_logic* content;
    variable_type var_type;
    
    //for \\forall quantifier
    vector<variable*> forall_variable;
    
    //for operator like \\iff, \\implies
    string operator_latex;
    expression* operand1;
    expression* operand2;
    
    statement(string, variable_type, string);
    statement(string, variable_type, expression*);
    void constructor_aux();
    virtual ~statement();
    
    string getLatex();
    statement* getCopy();
    expression* applyLeftToRight(statement*, vector<int>, vector<vector<int> >);
};

class Definition : public statement
{
public:
    Definition(string, variable_type, string);
    ~Definition();
    
    static void addDefinition(vector<Definition*>&, ofstream&, Definition*);
};

class Axiom : public statement
{
public:
    Axiom(string, variable_type, string);
    ~Axiom();
    
    static void addAxiom(vector<Axiom*>&, ofstream&, Axiom*);
};

class Proposition : public statement
{
public:
    Proposition(string, variable_type, string);
    ~Proposition();
    
    static void addProposition(vector<Proposition*>&, ofstream&, Proposition*);
};

template <class T>
T* FindByRef (vector<T*> v, string Name)
{
    for(long i=0;i<v.size();i++)
    {
        if(v[i]->label == Name)
        {
            return v[i];
        }
    }
    return nullptr;
}

#endif /* statement_hpp */
