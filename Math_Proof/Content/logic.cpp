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
    fout.open("logic.tex");
    
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
    Definition::addDefinition(fout, new Definition("lnot_True", LOGIC, "(\\lnot (\\text{True})) \\overset{\\operatorname{def}}{\\iff} (\\text{False})"));
    Definition::addDefinition(fout, new Definition("lnot_False", LOGIC, "(\\lnot (\\text{False})) \\overset{\\operatorname{def}}{\\iff} (\\text{True})"));
    
    //Definition of OR
    fout<<"\\subsection{Definition of $\\lor$}"<<endl;
    Definition::addDefinition(fout, new Definition("lor_True_True", LOGIC, "((\\text{True}) \\lor (\\text{True})) \\overset{\\operatorname{def}}{\\iff} (\\text{True})"));
    Definition::addDefinition(fout, new Definition("lor_True_False", LOGIC, "((\\text{True}) \\lor (\\text{False})) \\overset{\\operatorname{def}}{\\iff} (\\text{True})"));
    Definition::addDefinition(fout, new Definition("lor_False_True", LOGIC, "((\\text{False}) \\lor (\\text{True})) \\overset{\\operatorname{def}}{\\iff} (\\text{True})"));
    Definition::addDefinition(fout, new Definition("lor_False_False", LOGIC, "((\\text{False}) \\lor (\\text{False})) \\overset{\\operatorname{def}}{\\iff} (\\text{False})"));
    
    //Definition of AND
    fout<<"\\subsection{Definition of $\\land$}"<<endl;
    Definition::addDefinition(fout, new Definition("land_True_True", LOGIC, "((\\text{True}) \\land (\\text{True})) \\overset{\\operatorname{def}}{\\iff} (\\text{True})"));
    Definition::addDefinition(fout, new Definition("land_True_False", LOGIC, "((\\text{True}) \\land (\\text{False})) \\overset{\\operatorname{def}}{\\iff} (\\text{False})"));
    Definition::addDefinition(fout, new Definition("land_False_True", LOGIC, "((\\text{False}) \\land (\\text{True})) \\overset{\\operatorname{def}}{\\iff} (\\text{False})"));
    Definition::addDefinition(fout, new Definition("land_False_False", LOGIC, "((\\text{False}) \\land (\\text{False})) \\overset{\\operatorname{def}}{\\iff} (\\text{False})"));
    
    //Definition of iff
    fout<<"\\subsection{Definition of $\\iff$}"<<endl;
    Definition::addDefinition(fout, new Definition("iff", LOGIC, "\\forall x \\forall y ((x \\iff y) \\overset{\\operatorname{def}}{\\iff} ((x \\land y) \\lor ((\\lnot x) \\land (\\lnot y))))"));
    
    //Definition of implies
    fout<<"\\subsection{Definition of $\\implies$}"<<endl;
    Definition::addDefinition(fout, new Definition("implies", LOGIC, "\\forall x \\forall y ((x \\implies y) \\overset{\\operatorname{def}}{\\iff} ((\\lnot x) \\lor y))"));
    
    //Boolean algebra
    Proposition* x = nullptr;
    statement* law = nullptr;
    proof_block* block = nullptr;
    vector<substitution*> sub;
    string description;
    fout<<"\\section{Boolean algebra}"<<endl;
    //Associativity
    fout<<"\\subsection{Associativity of $\\lor$}"<<endl;
    Proposition::addProposition(fout, new Proposition("lor_associativity", LOGIC, "\\forall x \\forall y \\forall z (((x \\lor y) \\lor z) \\iff (x \\lor (y \\lor z)))"));
    
    fout<<"\\subsection{Associativity of $\\land$}"<<endl;
    Proposition::addProposition(fout, new Proposition("land_associativity", LOGIC, "\\forall x \\forall y \\forall z (((x \\land y) \\land z) \\iff (x \\land (y \\land z)))"));
    
    //Commutativity
    fout<<"\\subsection{Commutativity of $\\lor$}"<<endl;
    Proposition::addProposition(fout, new Proposition("lor_commutativity", LOGIC, "\\forall x \\forall y ((x \\lor y) \\iff (y \\lor x))"));
    
    fout<<"\\subsection{Commutativity of $\\land$}"<<endl;
    Proposition::addProposition(fout, new Proposition("land_commutativity", LOGIC, "\\forall x \\forall y ((x \\land y) \\iff (y \\land x))"));
    
    //Identity
    fout<<"\\subsection{Identity of $\\lor$}"<<endl;
    Proposition::addProposition(fout, new Proposition("lor_identity_1", LOGIC, "\\forall x ((x \\lor (\\text{False})) \\iff x)"));
    
    x = new Proposition("lor_identity_2", LOGIC, "\\forall x (((\\text{False}) \\lor x) \\iff x)");
    /*
    block = new proof_block("lor_identity_2", x, direct);
    sub.clear(); sub.push_back(new substitution("x", "x", LOGIC));
    block->append_binary_operator(input({}, "Proposition:lor_identity_1", LeftToRight, sub));
    block->append_binary_operator(input({1}, "Proposition:lor_commutativity", LeftToRight, true));
    x->append(block);
    */
    Proposition::addProposition(fout, x);
    
    fout<<"\\subsection{Identity of $\\land$}"<<endl;
    Proposition::addProposition(fout, new Proposition("land_identity_1", LOGIC, "\\forall x ((x \\land (\\text{True})) \\iff x)"));
    Proposition::addProposition(fout, new Proposition("land_identity_2", LOGIC, "\\forall x (((\\text{True}) \\land x) \\iff x)"));
    
    //Annihilator
    fout<<"\\subsection{Annihilator of $\\lor$}"<<endl;
    Proposition::addProposition(fout, new Proposition("lor_annihilator_1", LOGIC, "\\forall x ((x \\lor (\\text{True})) \\iff (\\text{True}))"));
    Proposition::addProposition(fout, new Proposition("lor_annihilator_2", LOGIC, "\\forall x (((\\text{True}) \\lor x) \\iff (\\text{True}))"));
    
    fout<<"\\subsection{Annihilator of $\\land$}"<<endl;
    Proposition::addProposition(fout, new Proposition("land_annihilator_1", LOGIC, "\\forall x ((x \\land (\\text{False})) \\iff (\\text{False}))"));
    Proposition::addProposition(fout, new Proposition("land_annihilator_2", LOGIC, "\\forall x (((\\text{False}) \\land x) \\iff (\\text{False}))"));
    
    //Idempotence
    fout<<"\\subsection{Idempotence of $\\lor$}"<<endl;
    Proposition::addProposition(fout, new Proposition("lor_idempotence", LOGIC, "\\forall x ((x \\lor x) \\iff x)"));
    
    fout<<"\\subsection{Idempotence of $\\land$}"<<endl;
    Proposition::addProposition(fout, new Proposition("land_idempotence", LOGIC, "\\forall x ((x \\land x) \\iff x)"));
    
    //Complement
    fout<<"\\subsection{Complement of $\\lor$}"<<endl;
    Proposition::addProposition(fout, new Proposition("lor_complement_1", LOGIC, "\\forall x ((x \\lor (\\lnot x)) \\iff (\\text{True}))"));
    Proposition::addProposition(fout, new Proposition("lor_complement_2", LOGIC, "\\forall x (((\\lnot x) \\lor x) \\iff (\\text{True}))"));
    
    fout<<"\\subsection{Complement of $\\land$}"<<endl;
    Proposition::addProposition(fout, new Proposition("land_complement_1", LOGIC, "\\forall x ((x \\land (\\lnot x)) \\iff (\\text{False}))"));
    Proposition::addProposition(fout, new Proposition("land_complement_2", LOGIC, "\\forall x (((\\lnot x) \\land x) \\iff (\\text{False}))"));
    
    //Absorption
    fout<<"\\subsection{Absorption of $\\lor$ over $\\land$}"<<endl;
    Proposition::addProposition(fout, new Proposition("lor_land_absorption_1", LOGIC, "\\forall x \\forall y ((x \\lor (x \\land y)) \\iff x)"));
    Proposition::addProposition(fout, new Proposition("lor_land_absorption_2", LOGIC, "\\forall x \\forall y ((x \\lor (y \\land x)) \\iff x)"));
    Proposition::addProposition(fout, new Proposition("lor_land_absorption_3", LOGIC, "\\forall x \\forall y (((x \\land y) \\lor x) \\iff x)"));
    Proposition::addProposition(fout, new Proposition("lor_land_absorption_4", LOGIC, "\\forall x \\forall y (((y \\land x) \\lor x) \\iff x)"));
    
    fout<<"\\subsection{Absorption of $\\land$ over $\\lor$}"<<endl;
    Proposition::addProposition(fout, new Proposition("land_lor_absorption_1", LOGIC, "\\forall x \\forall y ((x \\land (x \\lor y)) \\iff x)"));
    Proposition::addProposition(fout, new Proposition("land_lor_absorption_2", LOGIC, "\\forall x \\forall y ((x \\land (y \\lor x)) \\iff x)"));
    Proposition::addProposition(fout, new Proposition("land_lor_absorption_3", LOGIC, "\\forall x \\forall y (((x \\lor y) \\land x) \\iff x)"));
    Proposition::addProposition(fout, new Proposition("land_lor_absorption_4", LOGIC, "\\forall x \\forall y (((y \\lor x) \\land x) \\iff x)"));
    
    //Distributivity
    fout<<"\\subsection{Distributivity of $\\lor$ over $\\land$}"<<endl;
    Proposition::addProposition(fout, new Proposition("lor_land_distributivity_1", LOGIC, "\\forall x \\forall y \\forall z ((x \\lor (y \\land z)) \\iff ((x \\lor y) \\land (x \\lor z)))"));
    Proposition::addProposition(fout, new Proposition("lor_land_distributivity_2", LOGIC, "\\forall x \\forall y \\forall z (((x \\land y) \\lor z) \\iff ((x \\lor z) \\land (y \\lor z)))"));
    
    fout<<"\\subsection{Distributivity of $\\land$ over $\\lor$}"<<endl;
    Proposition::addProposition(fout, new Proposition("land_lor_distributivity_1", LOGIC, "\\forall x \\forall y \\forall z ((x \\land (y \\lor z)) \\iff ((x \\land y) \\lor (x \\land z)))"));
    Proposition::addProposition(fout, new Proposition("land_lor_distributivity_2", LOGIC, "\\forall x \\forall y \\forall z (((x \\lor y) \\land z) \\iff ((x \\land z) \\lor (y \\land z)))"));
    
    //Double negation
    fout<<"\\subsection{Double negation}"<<endl;
    Proposition::addProposition(fout, new Proposition("double_negation", LOGIC, "\\forall x ((\\lnot (\\lnot x)) \\iff x)"));
    
    //De Morgan's laws
    fout<<"\\subsection{De Morgan's laws}"<<endl;
    Proposition::addProposition(fout, new Proposition("De_Morgan_lor", LOGIC, "\\forall x \\forall y ((\\lnot (x \\lor y)) \\iff ((\\lnot x) \\land (\\lnot y)))"));
    Proposition::addProposition(fout, new Proposition("De_Morgan_land", LOGIC, "\\forall x \\forall y ((\\lnot (x \\land y)) \\iff ((\\lnot x) \\lor (\\lnot y)))"));
    
    //Basic Proposition
    fout<<"\\section{Basic Proposition}"<<endl;
    
    //x_lor_y_complement
    x = new Proposition("x_lor_y_complement", LOGIC, "\\forall x \\forall y (((x \\land (\\lnot y)) \\lor y) \\iff (x \\lor y))");
    block = new proof_block("x_lor_y_complement", x, deduction);
    block->append_binary_operator(input({}, "Proposition:lor_land_distributivity_2", LeftToRight));
    block->append_binary_operator(input({2}, "Proposition:lor_complement_2", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:land_identity_1", LeftToRight, true));
    x->append(block, true);
    Proposition::addProposition(fout, x);
    
    //Proof technique
    fout<<"\\section{Proof technique}"<<endl;
    
    //true statement
    x = new Proposition("true_statement", LOGIC, "\\forall x ((x \\iff (\\text{True})) \\iff x)");
    block = new proof_block("true_statement", x, deduction);
    block->append_binary_operator(input({}, "Definition:iff", LeftToRight));
    block->append_binary_operator(input({2,2}, "Definition:lnot_True", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:land_identity_1", LeftToRight));
    block->append_binary_operator(input({2}, "Proposition:land_annihilator_1", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:lor_identity_1", LeftToRight, true));
    x->append(block, true);
    Proposition::addProposition(fout, x);
    
    //implies_lor
    x = new Proposition("implies_lor", LOGIC, "\\forall x \\forall y \\forall z ((x \\implies y) \\implies ((x \\lor z) \\implies (y \\lor z)))");
    block = new proof_block("implies_lor", x, backward);
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
    block->append_binary_operator(input({1}, "Proposition:x_lor_y_complement", LeftToRight));
    block->append_binary_operator(input({2}, "Proposition:x_lor_y_complement", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:lor_associativity", RightToLeft));
    block->append_binary_operator(input({1}, "Proposition:lor_commutativity", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:lor_associativity", RightToLeft));
    block->append_binary_operator(input({1,1}, "Proposition:lor_complement_2", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:lor_annihilator_2", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:lor_annihilator_2", LeftToRight, true));
    x->append(block, true);
    Proposition::addProposition(fout, x);
    
    //Reflexive property of \\iff
    x = new Proposition("iff_reflexive", LOGIC, "\\forall x (x \\iff x)");
    description = "Reflexive property of $\\iff$.";
    block = new proof_block("iff_reflexive", x, backward);
    block->append_binary_operator(input({}, "Definition:iff", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:land_idempotence", LeftToRight));
    block->append_binary_operator(input({2}, "Proposition:land_idempotence", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:lor_complement_1", LeftToRight, true));
    x->append(block, true);
    Proposition::addProposition(fout, x, description);
    
    fout.close();
}
