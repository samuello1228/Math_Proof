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
class Proposition;

#include "expression.hpp"

enum direction {LeftToRight, RightToLeft, TrueToP, PToTrue};
vector<substitution*> createReplacement(vector<variable*>, vector<variable*>);
vector<substitution*> createSubstitution(vector<variable*> ,expression*, vector<vector<int> >);

class statement
{
public:
    string label;
    logic_value* content;
    
    //for \\forall quantifier
    vector<variable*> forall_variable;
    
    //for operator like \\iff, \\implies
    logic_binary_operator_logic_logic* binary_operator;
    vector<vector<int> > path_of_variable_operand1;
    vector<vector<int> > path_of_variable_operand2;
    
    statement(string, variable_type, string, bool isPrint = false);
    statement(string, expression*);
    void constructor_aux();
    void set_forall_variable(vector<variable*>&, long);
    logic_value* get_expression_without_forall_variable();
    void find_all_path_of_variable(bool);
    virtual ~statement();
    
    string getLatex();
    virtual statement* getCopy()=0;
    void delete_the_last_universal_quantifier();
    void collapse_to_operand(int);
    void collapse_to_true();
    void upgrade_to_true(direction);
    void apply_binary_operator(statement*, vector<int>, vector<substitution*>, bool isPrint = false);
};

class Definition : public statement
{
public:
    Definition(string, variable_type, string, bool isPrint = false);
    Definition(string, expression*);
    ~Definition();
    
    statement* getCopy();
    
    static vector<Definition*> All_Definition;
    static Definition* FindByRef(string);
    static void addDefinition(ofstream&, Definition*, string description = "");
};

class Axiom : public statement
{
public:
    Axiom(string, variable_type, string, bool isPrint = false);
    Axiom(string, expression*);
    ~Axiom();
    
    statement* getCopy();
    
    static vector<Axiom*> All_Axiom;
    static Axiom* FindByRef(string);
    static void addAxiom(ofstream&, Axiom*, string description = "");
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

struct Print_Info
{
    string ref_type;
    string ref;
    vector<vector<int> > split_point;
};

enum proof_method {direct, backward, deduction};
class proof_block
{
public:
    string label;
    statement* target;
    vector<variable*> forall_variable_proof;
    proof_method method;
    
    vector<Print_Info> print_info;
    vector<statement*> chain_of_deductive;
    
    proof_block(string, statement*, proof_method);
    proof_block(string, Proposition, proof_method);
    ~proof_block();
    
    void set_split_point(vector<vector<int> >);
    string getLatex();
    
    void set_target_forall_variable(long);
    statement* get_next_source();
    void check_finished(statement*);
    void append_binary_operator(input x);
};

class Proposition : public statement
{
public:
    vector<proof_block*> proof;
    
    Proposition(string, variable_type, string, bool isPrint = false);
    Proposition(string, expression*);
    ~Proposition();
    
    statement* getCopy();
    void append(proof_block*, bool isFinished = false);
    
    static vector<Proposition*> All_Proposition;
    static Proposition* Current;
    static Proposition* FindByRef(string);
    static void addProposition(ofstream&, Proposition*, string description = "");
};

#endif /* statement_hpp */
