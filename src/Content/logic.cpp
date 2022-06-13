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
    ofstream& fout = statement::fout;
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
    Definition::Current = new Definition("lnot_True", LOGIC, "(\\lnot (\\text{True})) \\iff (\\text{False})");
    Definition::addDefinition();

    Definition::Current = new Definition("lnot_False", LOGIC, "(\\lnot (\\text{False})) \\iff (\\text{True})");
    Definition::addDefinition();

    //Definition of OR
    fout<<"\\subsection{Definition of $\\lor$}"<<endl;
    Definition::Current = new Definition("lor_True_True", LOGIC, "((\\text{True}) \\lor (\\text{True})) \\iff (\\text{True})");
    Definition::addDefinition();

    Definition::Current = new Definition("lor_True_False", LOGIC, "((\\text{True}) \\lor (\\text{False})) \\iff (\\text{True})");
    Definition::addDefinition();

    Definition::Current = new Definition("lor_False_True", LOGIC, "((\\text{False}) \\lor (\\text{True})) \\iff (\\text{True})");
    Definition::addDefinition();

    Definition::Current = new Definition("lor_False_False", LOGIC, "((\\text{False}) \\lor (\\text{False})) \\iff (\\text{False})");
    Definition::addDefinition();

    //Definition of AND
    fout<<"\\subsection{Definition of $\\land$}"<<endl;
    Definition::Current = new Definition("land_True_True", LOGIC, "((\\text{True}) \\land (\\text{True})) \\iff (\\text{True})");
    Definition::addDefinition();

    Definition::Current = new Definition("land_True_False", LOGIC, "((\\text{True}) \\land (\\text{False})) \\iff (\\text{False})");
    Definition::addDefinition();

    Definition::Current = new Definition("land_False_True", LOGIC, "((\\text{False}) \\land (\\text{True})) \\iff (\\text{False})");
    Definition::addDefinition();

    Definition::Current = new Definition("land_False_False", LOGIC, "((\\text{False}) \\land (\\text{False})) \\iff (\\text{False})");
    Definition::addDefinition();

    //Definition of iff
    fout<<"\\subsection{Definition of $\\iff$}"<<endl;
    Definition::Current = new Definition("iff", LOGIC, "\\forall a \\forall b ((a \\iff b) \\iff ((a \\land b) \\lor ((\\lnot a) \\land (\\lnot b))))");
    Definition::addDefinition();

    //Definition of implies
    fout<<"\\subsection{Definition of $\\implies$}"<<endl;
    Definition::Current = new Definition("implies", LOGIC, "\\forall a \\forall b ((a \\implies b) \\iff ((\\lnot a) \\lor b))");
    Definition::addDefinition();

    //Boolean algebra
    proof_block* block = nullptr;
    vector<substitution*> sub;
    string description;
    fout<<"\\section{Boolean algebra}"<<endl;
    //Double negation
    fout<<"\\subsection{Double negation}"<<endl;
    Proposition::Current = new Proposition("double_negation", LOGIC, "\\forall a ((\\lnot (\\lnot a)) \\iff a)");
    Proposition::addProposition();

    //De Morgan's laws
    fout<<"\\subsection{De Morgan's laws}"<<endl;
    Proposition::Current = new Proposition("De_Morgan_lor", LOGIC, "\\forall a \\forall b ((\\lnot (a \\lor b)) \\iff ((\\lnot a) \\land (\\lnot b)))");
    Proposition::addProposition();

    Proposition::Current = new Proposition("De_Morgan_land", LOGIC, "\\forall a \\forall b ((\\lnot (a \\land b)) \\iff ((\\lnot a) \\lor (\\lnot b)))");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({1,1}, "Proposition:double_negation", RightToLeft));
    block->append(input({1,2}, "Proposition:double_negation", RightToLeft));
    block->append(input({1}, "Proposition:De_Morgan_lor", RightToLeft));
    block->append(input({}, "Proposition:double_negation", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    //Associativity
    fout<<"\\subsection{Associativity of $\\lor$}"<<endl;
    Proposition::Current = new Proposition("lor_associativity", LOGIC, "\\forall a \\forall b \\forall c (((a \\lor b) \\lor c) \\iff (a \\lor (b \\lor c)))");
    Proposition::addProposition();

    fout<<"\\subsection{Associativity of $\\land$}"<<endl;
    Proposition::Current = new Proposition("land_associativity", LOGIC, "\\forall a \\forall b \\forall c (((a \\land b) \\land c) \\iff (a \\land (b \\land c)))");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({1,1}, "Proposition:double_negation", RightToLeft));
    block->append(input({1,2}, "Proposition:double_negation", RightToLeft));
    block->append(input({1}, "Proposition:De_Morgan_lor", RightToLeft));
    block->append(input({2}, "Proposition:double_negation", RightToLeft));
    block->append(input({}, "Proposition:De_Morgan_lor", RightToLeft));
    block->append(input({1}, "Proposition:lor_associativity", LeftToRight));
    block->append(input({}, "Proposition:De_Morgan_lor", LeftToRight));
    block->append(input({1}, "Proposition:double_negation", LeftToRight));
    block->append(input({2}, "Proposition:De_Morgan_lor", LeftToRight));
    block->append(input({2,1}, "Proposition:double_negation", LeftToRight));
    block->append(input({2,2}, "Proposition:double_negation", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    //Commutativity
    fout<<"\\subsection{Commutativity of $\\lor$}"<<endl;
    Proposition::Current = new Proposition("lor_commutativity", LOGIC, "\\forall a \\forall b ((a \\lor b) \\iff (b \\lor a))");
    Proposition::addProposition();

    fout<<"\\subsection{Commutativity of $\\land$}"<<endl;
    Proposition::Current = new Proposition("land_commutativity", LOGIC, "\\forall a \\forall b ((a \\land b) \\iff (b \\land a))");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({1}, "Proposition:double_negation", RightToLeft));
    block->append(input({2}, "Proposition:double_negation", RightToLeft));
    block->append(input({}, "Proposition:De_Morgan_lor", RightToLeft));
    block->append(input({1}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({}, "Proposition:De_Morgan_lor", LeftToRight));
    block->append(input({1}, "Proposition:double_negation", LeftToRight));
    block->append(input({2}, "Proposition:double_negation", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    //Identity
    fout<<"\\subsection{Identity of $\\lor$}"<<endl;
    Proposition::Current = new Proposition("lor_identity_1", LOGIC, "\\forall a ((a \\lor (\\text{False})) \\iff a)");
    Proposition::addProposition();

    Proposition::Current = new Proposition("lor_identity_2", LOGIC, "\\forall a (((\\text{False}) \\lor a) \\iff a)");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({}, "Proposition:lor_identity_1", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    fout<<"\\subsection{Identity of $\\land$}"<<endl;
    Proposition::Current = new Proposition("land_identity_1", LOGIC, "\\forall a ((a \\land (\\text{True})) \\iff a)");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({1}, "Proposition:double_negation", RightToLeft));
    block->append(input({2}, "Definition:lnot_False", RightToLeft));
    block->append(input({}, "Proposition:De_Morgan_lor", RightToLeft));
    block->append(input({1}, "Proposition:lor_identity_1", LeftToRight));
    block->append(input({}, "Proposition:double_negation", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    Proposition::Current = new Proposition("land_identity_2", LOGIC, "\\forall a (((\\text{True}) \\land a) \\iff a)");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({}, "Proposition:land_identity_1", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    //Annihilator
    fout<<"\\subsection{Annihilator of $\\lor$}"<<endl;
    Proposition::Current = new Proposition("lor_annihilator_1", LOGIC, "\\forall a ((a \\lor (\\text{True})) \\iff (\\text{True}))");
    Proposition::addProposition();

    Proposition::Current = new Proposition("lor_annihilator_2", LOGIC, "\\forall a (((\\text{True}) \\lor a) \\iff (\\text{True}))");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({}, "Proposition:lor_annihilator_1", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    fout<<"\\subsection{Annihilator of $\\land$}"<<endl;
    Proposition::Current = new Proposition("land_annihilator_1", LOGIC, "\\forall a ((a \\land (\\text{False})) \\iff (\\text{False}))");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({1}, "Proposition:double_negation", RightToLeft));
    block->append(input({2}, "Definition:lnot_True", RightToLeft));
    block->append(input({}, "Proposition:De_Morgan_lor", RightToLeft));
    block->append(input({1}, "Proposition:lor_annihilator_1", LeftToRight));
    block->append(input({}, "Definition:lnot_True", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    Proposition::Current = new Proposition("land_annihilator_2", LOGIC, "\\forall a (((\\text{False}) \\land a) \\iff (\\text{False}))");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({}, "Proposition:land_annihilator_1", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    //Idempotence
    fout<<"\\subsection{Idempotence of $\\lor$}"<<endl;
    Proposition::Current = new Proposition("lor_idempotence", LOGIC, "\\forall a ((a \\lor a) \\iff a)");
    Proposition::addProposition();

    fout<<"\\subsection{Idempotence of $\\land$}"<<endl;
    Proposition::Current = new Proposition("land_idempotence", LOGIC, "\\forall a ((a \\land a) \\iff a)");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({1}, "Proposition:double_negation", RightToLeft));
    block->append(input({2}, "Proposition:double_negation", RightToLeft));
    block->append(input({}, "Proposition:De_Morgan_lor", RightToLeft));
    block->append(input({1}, "Proposition:lor_idempotence", LeftToRight));
    block->append(input({}, "Proposition:double_negation", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    //Complement
    fout<<"\\subsection{Complement of $\\lor$}"<<endl;
    Proposition::Current = new Proposition("lor_complement_1", LOGIC, "\\forall a ((a \\lor (\\lnot a)) \\iff (\\text{True}))");
    Proposition::addProposition();

    Proposition::Current = new Proposition("lor_complement_2", LOGIC, "\\forall a (((\\lnot a) \\lor a) \\iff (\\text{True}))");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({}, "Proposition:lor_complement_1", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    fout<<"\\subsection{Complement of $\\land$}"<<endl;
    Proposition::Current = new Proposition("land_complement_1", LOGIC, "\\forall a ((a \\land (\\lnot a)) \\iff (\\text{False}))");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({1}, "Proposition:double_negation", RightToLeft));
    block->append(input({}, "Proposition:De_Morgan_lor", RightToLeft));
    block->append(input({1}, "Proposition:lor_complement_2", LeftToRight));
    block->append(input({}, "Definition:lnot_True", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    Proposition::Current = new Proposition("land_complement_2", LOGIC, "\\forall a (((\\lnot a) \\land a) \\iff (\\text{False}))");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({}, "Proposition:land_complement_1", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    //Distributivity
    fout<<"\\subsection{Distributivity of $\\lor$ over $\\land$}"<<endl;
    Proposition::Current = new Proposition("lor_land_distributivity_1", LOGIC, "\\forall a \\forall b \\forall c ((a \\lor (b \\land c)) \\iff ((a \\lor b) \\land (a \\lor c)))");
    Proposition::addProposition();

    Proposition::Current = new Proposition("lor_land_distributivity_2", LOGIC, "\\forall a \\forall b \\forall c (((a \\land b) \\lor c) \\iff ((a \\lor c) \\land (b \\lor c)))");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({}, "Proposition:lor_land_distributivity_1", LeftToRight));
    block->append(input({1}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({2}, "Proposition:lor_commutativity", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    fout<<"\\subsection{Distributivity of $\\land$ over $\\lor$}"<<endl;
    Proposition::Current = new Proposition("land_lor_distributivity_1", LOGIC, "\\forall a \\forall b \\forall c ((a \\land (b \\lor c)) \\iff ((a \\land b) \\lor (a \\land c)))");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({2,1}, "Proposition:double_negation", RightToLeft));
    block->append(input({2,2}, "Proposition:double_negation", RightToLeft));
    block->append(input({2}, "Proposition:De_Morgan_land", RightToLeft));
    block->append(input({1}, "Proposition:double_negation", RightToLeft));
    block->append(input({}, "Proposition:De_Morgan_lor", RightToLeft));
    block->append(input({1}, "Proposition:lor_land_distributivity_1", LeftToRight));
    block->append(input({}, "Proposition:De_Morgan_land", LeftToRight));
    block->append(input({1}, "Proposition:De_Morgan_lor", LeftToRight));
    block->append(input({1,1}, "Proposition:double_negation", LeftToRight));
    block->append(input({1,2}, "Proposition:double_negation", LeftToRight));
    block->append(input({2}, "Proposition:De_Morgan_lor", LeftToRight));
    block->append(input({2,1}, "Proposition:double_negation", LeftToRight));
    block->append(input({2,2}, "Proposition:double_negation", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    Proposition::Current = new Proposition("land_lor_distributivity_2", LOGIC, "\\forall a \\forall b \\forall c (((a \\lor b) \\land c) \\iff ((a \\land c) \\lor (b \\land c)))");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({}, "Proposition:land_lor_distributivity_1", LeftToRight));
    block->append(input({1}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({2}, "Proposition:land_commutativity", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    //Absorption
    fout<<"\\subsection{Absorption of $\\lor$ over $\\land$}"<<endl;
    Proposition::Current = new Proposition("lor_land_absorption", LOGIC, "\\forall a \\forall b ((a \\lor (a \\land b)) \\iff a)");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({1}, "Proposition:land_identity_1", RightToLeft));
    sub.clear(); sub.push_back(new substitution("a", "b", LOGIC));
    block->append(input({1,2}, "Proposition:lor_complement_1", RightToLeft, sub));
    block->append(input({1}, "Proposition:land_lor_distributivity_1", LeftToRight));
    block->append(input({}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({}, "Proposition:lor_associativity", RightToLeft));
    block->append(input({1}, "Proposition:lor_idempotence", LeftToRight));
    block->append(input({}, "Proposition:land_lor_distributivity_1", RightToLeft));
    block->append(input({2}, "Proposition:lor_complement_1", LeftToRight));
    block->append(input({}, "Proposition:land_identity_1", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    fout<<"\\subsection{Absorption of $\\land$ over $\\lor$}"<<endl;
    Proposition::Current = new Proposition("land_lor_absorption", LOGIC, "\\forall a \\forall b ((a \\land (a \\lor b)) \\iff a)");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Proposition:land_lor_distributivity_1", LeftToRight));
    block->append(input({1}, "Proposition:land_idempotence", LeftToRight));
    block->append(input({}, "Proposition:lor_land_absorption", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    //Basic Proposition
    fout<<"\\section{Basic Proposition}"<<endl;

    //a_lor_b_complement
    fout<<"\\subsection{Complement of a $\\lor$ b}"<<endl;
    Proposition::Current = new Proposition("a_lor_b_complement_1", LOGIC, "\\forall a \\forall b (((a \\land (\\lnot b)) \\lor b) \\iff (a \\lor b))");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Proposition:lor_land_distributivity_2", LeftToRight));
    block->append(input({2}, "Proposition:lor_complement_2", LeftToRight));
    block->append(input({}, "Proposition:land_identity_1", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    Proposition::Current = new Proposition("a_lor_b_complement_2", LOGIC, "\\forall a \\forall b (((a \\land b) \\lor (\\lnot b)) \\iff (a \\lor (\\lnot b)))");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Proposition:lor_land_distributivity_2", LeftToRight));
    block->append(input({2}, "Proposition:lor_complement_1", LeftToRight));
    block->append(input({}, "Proposition:land_identity_1", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    //Multiple condition
    fout<<"\\subsection{Multiple condition}"<<endl;
    Proposition::Current = new Proposition("multiple_condition", LOGIC, "\\forall a \\forall b \\forall c ((a \\implies (b \\implies c)) \\iff ((a \\land b) \\implies c))");
    description = "Multiple condition.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({2}, "Definition:implies", LeftToRight));
    block->append(input({}, "Definition:implies", LeftToRight));
    block->append(input({}, "Proposition:lor_associativity", RightToLeft));
    block->append(input({1}, "Proposition:De_Morgan_land", RightToLeft));
    block->append(input({}, "Definition:implies", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    //Condition satisfied
    fout<<"\\subsection{Condition satisfied}"<<endl;
    Proposition::Current = new Proposition("a_implies_a_lor_b", LOGIC, "\\forall a \\forall b (a \\implies (a \\lor b))");
    block = new proof_block(backward);
    block->append(input({}, "Definition:implies", LeftToRight));
    block->append(input({}, "Proposition:lor_associativity", RightToLeft));
    block->append(input({1}, "Proposition:lor_complement_2", LeftToRight));
    block->append(input({}, "Proposition:lor_annihilator_2", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    Proposition::Current = new Proposition("a_land_b_implies_a", LOGIC, "\\forall a \\forall b ((a \\land b) \\implies a)");
    block = new proof_block(backward);
    block->append(input({}, "Definition:implies", LeftToRight));
    block->append(input({1}, "Proposition:De_Morgan_land", LeftToRight));
    block->append(input({}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({}, "Proposition:lor_associativity", RightToLeft));
    block->append(input({1}, "Proposition:lor_complement_1", LeftToRight));
    block->append(input({}, "Proposition:lor_annihilator_2", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    Proposition::Current = new Proposition("implies_satisfied", LOGIC, "\\forall a \\forall b ((a \\land (a \\implies b)) \\implies b)");
    description = "Condition satisfied for $\\implies$.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({2}, "Definition:implies", LeftToRight));
    block->append(input({}, "Proposition:land_lor_distributivity_1", LeftToRight));
    block->append(input({1}, "Proposition:land_complement_1", LeftToRight));
    block->append(input({}, "Proposition:lor_identity_2", LeftToRight));
    block->append(input({}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({}, "Proposition:a_land_b_implies_a", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    fout<<"\\subsection{Associativity and Commutativity}"<<endl;
    Proposition::Current = new Proposition("lor_commutativity_2_2", LOGIC, "\\forall a \\forall b \\forall c \\forall d (((a \\lor b) \\lor (c \\lor d)) \\iff ((a \\lor c) \\lor (b \\lor d)))");
    description = "Commutativity of $\\lor$.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Proposition:lor_associativity", RightToLeft));
    block->append(input({1}, "Proposition:lor_associativity", LeftToRight));
    block->append(input({1,2}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({1}, "Proposition:lor_associativity", RightToLeft));
    block->append(input({}, "Proposition:lor_associativity", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    Proposition::Current = new Proposition("land_commutativity_2_2", LOGIC, "\\forall a \\forall b \\forall c \\forall d (((a \\land b) \\land (c \\land d)) \\iff ((a \\land c) \\land (b \\land d)))");
    description = "Commutativity of $\\land$.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Proposition:land_associativity", RightToLeft));
    block->append(input({1}, "Proposition:land_associativity", LeftToRight));
    block->append(input({1,2}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({1}, "Proposition:land_associativity", RightToLeft));
    block->append(input({}, "Proposition:land_associativity", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    //Proof technique
    fout<<"\\section{Proof technique}"<<endl;

    //true statement
    Proposition::Current = new Proposition("true_statement", LOGIC, "\\forall a ((a \\iff (\\text{True})) \\iff a)");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Definition:iff", LeftToRight));
    block->append(input({2,2}, "Definition:lnot_True", LeftToRight));
    block->append(input({1}, "Proposition:land_identity_1", LeftToRight));
    block->append(input({2}, "Proposition:land_annihilator_1", LeftToRight));
    block->append(input({}, "Proposition:lor_identity_1", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    //Transitive property of implies
    fout<<"\\subsection{Transitive property of $\\implies$}"<<endl;
    Proposition::Current = new Proposition("implies_transitive", LOGIC, "\\forall a \\forall b \\forall c (((a \\implies b) \\land (b \\implies c)) \\implies (a \\implies c))");
    description = "Transitive property of $\\implies$.";
    block = new proof_block(backward);
    block->append(input({1,1}, "Definition:implies", LeftToRight));
    block->append(input({1,2}, "Definition:implies", LeftToRight));
    block->append(input({2}, "Definition:implies", LeftToRight));
    block->append(input({}, "Definition:implies", LeftToRight));
    block->append(input({1}, "Proposition:De_Morgan_land", LeftToRight));
    block->append(input({1,1}, "Proposition:De_Morgan_lor", LeftToRight));
    block->append(input({1,1,1}, "Proposition:double_negation", LeftToRight));
    block->append(input({1,2}, "Proposition:De_Morgan_lor", LeftToRight));
    block->append(input({1,2,1}, "Proposition:double_negation", LeftToRight));
    block->append(input({}, "Proposition:lor_commutativity_2_2", LeftToRight));
    block->append(input({1,1}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({1}, "Proposition:a_lor_b_complement_2", LeftToRight));
    block->append(input({2}, "Proposition:a_lor_b_complement_1", LeftToRight));
    block->append(input({}, "Proposition:lor_commutativity_2_2", LeftToRight));
    block->append(input({1}, "Proposition:lor_complement_2", LeftToRight));
    block->append(input({}, "Proposition:lor_annihilator_2", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    fout<<"\\subsection{Axiom of Substitution for $\\implies$}"<<endl;
    Proposition::Current = new Proposition("implies_substitution_lor", LOGIC, "\\forall a \\forall b \\forall c ((a \\implies b) \\implies ((a \\lor c) \\implies (b \\lor c)))");
    description = "Substitution of $\\implies$ for $\\lor$.";
    block = new proof_block(backward);
    block->append(input({1}, "Definition:implies", LeftToRight));
    block->append(input({2}, "Definition:implies", LeftToRight));
    block->append(input({}, "Definition:implies", LeftToRight));
    block->append(input({1}, "Proposition:De_Morgan_lor", LeftToRight));
    block->append(input({1,1}, "Proposition:double_negation", LeftToRight));
    block->append(input({2,1}, "Proposition:De_Morgan_lor", LeftToRight));
    block->append(input({2}, "Proposition:lor_associativity", RightToLeft));
    block->append(input({2,1}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({2}, "Proposition:lor_associativity", LeftToRight));
    block->append(input({}, "Proposition:lor_associativity", RightToLeft));
    block->append(input({1}, "Proposition:a_lor_b_complement_1", LeftToRight));
    block->append(input({2}, "Proposition:a_lor_b_complement_1", LeftToRight));
    block->append(input({}, "Proposition:lor_commutativity_2_2", LeftToRight));
    block->append(input({1}, "Proposition:lor_complement_1", LeftToRight));
    block->append(input({}, "Proposition:lor_annihilator_2", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    Proposition::Current = new Proposition("implies_substitution_land", LOGIC, "\\forall a \\forall b \\forall c ((a \\implies b) \\implies ((a \\land c) \\implies (b \\land c)))");
    description = "Substitution of $\\implies$ for $\\land$.";
    block = new proof_block(backward);
    block->append(input({1}, "Definition:implies", LeftToRight));
    block->append(input({2}, "Definition:implies", LeftToRight));
    block->append(input({}, "Definition:implies", LeftToRight));
    block->append(input({1}, "Proposition:De_Morgan_lor", LeftToRight));
    block->append(input({1,1}, "Proposition:double_negation", LeftToRight));
    block->append(input({2,1}, "Proposition:De_Morgan_land", LeftToRight));
    block->append(input({2}, "Proposition:lor_associativity", LeftToRight));
    block->append(input({}, "Proposition:lor_associativity", RightToLeft));
    block->append(input({1,1}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({2}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({1}, "Proposition:a_lor_b_complement_2", LeftToRight));
    block->append(input({2}, "Proposition:a_lor_b_complement_2", LeftToRight));
    block->append(input({}, "Proposition:lor_commutativity_2_2", LeftToRight));
    block->append(input({1}, "Proposition:lor_complement_2", LeftToRight));
    block->append(input({}, "Proposition:lor_annihilator_2", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    Proposition::Current = new Proposition("implies_substitution_implies", LOGIC, "\\forall a \\forall b \\forall c ((a \\implies b) \\implies ((c \\implies a) \\implies (c \\implies b)))");
    description = "Substitution of $\\implies$ for $\\implies$.";
    block = new proof_block(direct);
    sub.clear();
    sub.push_back(new substitution("a", "c", LOGIC));
    sub.push_back(new substitution("b", "a", LOGIC));
    sub.push_back(new substitution("c", "b", LOGIC));
    block->append(input({}, "Proposition:implies_transitive", TrueToP, sub));
    block->append(input({1}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({}, "Proposition:multiple_condition", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    //Contrapositive
    fout<<"\\subsection{Contrapositive}"<<endl;
    Proposition::Current = new Proposition("contrapositive", LOGIC, "\\forall a \\forall b ((a \\implies b) \\iff ((\\lnot b) \\implies (\\lnot a)))");
    description = "Contrapositive.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Definition:implies", LeftToRight));
    block->append(input({}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({1}, "Proposition:double_negation", RightToLeft));
    block->append(input({}, "Definition:implies", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    fout<<"\\subsection{Properties of $\\iff$}"<<endl;
    //iff and implies
    Proposition::Current = new Proposition("iff_implies", LOGIC, "\\forall a \\forall b ((a \\iff b) \\iff ((a \\implies b) \\land (b \\implies a)))");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Definition:iff", LeftToRight));
    block->append(input({}, "Proposition:lor_land_distributivity_2", LeftToRight));
    block->append(input({1}, "Proposition:lor_land_distributivity_1", LeftToRight));
    block->append(input({1,1}, "Proposition:lor_complement_1", LeftToRight));
    block->append(input({1}, "Proposition:land_identity_2", LeftToRight));
    block->append(input({2}, "Proposition:lor_land_distributivity_1", LeftToRight));
    block->append(input({2,2}, "Proposition:lor_complement_1", LeftToRight));
    block->append(input({2}, "Proposition:land_identity_1", LeftToRight));
    block->append(input({1}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({2}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({1}, "Definition:implies", RightToLeft));
    block->append(input({2}, "Definition:implies", RightToLeft));
    block->append(input({}, "Proposition:land_commutativity", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    Proposition::Current = new Proposition("iff_symmetric", LOGIC, "\\forall a \\forall b ((a \\iff b) \\iff (b \\iff a))");
    description = "Symmetric property of $\\iff$.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Definition:iff", LeftToRight));
    block->append(input({1}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({2}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({}, "Definition:iff", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    Proposition::Current = new Proposition("iff_transitive", LOGIC, "\\forall a \\forall b \\forall c (((a \\iff b) \\land (b \\iff c)) \\implies (a \\iff c))");
    description = "Transitive property of $\\iff$.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({1}, "Proposition:iff_implies", LeftToRight));
    block->append(input({2}, "Proposition:iff_implies", LeftToRight));
    block->append(input({}, "Proposition:land_commutativity_2_2", LeftToRight));
    block->append(input({2}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({1}, "Proposition:implies_transitive", LeftToRight));
    block->append(input({2}, "Proposition:implies_transitive", LeftToRight));
    block->append(input({}, "Proposition:iff_implies", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    Proposition::Current = new Proposition("iff_satisfied", LOGIC, "\\forall a \\forall b ((a \\land (a \\iff b)) \\implies b)");
    description = "Condition satisfied for $\\iff$.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({2}, "Proposition:iff_implies", LeftToRight));
    block->append(input({}, "Proposition:land_associativity", RightToLeft));
    block->append(input({}, "Proposition:a_land_b_implies_a", LeftToRight));
    block->append(input({}, "Proposition:implies_satisfied", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    fout<<"\\subsection{Axiom of Substitution for $\\iff$}"<<endl;
    Proposition::Current = new Proposition("iff_substitution_lor", LOGIC, "\\forall a \\forall b \\forall c ((a \\iff b) \\implies ((a \\lor c) \\iff (b \\lor c)))");
    description = "Substitution of $\\iff$ for $\\lor$.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Proposition:iff_implies", LeftToRight));
    sub.clear();
    sub.push_back(new substitution("a", "a", LOGIC));
    sub.push_back(new substitution("b", "b", LOGIC));
    sub.push_back(new substitution("c", "c", LOGIC));
    block->append(input({1}, "Proposition:implies_substitution_lor", LeftToRight, sub));
    sub.clear();
    sub.push_back(new substitution("a", "b", LOGIC));
    sub.push_back(new substitution("b", "a", LOGIC));
    sub.push_back(new substitution("c", "c", LOGIC));
    block->append(input({2}, "Proposition:implies_substitution_lor", LeftToRight, sub));
    block->append(input({}, "Proposition:iff_implies", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    Proposition::Current = new Proposition("iff_substitution_land", LOGIC, "\\forall a \\forall b \\forall c ((a \\iff b) \\implies ((a \\land c) \\iff (b \\land c)))");
    description = "Substitution of $\\iff$ for $\\land$.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Proposition:iff_implies", LeftToRight));
    sub.clear();
    sub.push_back(new substitution("a", "a", LOGIC));
    sub.push_back(new substitution("b", "b", LOGIC));
    sub.push_back(new substitution("c", "c", LOGIC));
    block->append(input({1}, "Proposition:implies_substitution_land", LeftToRight, sub));
    sub.clear();
    sub.push_back(new substitution("a", "b", LOGIC));
    sub.push_back(new substitution("b", "a", LOGIC));
    sub.push_back(new substitution("c", "c", LOGIC));
    block->append(input({2}, "Proposition:implies_substitution_land", LeftToRight, sub));
    block->append(input({}, "Proposition:iff_implies", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    Proposition::Current = new Proposition("iff_substitution_lnot", LOGIC, "\\forall a \\forall b ((a \\iff b) \\iff ((\\lnot a) \\iff (\\lnot b)))");
    description = "Substitution of $\\iff$ for $\\lnot$.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Definition:iff", LeftToRight));
    block->append(input({1,1}, "Proposition:double_negation", RightToLeft));
    block->append(input({1,2}, "Proposition:double_negation", RightToLeft));
    block->append(input({}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({}, "Definition:iff", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    Proposition::Current = new Proposition("iff_substitution_implies_1", LOGIC, "\\forall a \\forall b \\forall c ((a \\iff b) \\implies ((a \\implies c) \\iff (b \\implies c)))");
    description = "Substitution of $\\iff$ for $\\implies$.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Proposition:iff_substitution_lnot", LeftToRight));
    sub.clear();
    sub.push_back(new substitution("a", "\\lnot a", LOGIC));
    sub.push_back(new substitution("b", "\\lnot b", LOGIC));
    sub.push_back(new substitution("c", "c", LOGIC));
    block->append(input({}, "Proposition:iff_substitution_lor", LeftToRight, sub));
    block->append(input({1}, "Definition:implies", RightToLeft));
    block->append(input({2}, "Definition:implies", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    Proposition::Current = new Proposition("iff_substitution_implies_2", LOGIC, "\\forall a \\forall b \\forall c ((a \\iff b) \\implies ((c \\implies a) \\iff (c \\implies b)))");
    description = "Substitution of $\\iff$ for $\\implies$.";
    block = new proof_block(deduction_LeftToRight);
    sub.clear();
    sub.push_back(new substitution("a", "a", LOGIC));
    sub.push_back(new substitution("b", "b", LOGIC));
    sub.push_back(new substitution("c", "\\lnot c", LOGIC));
    block->append(input({}, "Proposition:iff_substitution_lor", LeftToRight, sub));
    block->append(input({1}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({2}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({1}, "Definition:implies", RightToLeft));
    block->append(input({2}, "Definition:implies", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    Proposition::Current = new Proposition("iff_substitution_iff", LOGIC, "\\forall a \\forall b \\forall c ((a \\iff b) \\iff ((a \\iff c) \\iff (b \\iff c)))");
    description = "Substitution of $\\iff$ for $\\iff$.";

    block = new proof_block("1", Proposition("", LOGIC, "\\forall a \\forall b \\forall c (((a \\land c) \\land (b \\land c)) \\iff ((a \\land b) \\land c))"), deduction_LeftToRight);
    block->append(input({}, "Proposition:land_commutativity_2_2", LeftToRight));
    block->append(input({2}, "Proposition:land_idempotence", LeftToRight));
    Proposition::Current->append(block);

    block = new proof_block("2", Proposition("", LOGIC, "\\forall a \\forall b \\forall c (((a \\land c) \\land (b \\land (\\lnot c))) \\iff (\\text{False}))"), deduction_LeftToRight);
    block->append(input({}, "Proposition:land_commutativity_2_2", LeftToRight));
    block->append(input({2}, "Proposition:land_complement_1", LeftToRight));
    block->append(input({}, "Proposition:land_annihilator_1", LeftToRight));
    Proposition::Current->append(block);

    block = new proof_block("3", Proposition("", LOGIC, "\\forall a \\forall b ((\\lnot (a \\iff b)) \\iff (a \\iff (\\lnot b)))"), deduction_LeftToRight);
    block->append(input({1}, "Definition:iff", LeftToRight));
    block->append(input({}, "Proposition:De_Morgan_lor", LeftToRight));
    block->append(input({1}, "Proposition:De_Morgan_land", LeftToRight));
    block->append(input({2}, "Proposition:De_Morgan_land", LeftToRight));
    block->append(input({2,1}, "Proposition:double_negation", LeftToRight));
    block->append(input({2,2}, "Proposition:double_negation", LeftToRight));
    block->append(input({}, "Proposition:land_lor_distributivity_2", LeftToRight));
    block->append(input({1}, "Proposition:land_lor_distributivity_1", LeftToRight));
    block->append(input({2}, "Proposition:land_lor_distributivity_1", LeftToRight));
    block->append(input({1,1}, "Proposition:land_complement_2", LeftToRight));
    block->append(input({2,2}, "Proposition:land_complement_2", LeftToRight));
    block->append(input({1}, "Proposition:lor_identity_2", LeftToRight));
    block->append(input({2}, "Proposition:lor_identity_1", LeftToRight));
    block->append(input({2}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({2,2}, "Proposition:double_negation", RightToLeft));
    block->append(input({}, "Definition:iff", RightToLeft));
    Proposition::Current->append(block);

    block = new proof_block("4", Proposition("", LOGIC, "\\forall a \\forall b \\forall c (((a \\iff c) \\land (b \\iff c)) \\iff (((a \\land b) \\land c) \\lor (((\\lnot a) \\land (\\lnot b)) \\land (\\lnot c))))"), deduction_LeftToRight);
    block->append(input({1}, "Definition:iff", LeftToRight));
    block->append(input({2}, "Definition:iff", LeftToRight));
    block->append(input({}, "Proposition:land_lor_distributivity_2", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({1}, "Proposition:land_lor_distributivity_1", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({2}, "Proposition:land_lor_distributivity_1", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({1,1}, "Local:1", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({1,2}, "Local:2", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({2,1,2,2}, "Proposition:double_negation", RightToLeft));
    block->set_split_point({{2}});
    block->append(input({2,1}, "Local:2", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({2,2}, "Local:1", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({1}, "Proposition:lor_identity_1", LeftToRight));
    block->append(input({2}, "Proposition:lor_identity_2", LeftToRight));
    Proposition::Current->append(block);

    block = new proof_block("5", Proposition("", LOGIC, "\\forall a \\forall b \\forall c (((a \\iff c) \\land (b \\iff c)) \\iff ((a \\iff b) \\land (a \\iff c)))"), deduction_LeftToRight);
    block->append(input({}, "Local:4", LeftToRight));
    block->append(input({1}, "Proposition:land_associativity", LeftToRight));
    block->append(input({2}, "Proposition:land_associativity", LeftToRight));
    block->append(input({1}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({2}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({}, "Local:4", RightToLeft));
    block->append(input({1}, "Proposition:iff_symmetric", LeftToRight));
    block->append(input({2}, "Proposition:iff_symmetric", LeftToRight));
    Proposition::Current->append(block);

    block = new proof_block(deduction_RightToLeft);
    block->append(input({}, "Definition:iff", LeftToRight));
    block->append(input({2,1}, "Local:3", LeftToRight));
    block->append(input({2,2}, "Local:3", LeftToRight));
    block->append(input({1}, "Local:5", LeftToRight));
    block->append(input({2}, "Local:5", LeftToRight));
    block->append(input({}, "Proposition:land_lor_distributivity_1", RightToLeft));
    block->append(input({2,2}, "Local:3", RightToLeft));
    block->append(input({2}, "Proposition:lor_complement_1", LeftToRight));
    block->append(input({}, "Proposition:land_identity_1", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    fout<<"\\subsection{Axiom of Substitution for quantifiers}"<<endl;
    Proposition::Current = new Proposition("implies_substitution_forall_1", LOGIC, "\\forall a \\forall b \\forall c \\forall d (((a \\implies b) \\land (c \\implies d)) \\implies ((a \\land c) \\implies (b \\land d)))");
    description = "Substitution of $\\implies$ for $\\forall$.";

    block = new proof_block("1", Proposition("", LOGIC, "\\forall a \\forall b \\forall c \\forall d ((((a \\implies b) \\land (c \\implies d)) \\land (a \\land c)) \\implies (b \\land d))"), deduction_LeftToRight);
    block->append(input({}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({}, "Proposition:land_commutativity_2_2", RightToLeft));
    block->append(input({1}, "Proposition:implies_satisfied", LeftToRight));
    block->append(input({2}, "Proposition:implies_satisfied", LeftToRight));
    Proposition::Current->append(block);

    block = new proof_block(backward);
    block->append(input({}, "Proposition:multiple_condition", LeftToRight));
    block->append(input({}, "Local:1", PToTrue));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    Proposition::Current = new Proposition("implies_substitution_exists_1", LOGIC, "\\forall a \\forall b \\forall c \\forall d (((a \\implies b) \\land (c \\implies d)) \\implies ((a \\lor c) \\implies (b \\lor d)))");
    description = "Substitution of $\\implies$ for $\\exists$.";
    block = new proof_block("1", Proposition("", LOGIC, "\\forall a \\forall b \\forall c \\forall d ((((a \\implies b) \\land (c \\implies d)) \\land (a \\lor c)) \\implies (b \\lor d))"), deduction_LeftToRight);
    block->append(input({}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({}, "Proposition:land_lor_distributivity_2", LeftToRight));
    block->append(input({1}, "Proposition:land_associativity", RightToLeft));
    block->append(input({2,2}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({2}, "Proposition:land_associativity", RightToLeft));
    block->append(input({1}, "Proposition:a_land_b_implies_a", LeftToRight));
    block->append(input({2}, "Proposition:a_land_b_implies_a", LeftToRight));
    block->append(input({1}, "Proposition:implies_satisfied", LeftToRight));
    block->append(input({2}, "Proposition:implies_satisfied", LeftToRight));
    Proposition::Current->append(block);

    block = new proof_block(backward);
    block->append(input({}, "Proposition:multiple_condition", LeftToRight));
    block->append(input({}, "Local:1", PToTrue));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    Proposition::Current = new Proposition("iff_substitution_forall_1", LOGIC, "\\forall a \\forall b \\forall c \\forall d (((a \\iff b) \\land (c \\iff d)) \\implies ((a \\land c) \\iff (b \\land d)))");
    description = "Substitution of $\\iff$ for $\\forall$.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({1}, "Proposition:iff_implies", LeftToRight));
    block->append(input({2}, "Proposition:iff_implies", LeftToRight));
    block->append(input({}, "Proposition:land_commutativity_2_2", RightToLeft));
    block->append(input({1}, "Proposition:implies_substitution_forall_1", LeftToRight));
    block->append(input({2}, "Proposition:implies_substitution_forall_1", LeftToRight));
    block->append(input({}, "Proposition:iff_implies", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    Proposition::Current = new Proposition("iff_substitution_exists_1", LOGIC, "\\forall a \\forall b \\forall c \\forall d (((a \\iff b) \\land (c \\iff d)) \\implies ((a \\lor c) \\iff (b \\lor d)))");
    description = "Substitution of $\\iff$ for $\\exists$.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({1}, "Proposition:iff_implies", LeftToRight));
    block->append(input({2}, "Proposition:iff_implies", LeftToRight));
    block->append(input({}, "Proposition:land_commutativity_2_2", RightToLeft));
    block->append(input({1}, "Proposition:implies_substitution_exists_1", LeftToRight));
    block->append(input({2}, "Proposition:implies_substitution_exists_1", LeftToRight));
    block->append(input({}, "Proposition:iff_implies", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

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

    fout<<"\\begin{defn}"<<endl;
    fout<<"\\label{Definition:uniqueness_quantifier}"<<endl;
    fout<<"Uniqueness quantifier is denoted by $!\\exists$."<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& !\\exists x (P(x)) \\\\"<<endl;
    fout<<"\\overset{\\operatorname{def}}{\\iff} & (\\exists x (P(x))) \\land (\\forall x \\forall y ((P(x) \\land P(y)) \\implies (x = y)))"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{defn}"<<endl;
    fout<<endl;

    {
        logic_variable* a = new logic_variable("a");
        set_variable* b = new set_variable("b");
        universal_quantifier* u1 = new universal_quantifier(b,a);

        a = new logic_variable("a");

        logic_binary_operator_logic_logic* iff = new logic_binary_operator_logic_logic("\\iff", u1, a);

        a = new logic_variable("a");
        universal_quantifier* u0 = new universal_quantifier(a, iff);

        Axiom::Current = new Axiom("forall_independent_variable", u0);
    }
    Axiom::addAxiom("$a$ is independent of $b$.");

    {
        logic_variable* a = new logic_variable("a");
        set_variable* b = new set_variable("b");
        existential_quantifier* e1 = new existential_quantifier(b,a);

        a = new logic_variable("a");

        logic_binary_operator_logic_logic* iff = new logic_binary_operator_logic_logic("\\iff", e1, a);

        a = new logic_variable("a");
        universal_quantifier* u0 = new universal_quantifier(a, iff);

        Axiom::Current = new Axiom("exists_independent_variable", u0);
    }
    Axiom::addAxiom("$a$ is independent of $b$.");

    fout<<"\\subsection{Boolean algebra for quantifier}"<<endl;
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
    Proposition::addProposition();

    fout<<"Proof of Proposition \\ref{Proposition:forall_land_commutativity} \\\\"<<endl;
    fout<<"For n = 2,"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& (a_1 \\land a_2) \\land (b_1 \\land b_2) \\\\"<<endl;
    fout<<"\\iff & (a_1 \\land b_1) \\land (a_2 \\land b_2)"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:land_commutativity_2_2}} \\\\"<<endl;
    fout<<"\\end{align*}"<<endl;

    fout<<"For n = k+1,"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& ((( \\dots (a_1 \\land a_2) \\dots ) \\land a_k) \\land a_{k+1}) \\land ((( \\dots (b_1 \\land b_2) \\dots ) \\land b_k ) \\land b_{k+1}) \\\\"<<endl;
    fout<<"\\iff & (( \\dots (a_1 \\land a_2) \\dots ) \\land (a_k \\land a_{k+1})) \\land ((( \\dots (b_1 \\land b_2) \\dots ) \\land b_k ) \\land b_{k+1})"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:land_associativity}} \\\\"<<endl;
    fout<<"\\iff & (( \\dots (a_1 \\land a_2) \\dots ) \\land (a_k \\land a_{k+1})) \\land (( \\dots (b_1 \\land b_2) \\dots ) \\land (b_k \\land b_{k+1}))"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:land_associativity}} \\\\"<<endl;
    fout<<"\\iff & ( \\dots ((a_1 \\land b_1) \\land (a_2 \\land b_2)) \\dots ) \\land ((a_k \\land a_{k+1}) \\land (b_k \\land b_{k+1}))"<<endl;
    fout<<"& & \\text{Assumption for n=k} \\\\"<<endl;
    fout<<"\\iff & ( \\dots ((a_1 \\land b_1) \\land (a_2 \\land b_2)) \\dots ) \\land ((a_k \\land b_k) \\land (a_{k+1} \\land b_{k+1}))"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:land_commutativity_2_2}} \\\\"<<endl;
    fout<<"\\iff & (( \\dots ((a_1 \\land b_1) \\land (a_2 \\land b_2)) \\dots ) \\land (a_k \\land b_k)) \\land (a_{k+1} \\land b_{k+1})"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:land_associativity}} \\\\"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<endl;

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
    Proposition::addProposition();

    fout<<"Proof of Proposition \\ref{Proposition:exists_lor_commutativity} \\\\"<<endl;
    fout<<"For n = 2,"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& (a_1 \\lor a_2) \\lor (b_1 \\lor b_2) \\\\"<<endl;
    fout<<"\\iff & (a_1 \\lor b_1) \\lor (a_2 \\lor b_2)"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:lor_commutativity_2_2}} \\\\"<<endl;
    fout<<"\\end{align*}"<<endl;

    fout<<"For n = k+1,"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& ((( \\dots (a_1 \\lor a_2) \\dots ) \\lor a_k) \\lor a_{k+1}) \\lor ((( \\dots (b_1 \\lor b_2) \\dots ) \\lor b_k ) \\lor b_{k+1}) \\\\"<<endl;
    fout<<"\\iff & (( \\dots (a_1 \\lor a_2) \\dots ) \\lor (a_k \\lor a_{k+1})) \\lor ((( \\dots (b_1 \\lor b_2) \\dots ) \\lor b_k ) \\lor b_{k+1})"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:lor_associativity}} \\\\"<<endl;
    fout<<"\\iff & (( \\dots (a_1 \\lor a_2) \\dots ) \\lor (a_k \\lor a_{k+1})) \\lor (( \\dots (b_1 \\lor b_2) \\dots ) \\lor (b_k \\lor b_{k+1}))"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:lor_associativity}} \\\\"<<endl;
    fout<<"\\iff & ( \\dots ((a_1 \\lor b_1) \\lor (a_2 \\lor b_2)) \\dots ) \\lor ((a_k \\lor a_{k+1}) \\lor (b_k \\lor b_{k+1}))"<<endl;
    fout<<"& & \\text{Assumption for n=k} \\\\"<<endl;
    fout<<"\\iff & ( \\dots ((a_1 \\lor b_1) \\lor (a_2 \\lor b_2)) \\dots ) \\lor ((a_k \\lor b_k) \\lor (a_{k+1} \\lor b_{k+1}))"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:lor_commutativity_2_2}} \\\\"<<endl;
    fout<<"\\iff & (( \\dots ((a_1 \\lor b_1) \\lor (a_2 \\lor b_2)) \\dots ) \\lor (a_k \\lor b_k)) \\lor (a_{k+1} \\lor b_{k+1})"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:lor_associativity}} \\\\"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<endl;

    {
        logic_variable* a = new logic_variable("a");
        set_variable* c = new set_variable("c");
        logic_variable* b = new logic_variable("b");
        universal_quantifier* u1 = new universal_quantifier(c,b);
        logic_binary_operator_logic_logic* a_or_u1 = new logic_binary_operator_logic_logic("\\lor", a, u1);

        a = new logic_variable("a");
        b = new logic_variable("b");
        logic_binary_operator_logic_logic* a_or_b = new logic_binary_operator_logic_logic("\\lor", a, b);
        c = new set_variable("c");
        universal_quantifier* u2 = new universal_quantifier(c, a_or_b);

        logic_binary_operator_logic_logic* iff = new logic_binary_operator_logic_logic("\\iff", a_or_u1, u2);

        b = new logic_variable("b");
        universal_quantifier* ub = new universal_quantifier(b, iff);
        a = new logic_variable("a");
        universal_quantifier* ua = new universal_quantifier(a, ub);

        Proposition::Current = new Proposition("lor_forall_distributivity", ua);
    }
    Proposition::addProposition("$a$ is independent of $c$.");

    fout<<"Proof of Proposition \\ref{Proposition:lor_forall_distributivity} \\\\"<<endl;
    fout<<"For n = 2,"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& a \\lor (b_1 \\land b_2) \\\\"<<endl;
    fout<<"\\iff & (a \\lor b_1) \\land (a \\lor b_2)"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:lor_land_distributivity_1}} \\\\"<<endl;
    fout<<"\\end{align*}"<<endl;

    fout<<"For n = k+1,"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& a \\lor ((( \\dots (b_1 \\land b_2) \\dots ) \\land b_k ) \\land b_{k+1}) \\\\"<<endl;
    fout<<"\\iff & a \\lor (( \\dots (b_1 \\land b_2) \\dots ) \\land ( b_k \\land b_{k+1}))"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:land_associativity}} \\\\"<<endl;
    fout<<"\\iff & ( \\dots ((a \\lor b_1) \\land (a \\lor b_2)) \\dots ) \\land (a \\lor (b_k \\land b_{k+1}))"<<endl;
    fout<<"& & \\text{Assumption for n=k} \\\\"<<endl;
    fout<<"\\iff & ( \\dots ((a \\lor b_1) \\land (a \\lor b_2)) \\dots ) \\land ((a \\lor b_k) \\land (a \\lor b_{k+1}))"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:lor_land_distributivity_1}} \\\\"<<endl;
    fout<<"\\iff & (( \\dots ((a \\lor b_1) \\land (a \\lor b_2)) \\dots ) \\land (a \\lor b_k)) \\land (a \\lor b_{k+1})"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:land_associativity}} \\\\"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<endl;

    {
        logic_variable* a = new logic_variable("a");
        set_variable* c = new set_variable("c");
        logic_variable* b = new logic_variable("b");
        existential_quantifier* e1 = new existential_quantifier(c,b);
        logic_binary_operator_logic_logic* a_and_e1 = new logic_binary_operator_logic_logic("\\land", a, e1);

        a = new logic_variable("a");
        b = new logic_variable("b");
        logic_binary_operator_logic_logic* a_and_b = new logic_binary_operator_logic_logic("\\land", a, b);
        c = new set_variable("c");
        existential_quantifier* e2 = new existential_quantifier(c, a_and_b);

        logic_binary_operator_logic_logic* iff = new logic_binary_operator_logic_logic("\\iff", a_and_e1, e2);

        b = new logic_variable("b");
        universal_quantifier* ub = new universal_quantifier(b, iff);
        a = new logic_variable("a");
        universal_quantifier* ua = new universal_quantifier(a, ub);

        Proposition::Current = new Proposition("land_exists_distributivity", ua);
    }
    Proposition::addProposition("$a$ is independent of $c$.");

    fout<<"Proof of Proposition \\ref{Proposition:land_exists_distributivity} \\\\"<<endl;
    fout<<"For n = 2,"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& a \\land (b_1 \\lor b_2) \\\\"<<endl;
    fout<<"\\iff & (a \\land b_1) \\lor (a \\land b_2)"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:land_lor_distributivity_1}} \\\\"<<endl;
    fout<<"\\end{align*}"<<endl;

    fout<<"For n = k+1,"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& a \\land ((( \\dots (b_1 \\lor b_2) \\dots ) \\lor b_k ) \\lor b_{k+1}) \\\\"<<endl;
    fout<<"\\iff & a \\land (( \\dots (b_1 \\lor b_2) \\dots ) \\lor ( b_k \\lor b_{k+1}))"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:lor_associativity}} \\\\"<<endl;
    fout<<"\\iff & ( \\dots ((a \\land b_1) \\lor (a \\land b_2)) \\dots ) \\lor (a \\land (b_k \\lor b_{k+1}))"<<endl;
    fout<<"& & \\text{Assumption for n=k} \\\\"<<endl;
    fout<<"\\iff & ( \\dots ((a \\land b_1) \\lor (a \\land b_2)) \\dots ) \\lor ((a \\land b_k) \\lor (a \\land b_{k+1}))"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:land_lor_distributivity_1}} \\\\"<<endl;
    fout<<"\\iff & (( \\dots ((a \\land b_1) \\lor (a \\land b_2)) \\dots ) \\lor (a \\land b_k)) \\lor (a \\land b_{k+1})"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:lor_associativity}} \\\\"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<endl;

    {
        logic_variable* a = new logic_variable("a");
        set_variable* c = new set_variable("c");
        logic_variable* b = new logic_variable("b");
        universal_quantifier* u1 = new universal_quantifier(c,b);
        logic_binary_operator_logic_logic* a_implies_u1 = new logic_binary_operator_logic_logic("\\implies", a, u1);

        a = new logic_variable("a");
        b = new logic_variable("b");
        logic_binary_operator_logic_logic* a_implies_b = new logic_binary_operator_logic_logic("\\implies", a, b);
        c = new set_variable("c");
        universal_quantifier* u2 = new universal_quantifier(c, a_implies_b);

        logic_binary_operator_logic_logic* iff = new logic_binary_operator_logic_logic("\\iff", a_implies_u1, u2);

        b = new logic_variable("b");
        universal_quantifier* ub = new universal_quantifier(b, iff);
        a = new logic_variable("a");
        universal_quantifier* ua = new universal_quantifier(a, ub);

        Proposition::Current = new Proposition("implies_forall_distributivity", ua);
    }
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Definition:implies", LeftToRight));
    block->append(input({}, "Proposition:lor_forall_distributivity", LeftToRight));
    block->append(input({1}, "Definition:implies", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition("$a$ is independent of $c$.");

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
    Proposition::addProposition("De Morgan's law");

    fout<<"Proof of Proposition \\ref{Proposition:De_Morgan_1} \\\\"<<endl;
    fout<<"For n = 2,"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& \\lnot (a_1 \\land a_2) \\\\"<<endl;
    fout<<"\\iff & (\\lnot a_1) \\lor (\\lnot a_2)"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:De_Morgan_land}} \\\\"<<endl;
    fout<<"\\end{align*}"<<endl;

    fout<<"For n = k+1,"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& \\lnot ((( \\dots (a_1 \\land a_2) \\dots ) \\land a_k ) \\land a_{k+1}) \\\\"<<endl;
    fout<<"\\iff & \\lnot (( \\dots (a_1 \\land a_2) \\dots ) \\land ( a_k \\land a_{k+1}))"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:land_associativity}} \\\\"<<endl;
    fout<<"\\iff & ( \\dots ((\\lnot a_1) \\lor (\\lnot a_2)) \\dots ) \\lor (\\lnot (a_k \\land a_{k+1}))"<<endl;
    fout<<"& & \\text{Assumption for n=k} \\\\"<<endl;
    fout<<"\\iff & ( \\dots ((\\lnot a_1) \\lor (\\lnot a_2)) \\dots ) \\lor ((\\lnot a_k) \\lor (\\lnot a_{k+1}))"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:De_Morgan_land}} \\\\"<<endl;
    fout<<"\\iff & (( \\dots ((\\lnot a_1) \\lor (\\lnot a_2)) \\dots ) \\lor (\\lnot a_k)) \\lor (\\lnot a_{k+1})"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:lor_associativity}} \\\\"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<endl;

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
    Proposition::addProposition("De Morgan's law");

    fout<<"Proof of Proposition \\ref{Proposition:De_Morgan_2} \\\\"<<endl;
    fout<<"For n = 2,"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& \\lnot (a_1 \\lor a_2) \\\\"<<endl;
    fout<<"\\iff & (\\lnot a_1) \\land (\\lnot a_2)"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:De_Morgan_lor}} \\\\"<<endl;
    fout<<"\\end{align*}"<<endl;

    fout<<"For n = k+1,"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& \\lnot ((( \\dots (a_1 \\lor a_2) \\dots ) \\lor a_k ) \\lor a_{k+1}) \\\\"<<endl;
    fout<<"\\iff & \\lnot (( \\dots (a_1 \\lor a_2) \\dots ) \\lor ( a_k \\lor a_{k+1}))"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:lor_associativity}} \\\\"<<endl;
    fout<<"\\iff & ( \\dots ((\\lnot a_1) \\land (\\lnot a_2)) \\dots ) \\land (\\lnot (a_k \\lor a_{k+1}))"<<endl;
    fout<<"& & \\text{Assumption for n=k} \\\\"<<endl;
    fout<<"\\iff & ( \\dots ((\\lnot a_1) \\land (\\lnot a_2)) \\dots ) \\land ((\\lnot a_k) \\land (\\lnot a_{k+1}))"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:De_Morgan_lor}} \\\\"<<endl;
    fout<<"\\iff & (( \\dots ((\\lnot a_1) \\land (\\lnot a_2)) \\dots ) \\land (\\lnot a_k)) \\land (\\lnot a_{k+1})"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:land_associativity}} \\\\"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<endl;

    fout<<"\\subsection{Axiom of Substitution for quantifiers}"<<endl;

    {
        logic_variable* a = new logic_variable("a");
        logic_variable* b = new logic_variable("b");
        logic_binary_operator_logic_logic* implies1 = new logic_binary_operator_logic_logic("\\implies", a, b);
        set_variable* c = new set_variable("c");
        universal_quantifier* u0 = new universal_quantifier(c, implies1);

        a = new logic_variable("a");
        c = new set_variable("c");
        universal_quantifier* u1 = new universal_quantifier(c, a);
        b = new logic_variable("b");
        c = new set_variable("c");
        universal_quantifier* u2 = new universal_quantifier(c, b);
        logic_binary_operator_logic_logic* implies2 = new logic_binary_operator_logic_logic("\\implies", u1, u2);

        logic_binary_operator_logic_logic* implies0 = new logic_binary_operator_logic_logic("\\implies", u0, implies2);

        b = new logic_variable("b");
        universal_quantifier* ub = new universal_quantifier(b, implies0);
        a = new logic_variable("a");
        universal_quantifier* ua = new universal_quantifier(a, ub);

        Proposition::Current = new Proposition("implies_substitution_forall_2", ua);
    }
    Proposition::addProposition();

    fout<<"Proof of Proposition \\ref{Proposition:implies_substitution_forall_2} \\\\"<<endl;
    fout<<"For n = 2,"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& (a_1 \\implies b_1) \\land (a_2 \\implies b_2) \\\\"<<endl;
    fout<<"\\implies & (a_1 \\land a_2) \\implies (b_1 \\land b_2)"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:implies_substitution_forall_1}} \\\\"<<endl;
    fout<<"\\end{align*}"<<endl;

    fout<<"For n = k+1,"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& (( \\dots ((a_1 \\implies b_1) \\land (a_2 \\implies b_2)) \\dots ) \\land (a_k \\implies b_k)) \\land (a_{k+1} \\implies b_{k+1}) \\\\"<<endl;
    fout<<"\\implies & ((( \\dots (a_1 \\land a_2) \\dots ) \\land a_k) \\implies (( \\dots (b_1 \\land b_2) \\dots ) \\land b_k)) \\land (a_{k+1} \\implies b_{k+1})"<<endl;
    fout<<"& & \\text{Assumption for n=k} \\\\"<<endl;
    fout<<"\\implies & ((( \\dots (a_1 \\land a_2) \\dots ) \\land a_k) \\land a_{k+1}) \\implies ((( \\dots (b_1 \\land b_2) \\dots ) \\land b_k) \\land b_{k+1})"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:implies_substitution_forall_1}} \\\\"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<endl;

    {
        logic_variable* a = new logic_variable("a");
        logic_variable* b = new logic_variable("b");
        logic_binary_operator_logic_logic* implies1 = new logic_binary_operator_logic_logic("\\implies", a, b);
        set_variable* c = new set_variable("c");
        universal_quantifier* u0 = new universal_quantifier(c, implies1);

        a = new logic_variable("a");
        c = new set_variable("c");
        existential_quantifier* e1 = new existential_quantifier(c, a);
        b = new logic_variable("b");
        c = new set_variable("c");
        existential_quantifier* e2 = new existential_quantifier(c, b);
        logic_binary_operator_logic_logic* implies2 = new logic_binary_operator_logic_logic("\\implies", e1, e2);

        logic_binary_operator_logic_logic* implies0 = new logic_binary_operator_logic_logic("\\implies", u0, implies2);

        b = new logic_variable("b");
        universal_quantifier* ub = new universal_quantifier(b, implies0);
        a = new logic_variable("a");
        universal_quantifier* ua = new universal_quantifier(a, ub);

        Proposition::Current = new Proposition("implies_substitution_exists_2", ua);
    }
    Proposition::addProposition();

    fout<<"Proof of Proposition \\ref{Proposition:implies_substitution_exists_2} \\\\"<<endl;
    fout<<"For n = 2,"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& (a_1 \\implies b_1) \\land (a_2 \\implies b_2) \\\\"<<endl;
    fout<<"\\implies & (a_1 \\lor a_2) \\implies (b_1 \\lor b_2)"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:implies_substitution_exists_1}} \\\\"<<endl;
    fout<<"\\end{align*}"<<endl;

    fout<<"For n = k+1,"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& (( \\dots ((a_1 \\implies b_1) \\land (a_2 \\implies b_2)) \\dots ) \\land (a_k \\implies b_k)) \\land (a_{k+1} \\implies b_{k+1}) \\\\"<<endl;
    fout<<"\\implies & ((( \\dots (a_1 \\lor a_2) \\dots ) \\lor a_k) \\implies (( \\dots (b_1 \\lor b_2) \\dots ) \\lor b_k)) \\land (a_{k+1} \\implies b_{k+1})"<<endl;
    fout<<"& & \\text{Assumption for n=k} \\\\"<<endl;
    fout<<"\\implies & ((( \\dots (a_1 \\lor a_2) \\dots ) \\lor a_k) \\lor a_{k+1}) \\implies ((( \\dots (b_1 \\lor b_2) \\dots ) \\lor b_k) \\lor b_{k+1})"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:implies_substitution_exists_1}} \\\\"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<endl;

    {
        logic_variable* a = new logic_variable("a");
        logic_variable* b = new logic_variable("b");
        logic_binary_operator_logic_logic* iff1 = new logic_binary_operator_logic_logic("\\iff", a, b);
        set_variable* c = new set_variable("c");
        universal_quantifier* u0 = new universal_quantifier(c, iff1);

        a = new logic_variable("a");
        c = new set_variable("c");
        universal_quantifier* u1 = new universal_quantifier(c, a);
        b = new logic_variable("b");
        c = new set_variable("c");
        universal_quantifier* u2 = new universal_quantifier(c, b);
        logic_binary_operator_logic_logic* iff2 = new logic_binary_operator_logic_logic("\\iff", u1, u2);

        logic_binary_operator_logic_logic* implies0 = new logic_binary_operator_logic_logic("\\implies", u0, iff2);

        b = new logic_variable("b");
        universal_quantifier* ub = new universal_quantifier(b, implies0);
        a = new logic_variable("a");
        universal_quantifier* ua = new universal_quantifier(a, ub);

        Proposition::Current = new Proposition("iff_substitution_forall_2", ua);
    }
    Proposition::addProposition();

    fout<<"Proof of Proposition \\ref{Proposition:iff_substitution_forall_2} \\\\"<<endl;
    fout<<"For n = 2,"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& (a_1 \\iff b_1) \\land (a_2 \\iff b_2) \\\\"<<endl;
    fout<<"\\implies & (a_1 \\land a_2) \\iff (b_1 \\land b_2)"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:iff_substitution_forall_1}} \\\\"<<endl;
    fout<<"\\end{align*}"<<endl;

    fout<<"For n = k+1,"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& (( \\dots ((a_1 \\iff b_1) \\land (a_2 \\iff b_2)) \\dots ) \\land (a_k \\iff b_k)) \\land (a_{k+1} \\iff b_{k+1}) \\\\"<<endl;
    fout<<"\\implies & ((( \\dots (a_1 \\land a_2) \\dots ) \\land a_k) \\iff (( \\dots (b_1 \\land b_2) \\dots ) \\land b_k)) \\land (a_{k+1} \\iff b_{k+1})"<<endl;
    fout<<"& & \\text{Assumption for n=k} \\\\"<<endl;
    fout<<"\\implies & ((( \\dots (a_1 \\land a_2) \\dots ) \\land a_k) \\land a_{k+1}) \\iff ((( \\dots (b_1 \\land b_2) \\dots ) \\land b_k) \\land b_{k+1})"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:iff_substitution_forall_1}} \\\\"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<endl;

    {
        logic_variable* a = new logic_variable("a");
        logic_variable* b = new logic_variable("b");
        logic_binary_operator_logic_logic* iff1 = new logic_binary_operator_logic_logic("\\iff", a, b);
        set_variable* c = new set_variable("c");
        universal_quantifier* u0 = new universal_quantifier(c, iff1);

        a = new logic_variable("a");
        c = new set_variable("c");
        existential_quantifier* e1 = new existential_quantifier(c, a);
        b = new logic_variable("b");
        c = new set_variable("c");
        existential_quantifier* e2 = new existential_quantifier(c, b);
        logic_binary_operator_logic_logic* iff2 = new logic_binary_operator_logic_logic("\\iff", e1, e2);

        logic_binary_operator_logic_logic* implies0 = new logic_binary_operator_logic_logic("\\implies", u0, iff2);

        b = new logic_variable("b");
        universal_quantifier* ub = new universal_quantifier(b, implies0);
        a = new logic_variable("a");
        universal_quantifier* ua = new universal_quantifier(a, ub);

        Proposition::Current = new Proposition("iff_substitution_exists_2", ua);
    }
    Proposition::addProposition();

    fout<<"Proof of Proposition \\ref{Proposition:iff_substitution_exists_2} \\\\"<<endl;
    fout<<"For n = 2,"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& (a_1 \\iff b_1) \\land (a_2 \\iff b_2) \\\\"<<endl;
    fout<<"\\implies & (a_1 \\lor a_2) \\iff (b_1 \\lor b_2)"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:iff_substitution_exists_1}} \\\\"<<endl;
    fout<<"\\end{align*}"<<endl;

    fout<<"For n = k+1,"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& (( \\dots ((a_1 \\iff b_1) \\land (a_2 \\iff b_2)) \\dots ) \\land (a_k \\iff b_k)) \\land (a_{k+1} \\iff b_{k+1}) \\\\"<<endl;
    fout<<"\\implies & ((( \\dots (a_1 \\lor a_2) \\dots ) \\lor a_k) \\iff (( \\dots (b_1 \\lor b_2) \\dots ) \\lor b_k)) \\land (a_{k+1} \\iff b_{k+1})"<<endl;
    fout<<"& & \\text{Assumption for n=k} \\\\"<<endl;
    fout<<"\\implies & ((( \\dots (a_1 \\lor a_2) \\dots ) \\lor a_k) \\lor a_{k+1}) \\iff ((( \\dots (b_1 \\lor b_2) \\dots ) \\lor b_k) \\lor b_{k+1})"<<endl;
    fout<<"& & \\text{Proposition \\ref{Proposition:iff_substitution_exists_1}} \\\\"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<endl;

    fout<<"\\subsection{Axiom of Existence}"<<endl;
    fout<<"\\begin{axm}"<<endl;
    fout<<"\\label{Axiom:axiom_of_existence}"<<endl;
    fout<<"Axiom of Existence"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& \\forall a ( \\\\"<<endl;
    fout<<"& & & P(a,a) \\\\"<<endl;
    fout<<"& & \\iff & \\exists b ((b = a) \\land (P(a,b))) \\\\"<<endl;
    fout<<"& )"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{axm}"<<endl;
    fout<<endl;

    //Logic proposition
    fout<<"\\section{Logic proposition}"<<endl;

    //Reflexive Property of implies
    Proposition::Current = new Proposition("implies_reflexive", LOGIC, "\\forall a (a \\implies a)");
    description = "Reflexive property of $\\implies$.";
    block = new proof_block(backward);
    block->append(input({}, "Definition:implies", LeftToRight));
    block->append(input({}, "Proposition:lor_complement_2", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    //Reflexive Property of iff
    Proposition::Current = new Proposition("iff_reflexive", LOGIC, "\\forall a (a \\iff a)");
    description = "Reflexive property of $\\iff$.";
    block = new proof_block(backward);
    block->append(input({}, "Definition:iff", LeftToRight));
    block->append(input({1}, "Proposition:land_idempotence", LeftToRight));
    block->append(input({2}, "Proposition:land_idempotence", LeftToRight));
    block->append(input({}, "Proposition:lor_complement_1", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    //lemma_substitution
    Proposition::Current = new Proposition("lemma_substitution", LOGIC, "\\forall a \\forall b \\forall c ((a \\implies (b \\iff c)) \\iff (((a \\land b) \\implies c) \\land ((a \\land c) \\implies b)))");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({2}, "Proposition:iff_implies", LeftToRight));
    block->append(input({}, "Definition:implies", LeftToRight));
    block->append(input({}, "Proposition:lor_land_distributivity_1", LeftToRight));
    block->append(input({1}, "Definition:implies", RightToLeft));
    block->append(input({2}, "Definition:implies", RightToLeft));
    block->append(input({1}, "Proposition:multiple_condition", LeftToRight));
    block->append(input({2}, "Proposition:multiple_condition", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();

    Proposition::Current = new Proposition("lor_iff_distributivity", LOGIC, "\\forall a \\forall b \\forall c ((a \\lor (b \\iff c)) \\iff ((a \\lor b) \\iff (a \\lor c)))");
    description = "Distributivity of $\\lor$ over $\\iff$";
    block = new proof_block(deduction_RightToLeft);
    block->append(input({}, "Definition:iff", LeftToRight));
    block->append(input({1}, "Proposition:lor_land_distributivity_1", RightToLeft));
    block->append(input({2,1}, "Proposition:De_Morgan_lor", LeftToRight));
    block->append(input({2,2}, "Proposition:De_Morgan_lor", LeftToRight));
    block->append(input({2}, "Proposition:land_commutativity_2_2", LeftToRight));
    block->append(input({2,1}, "Proposition:land_idempotence", LeftToRight));
    block->append(input({}, "Proposition:lor_land_distributivity_1", LeftToRight));
    block->append(input({1}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({1}, "Proposition:lor_associativity", RightToLeft));
    block->append(input({1,1}, "Proposition:lor_complement_2", LeftToRight));
    block->append(input({1}, "Proposition:lor_annihilator_2", LeftToRight));
    block->append(input({}, "Proposition:land_identity_2", LeftToRight));
    block->append(input({}, "Proposition:lor_associativity", LeftToRight));
    block->append(input({2}, "Definition:iff", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);

    fout.close();
}
