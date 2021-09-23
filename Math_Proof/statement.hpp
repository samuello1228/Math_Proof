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

#include "expression.hpp"

class statement
{
public:
    string label;
    
    statement(string);
    virtual ~statement();
};

class Definition : public statement
{
public:
    compound_logic* content;
    
    Definition(string, variable_type, string);
    ~Definition();
    
    string getLatex();
    static void addDefinition(vector<Definition*>&, ofstream&, Definition*);
};

class Axiom : public statement
{
public:
    compound_logic* content;
    
    Axiom(string, compound_logic*);
    ~Axiom();
};

class Proposition : public statement
{
public:
    compound_logic* content;
    
    Proposition(string, compound_logic*);
    ~Proposition();
};

#endif /* statement_hpp */
