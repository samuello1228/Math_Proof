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
using namespace std;

#include "expression.hpp"

class statement
{
};

class Definition : public statement
{
public:
    string defining_operator;
    expression* operand1;
    expression* operand2;
};

class Axiom : public statement
{
public:
    compound_logic* content;
};

class Proposition : public statement
{
public:
    compound_logic* content;
};

#endif /* statement_hpp */
