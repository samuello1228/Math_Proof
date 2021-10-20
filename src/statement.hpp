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
    
    //for binary operator with transitive property: \\iff, \\implies, =
    variable_type binary_operator_type;
    logic_binary_operator_logic_logic* binary_operator_logic;
    logic_binary_operator_set_set* binary_operator_set;
    vector<vector<int> > path_of_variable_operand1;
    vector<vector<int> > path_of_variable_operand2;
    
    statement(string, variable_type, string, bool isPrint = false);
    statement(string, expression*);
    void constructor_aux();
    void set_forall_variable(vector<variable*>&, long);
    logic_value* get_expression_without_forall_variable();
    void find_all_path_of_variable(bool);
    virtual ~statement();
    
    logic_value* get_binary_operator();
    string get_binary_operator_latex();
    expression* get_oeprand(int);
    
    string getLatex();
    virtual statement* getCopy()=0;
    void delete_the_last_universal_quantifier();
    void upgrade_to_true(direction);
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
    bool isFinished;
    bool isPrint;
    
    //for binary operator
    statement* law;
    string law_label;
    direction dir;
    substitution_type sub_type;
    vector<vector<int> > source_specified_substitution;
    vector<substitution*> full_substitution;
    
    //for forall substitution
    expression* forall_substitution;
    
    input(vector<int> relative_path, string law_label, direction dir, bool isFinished = false, bool isPrint = false);
    input(vector<int> relative_path, string law_label, direction dir, vector<vector<int> > sub, bool isFinished = false, bool isPrint = false);
    input(vector<int> relative_path, string law_label, direction dir, vector<substitution*> sub, bool isFinished = false, bool isPrint = false);
    
    input(vector<int> relative_path, expression* forall_substitution, bool isFinished = false, bool isPrint = false);
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
    expression* get_next_source();
    void check_finished(statement*);
    
    void apply_binary_operator(input&, vector<variable*>, expression*, Print_Info&);
    
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
