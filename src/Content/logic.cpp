//
//  logic.cpp
//  Math_Proof
//
//  Created by Samuel on 19/9/2021.
//  Copyright © 2021 Samuel. All rights reserved.
//

#include "logic.hpp"

void logic()
{
    ofstream fout;
    fout.open("../tex/logic.tex");
    
    //Definition of Proposition
    fout<<"\\chapter{Logic}"<<endl;
    fout<<"\\begin{defn}"<<endl;
    fout<<"Proposition is a statement that is either true or false, but not both."<<endl;
    fout<<"\\end{defn}"<<endl;
    fout<<endl;
    
    //Logical operations
    fout<<"\\section{Logical operations}"<<endl;
    //Definition of NOT
    fout<<"\\subsection{Definition of $\\lnot$}"<<endl;
    Definition::addDefinition(fout, new Definition("lnot_True", LOGIC, "(\\lnot (\\text{True})) \\iff (\\text{False})"));
    Definition::addDefinition(fout, new Definition("lnot_False", LOGIC, "(\\lnot (\\text{False})) \\iff (\\text{True})"));
    
    //Definition of OR
    fout<<"\\subsection{Definition of $\\lor$}"<<endl;
    Definition::addDefinition(fout, new Definition("lor_True_True", LOGIC, "((\\text{True}) \\lor (\\text{True})) \\iff (\\text{True})"));
    Definition::addDefinition(fout, new Definition("lor_True_False", LOGIC, "((\\text{True}) \\lor (\\text{False})) \\iff (\\text{True})"));
    Definition::addDefinition(fout, new Definition("lor_False_True", LOGIC, "((\\text{False}) \\lor (\\text{True})) \\iff (\\text{True})"));
    Definition::addDefinition(fout, new Definition("lor_False_False", LOGIC, "((\\text{False}) \\lor (\\text{False})) \\iff (\\text{False})"));
    
    //Definition of AND
    fout<<"\\subsection{Definition of $\\land$}"<<endl;
    Definition::addDefinition(fout, new Definition("land_True_True", LOGIC, "((\\text{True}) \\land (\\text{True})) \\iff (\\text{True})"));
    Definition::addDefinition(fout, new Definition("land_True_False", LOGIC, "((\\text{True}) \\land (\\text{False})) \\iff (\\text{False})"));
    Definition::addDefinition(fout, new Definition("land_False_True", LOGIC, "((\\text{False}) \\land (\\text{True})) \\iff (\\text{False})"));
    Definition::addDefinition(fout, new Definition("land_False_False", LOGIC, "((\\text{False}) \\land (\\text{False})) \\iff (\\text{False})"));
    
    //Definition of iff
    fout<<"\\subsection{Definition of $\\iff$}"<<endl;
    Definition::addDefinition(fout, new Definition("iff", LOGIC, "\\forall a \\forall b ((a \\iff b) \\iff ((a \\land b) \\lor ((\\lnot a) \\land (\\lnot b))))"));
    
    //Definition of implies
    fout<<"\\subsection{Definition of $\\implies$}"<<endl;
    Definition::addDefinition(fout, new Definition("implies", LOGIC, "\\forall a \\forall b ((a \\implies b) \\iff ((\\lnot a) \\lor b))"));
    
    //Boolean algebra
    statement* law = nullptr;
    proof_block* block = nullptr;
    vector<substitution*> sub;
    string description;
    fout<<"\\section{Boolean algebra}"<<endl;
    //Associativity
    fout<<"\\subsection{Associativity of $\\lor$}"<<endl;
    Proposition::addProposition(fout, new Proposition("lor_associativity", LOGIC, "\\forall a \\forall b \\forall c (((a \\lor b) \\lor c) \\iff (a \\lor (b \\lor c)))"));
    
    fout<<"\\subsection{Associativity of $\\land$}"<<endl;
    Proposition::addProposition(fout, new Proposition("land_associativity", LOGIC, "\\forall a \\forall b \\forall c (((a \\land b) \\land c) \\iff (a \\land (b \\land c)))"));
    
    //Commutativity
    fout<<"\\subsection{Commutativity of $\\lor$}"<<endl;
    Proposition::addProposition(fout, new Proposition("lor_commutativity", LOGIC, "\\forall a \\forall b ((a \\lor b) \\iff (b \\lor a))"));
    
    fout<<"\\subsection{Commutativity of $\\land$}"<<endl;
    Proposition::addProposition(fout, new Proposition("land_commutativity", LOGIC, "\\forall a \\forall b ((a \\land b) \\iff (b \\land a))"));
    
    //Identity
    fout<<"\\subsection{Identity of $\\lor$}"<<endl;
    Proposition::addProposition(fout, new Proposition("lor_identity_1", LOGIC, "\\forall a ((a \\lor (\\text{False})) \\iff a)"));
    
    Proposition::Current = new Proposition("lor_identity_2", LOGIC, "\\forall a (((\\text{False}) \\lor a) \\iff a)");
    Proposition::addProposition(fout, Proposition::Current);
    
    fout<<"\\subsection{Identity of $\\land$}"<<endl;
    Proposition::addProposition(fout, new Proposition("land_identity_1", LOGIC, "\\forall a ((a \\land (\\text{True})) \\iff a)"));
    Proposition::addProposition(fout, new Proposition("land_identity_2", LOGIC, "\\forall a (((\\text{True}) \\land a) \\iff a)"));
    
    //Annihilator
    fout<<"\\subsection{Annihilator of $\\lor$}"<<endl;
    Proposition::addProposition(fout, new Proposition("lor_annihilator_1", LOGIC, "\\forall a ((a \\lor (\\text{True})) \\iff (\\text{True}))"));
    Proposition::addProposition(fout, new Proposition("lor_annihilator_2", LOGIC, "\\forall a (((\\text{True}) \\lor a) \\iff (\\text{True}))"));
    
    fout<<"\\subsection{Annihilator of $\\land$}"<<endl;
    Proposition::addProposition(fout, new Proposition("land_annihilator_1", LOGIC, "\\forall a ((a \\land (\\text{False})) \\iff (\\text{False}))"));
    Proposition::addProposition(fout, new Proposition("land_annihilator_2", LOGIC, "\\forall a (((\\text{False}) \\land a) \\iff (\\text{False}))"));
    
    //Idempotence
    fout<<"\\subsection{Idempotence of $\\lor$}"<<endl;
    Proposition::addProposition(fout, new Proposition("lor_idempotence", LOGIC, "\\forall a ((a \\lor a) \\iff a)"));
    
    fout<<"\\subsection{Idempotence of $\\land$}"<<endl;
    Proposition::addProposition(fout, new Proposition("land_idempotence", LOGIC, "\\forall a ((a \\land a) \\iff a)"));
    
    //Complement
    fout<<"\\subsection{Complement of $\\lor$}"<<endl;
    Proposition::addProposition(fout, new Proposition("lor_complement_1", LOGIC, "\\forall a ((a \\lor (\\lnot a)) \\iff (\\text{True}))"));
    Proposition::addProposition(fout, new Proposition("lor_complement_2", LOGIC, "\\forall a (((\\lnot a) \\lor a) \\iff (\\text{True}))"));
    
    fout<<"\\subsection{Complement of $\\land$}"<<endl;
    Proposition::addProposition(fout, new Proposition("land_complement_1", LOGIC, "\\forall a ((a \\land (\\lnot a)) \\iff (\\text{False}))"));
    Proposition::addProposition(fout, new Proposition("land_complement_2", LOGIC, "\\forall a (((\\lnot a) \\land a) \\iff (\\text{False}))"));
    
    //Absorption
    fout<<"\\subsection{Absorption of $\\lor$ over $\\land$}"<<endl;
    Proposition::addProposition(fout, new Proposition("lor_land_absorption_1", LOGIC, "\\forall a \\forall b ((a \\lor (a \\land b)) \\iff a)"));
    Proposition::addProposition(fout, new Proposition("lor_land_absorption_2", LOGIC, "\\forall a \\forall b ((a \\lor (b \\land a)) \\iff a)"));
    Proposition::addProposition(fout, new Proposition("lor_land_absorption_3", LOGIC, "\\forall a \\forall b (((a \\land b) \\lor a) \\iff a)"));
    Proposition::addProposition(fout, new Proposition("lor_land_absorption_4", LOGIC, "\\forall a \\forall b (((b \\land a) \\lor a) \\iff a)"));
    
    fout<<"\\subsection{Absorption of $\\land$ over $\\lor$}"<<endl;
    Proposition::addProposition(fout, new Proposition("land_lor_absorption_1", LOGIC, "\\forall a \\forall b ((a \\land (a \\lor b)) \\iff a)"));
    Proposition::addProposition(fout, new Proposition("land_lor_absorption_2", LOGIC, "\\forall a \\forall b ((a \\land (b \\lor a)) \\iff a)"));
    Proposition::addProposition(fout, new Proposition("land_lor_absorption_3", LOGIC, "\\forall a \\forall b (((a \\lor b) \\land a) \\iff a)"));
    Proposition::addProposition(fout, new Proposition("land_lor_absorption_4", LOGIC, "\\forall a \\forall b (((b \\lor a) \\land a) \\iff a)"));
    
    //Distributivity
    fout<<"\\subsection{Distributivity of $\\lor$ over $\\land$}"<<endl;
    Proposition::addProposition(fout, new Proposition("lor_land_distributivity_1", LOGIC, "\\forall a \\forall b \\forall c ((a \\lor (b \\land c)) \\iff ((a \\lor b) \\land (a \\lor c)))"));
    Proposition::addProposition(fout, new Proposition("lor_land_distributivity_2", LOGIC, "\\forall a \\forall b \\forall c (((a \\land b) \\lor c) \\iff ((a \\lor c) \\land (b \\lor c)))"));
    
    fout<<"\\subsection{Distributivity of $\\land$ over $\\lor$}"<<endl;
    Proposition::addProposition(fout, new Proposition("land_lor_distributivity_1", LOGIC, "\\forall a \\forall b \\forall c ((a \\land (b \\lor c)) \\iff ((a \\land b) \\lor (a \\land c)))"));
    Proposition::addProposition(fout, new Proposition("land_lor_distributivity_2", LOGIC, "\\forall a \\forall b \\forall c (((a \\lor b) \\land c) \\iff ((a \\land c) \\lor (b \\land c)))"));
    
    //Double negation
    fout<<"\\subsection{Double negation}"<<endl;
    Proposition::addProposition(fout, new Proposition("double_negation", LOGIC, "\\forall a ((\\lnot (\\lnot a)) \\iff a)"));
    
    //De Morgan's laws
    fout<<"\\subsection{De Morgan's laws}"<<endl;
    Proposition::addProposition(fout, new Proposition("De_Morgan_lor", LOGIC, "\\forall a \\forall b ((\\lnot (a \\lor b)) \\iff ((\\lnot a) \\land (\\lnot b)))"));
    Proposition::addProposition(fout, new Proposition("De_Morgan_land", LOGIC, "\\forall a \\forall b ((\\lnot (a \\land b)) \\iff ((\\lnot a) \\lor (\\lnot b)))"));
    
    //Basic Proposition
    fout<<"\\section{Basic Proposition}"<<endl;
    
    //a_lor_b_complement
    fout<<"\\subsection{Complement of a $\\lor$ b}"<<endl;
    Proposition::Current = new Proposition("a_lor_b_complement_1", LOGIC, "\\forall a \\forall b (((a \\land (\\lnot b)) \\lor b) \\iff (a \\lor b))");
    block = new proof_block("a_lor_b_complement_1", Proposition::Current, deduction);
    block->append_binary_operator(input({}, "Proposition:lor_land_distributivity_2", LeftToRight));
    block->append_binary_operator(input({2}, "Proposition:lor_complement_2", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:land_identity_1", LeftToRight, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current);
    
    Proposition::Current = new Proposition("a_lor_b_complement_2", LOGIC, "\\forall a \\forall b (((a \\land b) \\lor (\\lnot b)) \\iff (a \\lor (\\lnot b)))");
    block = new proof_block("a_lor_b_complement_2", Proposition::Current, deduction);
    block->append_binary_operator(input({}, "Proposition:lor_land_distributivity_2", LeftToRight));
    block->append_binary_operator(input({2}, "Proposition:lor_complement_1", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:land_identity_1", LeftToRight, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current);
    
    //Multiple assumption
    fout<<"\\subsection{Multiple assumption}"<<endl;
    Proposition::Current = new Proposition("multiple_assumption", LOGIC, "\\forall a \\forall b \\forall c ((a \\implies (b \\implies c)) \\iff ((a \\land b) \\implies c))");
    block = new proof_block("multiple_assumption", Proposition::Current, deduction);
    block->append_binary_operator(input({2}, "Definition:implies", LeftToRight));
    block->append_binary_operator(input({}, "Definition:implies", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:lor_associativity", RightToLeft));
    block->append_binary_operator(input({1}, "Proposition:De_Morgan_land", RightToLeft));
    block->append_binary_operator(input({}, "Definition:implies", RightToLeft, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current);
    
    //Proof technique
    fout<<"\\section{Proof technique}"<<endl;
    
    //true statement
    Proposition::Current = new Proposition("true_statement", LOGIC, "\\forall a ((a \\iff (\\text{True})) \\iff a)");
    block = new proof_block("true_statement", Proposition::Current, deduction);
    block->append_binary_operator(input({}, "Definition:iff", LeftToRight));
    block->append_binary_operator(input({2,2}, "Definition:lnot_True", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:land_identity_1", LeftToRight));
    block->append_binary_operator(input({2}, "Proposition:land_annihilator_1", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:lor_identity_1", LeftToRight, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current);
    
    fout<<"\\subsection{Axiom of Substitution for $\\implies$}"<<endl;
    Proposition::Current = new Proposition("implies_substitution_lor", LOGIC, "\\forall a \\forall b \\forall c ((a \\implies b) \\implies ((a \\lor c) \\implies (b \\lor c)))");
    description = "Substitution of $\\implies$ for $\\lor$";
    block = new proof_block("implies_substitution_lor", Proposition::Current, backward);
    block->append_binary_operator(input({1}, "Definition:implies", LeftToRight));
    block->append_binary_operator(input({2}, "Definition:implies", LeftToRight));
    block->append_binary_operator(input({}, "Definition:implies", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:De_Morgan_lor", LeftToRight));
    block->append_binary_operator(input({1,1}, "Proposition:double_negation", LeftToRight));
    block->append_binary_operator(input({2,1}, "Proposition:De_Morgan_lor", LeftToRight));
    block->append_binary_operator(input({2,2}, "Proposition:lor_commutativity", LeftToRight));
    block->append_binary_operator(input({2}, "Proposition:lor_associativity", RightToLeft));
    block->append_binary_operator(input({2}, "Proposition:lor_commutativity", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:lor_associativity", RightToLeft));
    block->append_binary_operator(input({1}, "Proposition:a_lor_b_complement_1", LeftToRight));
    block->append_binary_operator(input({2}, "Proposition:a_lor_b_complement_1", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:lor_associativity", RightToLeft));
    block->append_binary_operator(input({1}, "Proposition:lor_commutativity", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:lor_associativity", RightToLeft));
    block->append_binary_operator(input({1,1}, "Proposition:lor_complement_2", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:lor_annihilator_2", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:lor_annihilator_2", LeftToRight, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    Proposition::Current = new Proposition("implies_substitution_land", LOGIC, "\\forall a \\forall b \\forall c ((a \\implies b) \\implies ((a \\land c) \\implies (b \\land c)))");
    description = "Substitution of $\\implies$ for $\\land$";
    block = new proof_block("implies_substitution_land", Proposition::Current, backward);
    block->append_binary_operator(input({1}, "Definition:implies", LeftToRight));
    block->append_binary_operator(input({2}, "Definition:implies", LeftToRight));
    block->append_binary_operator(input({}, "Definition:implies", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:De_Morgan_lor", LeftToRight));
    block->append_binary_operator(input({1,1}, "Proposition:double_negation", LeftToRight));
    block->append_binary_operator(input({2,1}, "Proposition:De_Morgan_land", LeftToRight));
    block->append_binary_operator(input({2}, "Proposition:lor_associativity", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:lor_associativity", RightToLeft));
    block->append_binary_operator(input({1,1}, "Proposition:land_commutativity", LeftToRight));
    block->append_binary_operator(input({2}, "Proposition:lor_commutativity", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:a_lor_b_complement_2", LeftToRight));
    block->append_binary_operator(input({2}, "Proposition:a_lor_b_complement_2", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:lor_associativity", RightToLeft));
    block->append_binary_operator(input({1}, "Proposition:lor_commutativity", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:lor_associativity", RightToLeft));
    block->append_binary_operator(input({1,1}, "Proposition:lor_complement_1", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:lor_annihilator_2", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:lor_annihilator_2", LeftToRight, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    Proposition::Current = new Proposition("implies_substitution_implies", LOGIC, "\\forall a \\forall b \\forall c ((a \\implies b) \\implies ((c \\implies a) \\implies (c \\implies b)))");
    description = "Substitution of $\\implies$ for $\\implies$";
    block = new proof_block("implies_substitution_implies", Proposition::Current, backward);
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    //contrapositive
    Proposition::Current = new Proposition("contrapositive", LOGIC, "\\forall a \\forall b ((a \\implies b) \\iff ((\\lnot b) \\implies (\\lnot a)))");
    description = "Contrapositive";
    Proposition::addProposition(fout, Proposition::Current, description);
    
    //Transitive property of implies
    Proposition::Current = new Proposition("implies_transitive", LOGIC, "\\forall a \\forall b \\forall c (((a \\implies b) \\land (b \\implies c)) \\implies (a \\implies c))");
    description = "Transitive property of $\\implies$.";
    Proposition::addProposition(fout, Proposition::Current, description);
    
    //iff and implies
    Proposition::Current = new Proposition("iff_implies", LOGIC, "\\forall a \\forall b ((a \\iff b) \\iff ((a \\implies b) \\land (b \\implies a)))");
    Proposition::addProposition(fout, Proposition::Current);
    
    //iff
    Proposition::Current = new Proposition("iff_lor", LOGIC, "\\forall a \\forall b \\forall c ((a \\iff b) \\implies ((a \\lor c) \\iff (b \\lor c)))");
    Proposition::addProposition(fout, Proposition::Current);
    
    Proposition::Current = new Proposition("iff_land", LOGIC, "\\forall a \\forall b \\forall c ((a \\iff b) \\implies ((a \\land c) \\iff (b \\land c)))");
    Proposition::addProposition(fout, Proposition::Current);
    
    Proposition::Current = new Proposition("iff_symmetric", LOGIC, "\\forall a \\forall b ((a \\iff b) \\iff (b \\iff a))");
    description = "Symmetric property of $\\iff$.";
    Proposition::addProposition(fout, Proposition::Current, description);
    
    Proposition::Current = new Proposition("iff_contrapositive", LOGIC, "\\forall a \\forall b ((a \\iff b) \\iff ((\\lnot a) \\iff (\\lnot b)))");
    Proposition::addProposition(fout, Proposition::Current);
    
    Proposition::Current = new Proposition("iff_transitive", LOGIC, "\\forall a \\forall b \\forall c (((a \\iff b) \\land (b \\iff c)) \\implies (a \\iff c))");
    description = "Transitive property of $\\iff$.";
    Proposition::addProposition(fout, Proposition::Current, description);
    
    Proposition::Current = new Proposition("iff_reflexive", LOGIC, "\\forall a (a \\iff a)");
    description = "Reflexive property of $\\iff$.";
    block = new proof_block("iff_reflexive", Proposition::Current, backward);
    block->append_binary_operator(input({}, "Definition:iff", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:land_idempotence", LeftToRight));
    block->append_binary_operator(input({2}, "Proposition:land_idempotence", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:lor_complement_1", LeftToRight, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    //Quantifiers
    fout<<"\\section{Quantifiers}"<<endl;
    
    //Universal quantifier
    fout<<"\\begin{defn}"<<endl;
    fout<<"Universal quantifier is denoted by $\\forall$."<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& \\forall x (P(x)) \\\\"<<endl;
    fout<<"\\overset{\\operatorname{def}}{\\iff} & (P(x_1) \\land P(x_2) \\land \\dots)"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{defn}"<<endl;
    fout<<endl;
    
    //Existential quantifier
    fout<<"\\begin{defn}"<<endl;
    fout<<"Existential quantifier is denoted by $\\exists$."<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& \\exists x (P(x)) \\\\"<<endl;
    fout<<"\\overset{\\operatorname{def}}{\\iff} & (P(x_1) \\lor P(x_2) \\lor \\dots)"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{defn}"<<endl;
    fout<<endl;
    
    {
        logic_variable* a = new logic_variable("a");
        set_variable* c = new set_variable("c");
        universal_quantifier* u1 = new universal_quantifier(c,a);
        
        c = new set_variable("c");
        logic_variable* b = new logic_variable("b");
        universal_quantifier* u2 = new universal_quantifier(c,b);
        
        logic_binary_operator_logic_logic* u1_and_u2 = new logic_binary_operator_logic_logic("\\land", u1, u2);
        
        a = new logic_variable("a");
        b = new logic_variable("b");
        logic_binary_operator_logic_logic* a_and_b = new logic_binary_operator_logic_logic("\\land", a, b);
        c = new set_variable("c");
        universal_quantifier* u3 = new universal_quantifier(c, a_and_b);
        
        logic_binary_operator_logic_logic* iff = new logic_binary_operator_logic_logic("\\iff", u1_and_u2, u3);
        
        b = new logic_variable("b");
        universal_quantifier* u4 = new universal_quantifier(b, iff);
        a = new logic_variable("a");
        universal_quantifier* u5 = new universal_quantifier(a, u4);
        
        Proposition::Current = new Proposition("forall_land_commutativity", u5);
    }
    Proposition::addProposition(fout, Proposition::Current);
    
    {
        logic_variable* a = new logic_variable("a");
        set_variable* c = new set_variable("c");
        existential_quantifier* e1 = new existential_quantifier(c,a);
        
        c = new set_variable("c");
        logic_variable* b = new logic_variable("b");
        existential_quantifier* e2 = new existential_quantifier(c,b);
        
        logic_binary_operator_logic_logic* e1_or_e2 = new logic_binary_operator_logic_logic("\\lor", e1, e2);
        
        a = new logic_variable("a");
        b = new logic_variable("b");
        logic_binary_operator_logic_logic* a_or_b = new logic_binary_operator_logic_logic("\\lor", a, b);
        c = new set_variable("c");
        existential_quantifier* e3 = new existential_quantifier(c, a_or_b);
        
        logic_binary_operator_logic_logic* iff = new logic_binary_operator_logic_logic("\\iff", e1_or_e2, e3);
        
        b = new logic_variable("b");
        universal_quantifier* u4 = new universal_quantifier(b, iff);
        a = new logic_variable("a");
        universal_quantifier* u5 = new universal_quantifier(a, u4);
        
        Proposition::Current = new Proposition("exists_lor_commutativity", u5);
    }
    Proposition::addProposition(fout, Proposition::Current);
    
    fout<<"\\begin{prop}"<<endl;
    fout<<"\\label{Proposition:lor_forall_distributivity}"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& P \\lor (\\forall x (Q(x))) \\\\"<<endl;
    fout<<"\\iff & \\forall x (P \\lor (Q(x)))"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{prop}"<<endl;
    fout<<endl;
    
    fout<<"\\begin{prop}"<<endl;
    fout<<"\\label{Proposition:land_exists_distributivity}"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& P \\land (\\exists x (Q(x))) \\\\"<<endl;
    fout<<"\\iff & \\exists x (P \\land (Q(x)))"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{prop}"<<endl;
    fout<<endl;
    
    fout<<"\\begin{axm}"<<endl;
    fout<<"\\label{Axiom:forall_independent_variable}"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& \\forall x (P(y)) \\\\"<<endl;
    fout<<"\\iff & P(y)"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{axm}"<<endl;
    fout<<endl;
    
    fout<<"\\begin{axm}"<<endl;
    fout<<"\\label{Axiom:exists_independent_variable}"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& \\exists x (P(y)) \\\\"<<endl;
    fout<<"\\iff & P(y)"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{axm}"<<endl;
    fout<<endl;
    
    {
        logic_variable* a = new logic_variable("a");
        set_variable* b = new set_variable("b");
        universal_quantifier* q1 = new universal_quantifier(b, a);
        logic_unary_operator_logic* not1 = new logic_unary_operator_logic("\\lnot", q1);
        
        a = new logic_variable("a");
        logic_unary_operator_logic* not2 = new logic_unary_operator_logic("\\lnot", a);
        b = new set_variable("b");
        existential_quantifier* q2 = new existential_quantifier(b, not2);
        
        logic_binary_operator_logic_logic* iff = new logic_binary_operator_logic_logic("\\iff", not1, q2);
        
        a = new logic_variable("a");
        universal_quantifier* u3 = new universal_quantifier(a, iff);
        
        Proposition::Current = new Proposition("De_Morgan_1", u3);
    }
    Proposition::addProposition(fout, Proposition::Current, "De Morgan's law");
    
    {
        logic_variable* a = new logic_variable("a");
        set_variable* b = new set_variable("b");
        existential_quantifier* q1 = new existential_quantifier(b, a);
        logic_unary_operator_logic* not1 = new logic_unary_operator_logic("\\lnot", q1);
        
        a = new logic_variable("a");
        logic_unary_operator_logic* not2 = new logic_unary_operator_logic("\\lnot", a);
        b = new set_variable("b");
        universal_quantifier* q2 = new universal_quantifier(b, not2);
        
        logic_binary_operator_logic_logic* iff = new logic_binary_operator_logic_logic("\\iff", not1, q2);
        
        a = new logic_variable("a");
        universal_quantifier* u3 = new universal_quantifier(a, iff);
        
        Proposition::Current = new Proposition("De_Morgan_2", u3);
    }
    Proposition::addProposition(fout, Proposition::Current, "De Morgan's law");
    
    fout<<"\\begin{defn}"<<endl;
    fout<<"\\label{Definition:uniqueness_quantifier}"<<endl;
    fout<<"Uniqueness quantifier is denoted by $!\\exists$."<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& !\\exists x (P(x)) \\\\"<<endl;
    fout<<"\\overset{\\operatorname{def}}{\\iff} & (\\exists x (P(x))) \\land (\\forall x \\forall y ((P(x) \\land P(y)) \\implies (x = y)))"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{defn}"<<endl;
    fout<<endl;
    
    fout<<"\\begin{axm}"<<endl;
    fout<<"\\label{Axiom:axiom_of_substitution}"<<endl;
    fout<<"Axiom of Substitution"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"\\forall x ((\\exists y ((y = x) \\land P(y))) \\iff P(x))"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{axm}"<<endl;
    fout<<endl;
    
    //Logic proposition
    fout<<"\\section{Logic proposition}"<<endl;
    
    Proposition::Current = new Proposition("land_implies_iff", LOGIC, "\\forall a \\forall b ((a \\land b) \\implies (a \\iff b))");
    Proposition::addProposition(fout, Proposition::Current);
    
    Proposition::Current = new Proposition("land_omit", LOGIC, "\\forall a \\forall b ((a \\land b) \\implies a)");
    Proposition::addProposition(fout, Proposition::Current);
    
    Proposition::Current = new Proposition("lemma_uniqueness", LOGIC, "\\forall a \\forall b \\forall c ((a \\land ((b \\land a) \\implies c)) \\implies (b \\implies c))");
    Proposition::addProposition(fout, Proposition::Current);
    
    Proposition::Current = new Proposition("implies_satisfy", LOGIC, "\\forall a \\forall b ((a \\land (a \\implies b)) \\implies b)");
    Proposition::addProposition(fout, Proposition::Current);
    
    Proposition::Current = new Proposition("iff_satisfy", LOGIC, "\\forall a \\forall b ((a \\land (a \\iff b)) \\implies b)");
    Proposition::addProposition(fout, Proposition::Current);
    
    fout.close();
}
