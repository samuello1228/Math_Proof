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

enum direction {LeftToRight, RightToLeft};
vector<substitution*> createReplacement(vector<variable*>, vector<variable*>);
vector<substitution*> createSubstitution(vector<variable*> ,expression*, vector<vector<int> >);

class statement
{
public:
    string label;
    logic_value* content;
    variable_type var_type;
    
    //for \\forall quantifier
    vector<variable*> forall_variable;
    vector<vector<int> > path_of_variable;
    
    //for operator like \\iff, \\implies
    logic_binary_operator_logic_logic* binary_operator;
    vector<vector<int> > path_of_variable_operand1;
    vector<vector<int> > path_of_variable_operand2;
    
    statement(string, variable_type, string);
    statement(string, variable_type, expression*);
    void constructor_aux();
    logic_value* get_expression_without_forall_variable();
    void find_all_path_of_variable(bool);
    virtual ~statement();
    
    string getLatex();
    statement* getCopy();
    void delete_the_last_universal_quantifier();
    void collapse_to_operand(int);
    void collapse_to_true();
    void upgrade_to_true(direction);
    statement* apply_binary_operator(statement*, vector<int>, vector<substitution*>, direction, bool isPrint = false);
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

enum proof_method {direct, backward, deduction};
class proof_block
{
public:
    string label;
    statement* target;
    proof_method method;
    vector<string> ref_type;
    vector<string> ref;
    vector<statement*> chain_of_deductive;
    
    proof_block(string, statement*, proof_method);
    ~proof_block();
    
    statement* get_next_source();
    void check_finished(statement*);
    void append_binary_operator(vector<int>, statement*, vector<vector<int> >, direction, bool isFinished = false, bool isPrint = false);
    void append_binary_operator_advanced(vector<int>, statement*, vector<substitution*>, direction, bool isFinished = false, bool isPrint = false);
};

class Proposition : public statement
{
public:
    vector<proof_block*> proof;
    
    Proposition(string, variable_type, string);
    ~Proposition();
    void append(proof_block*, bool isFinished = true);
    
    static void addProposition(vector<Proposition*>&, ofstream&, Proposition*, string description = "");
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
