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
    virtual statement* getCopy();
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
    
    statement* getCopy();
    
    static vector<Definition*> All_Definition;
    static Definition* FindByRef(string);
    static void addDefinition(ofstream&, Definition*);
};

class Axiom : public statement
{
public:
    Axiom(string, variable_type, string);
    ~Axiom();
    
    statement* getCopy();
    
    static vector<Axiom*> All_Axiom;
    static Axiom* FindByRef(string);
    static void addAxiom(ofstream&, Axiom*);
};

enum substitution_type {automatic, source_specified, full};
class input
{
public:
    vector<int> relative_path;
    
    statement* law;
    string law_label;
    
    direction dir;
    
    substitution_type sub_type;
    vector<vector<int> > source_specified_substitution;
    vector<substitution*> full_substitution;
    
    bool isFinished;
    bool isPrint;
    
    input(vector<int> relative_path, statement* law, direction dir, bool isFinished = false, bool isPrint = false);
    input(vector<int> relative_path, string law_label, direction dir, bool isFinished = false, bool isPrint = false);
    
    input(vector<int> relative_path, statement* law, direction dir, vector<vector<int> > sub, bool isFinished = false, bool isPrint = false);
    input(vector<int> relative_path, string law_label, direction dir, vector<vector<int> > sub, bool isFinished = false, bool isPrint = false);
    
    input(vector<int> relative_path, statement* law, direction dir, vector<substitution*> sub, bool isFinished = false, bool isPrint = false);
    input(vector<int> relative_path, string law_label, direction dir, vector<substitution*> sub, bool isFinished = false, bool isPrint = false);
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
    void append_binary_operator(input x);
};

class Proposition : public statement
{
public:
    vector<proof_block*> proof;
    
    Proposition(string, variable_type, string);
    ~Proposition();
    
    statement* getCopy();
    void append(proof_block*, bool isFinished = true);
    
    static vector<Proposition*> All_Proposition;
    static Proposition* FindByRef(string);
    static void addProposition(ofstream&, Proposition*, string description = "");
};

#endif /* statement_hpp */
