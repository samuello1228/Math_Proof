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
    Definition::addDefinition(fout, new Definition("iff", LOGIC, "\\forall a \\forall b ((a \\iff b) \\overset{\\operatorname{def}}{\\iff} ((a \\land b) \\lor ((\\lnot a) \\land (\\lnot b))))"));
    
    //Definition of implies
    fout<<"\\subsection{Definition of $\\implies$}"<<endl;
    Definition::addDefinition(fout, new Definition("implies", LOGIC, "\\forall a \\forall b ((a \\implies b) \\overset{\\operatorname{def}}{\\iff} ((\\lnot a) \\lor b))"));
    
    //Boolean algebra
    Proposition* x = nullptr;
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
    
    x = new Proposition("lor_identity_2", LOGIC, "\\forall a (((\\text{False}) \\lor a) \\iff a)");
    /*
    block = new proof_block("lor_identity_2", x, direct);
    sub.clear(); sub.push_back(new substitution("a", "a", LOGIC));
    block->append_binary_operator(input({}, "Proposition:lor_identity_1", TrueToP, sub));
    block->append_binary_operator(input({1}, "Proposition:lor_commutativity", LeftToRight, true));
    x->append(block);
    */
    Proposition::addProposition(fout, x);
    
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
    x = new Proposition("a_lor_b_complement", LOGIC, "\\forall a \\forall b (((a \\land (\\lnot b)) \\lor b) \\iff (a \\lor b))");
    block = new proof_block("a_lor_b_complement", x, deduction);
    block->append_binary_operator(input({}, "Proposition:lor_land_distributivity_2", LeftToRight));
    block->append_binary_operator(input({2}, "Proposition:lor_complement_2", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:land_identity_1", LeftToRight, true));
    x->append(block, true);
    Proposition::addProposition(fout, x);
    
    //Proof technique
    fout<<"\\section{Proof technique}"<<endl;
    
    //true statement
    x = new Proposition("true_statement", LOGIC, "\\forall a ((a \\iff (\\text{True})) \\iff a)");
    block = new proof_block("true_statement", x, deduction);
    block->append_binary_operator(input({}, "Definition:iff", LeftToRight));
    block->append_binary_operator(input({2,2}, "Definition:lnot_True", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:land_identity_1", LeftToRight));
    block->append_binary_operator(input({2}, "Proposition:land_annihilator_1", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:lor_identity_1", LeftToRight, true));
    x->append(block, true);
    Proposition::addProposition(fout, x);
    
    //implies_lor
    x = new Proposition("implies_lor", LOGIC, "\\forall a \\forall b \\forall c ((a \\implies b) \\implies ((a \\lor c) \\implies (b \\lor c)))");
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
    block->append_binary_operator(input({1}, "Proposition:a_lor_b_complement", LeftToRight));
    block->append_binary_operator(input({2}, "Proposition:a_lor_b_complement", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:lor_associativity", RightToLeft));
    block->append_binary_operator(input({1}, "Proposition:lor_commutativity", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:lor_associativity", RightToLeft));
    block->append_binary_operator(input({1,1}, "Proposition:lor_complement_2", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:lor_annihilator_2", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:lor_annihilator_2", LeftToRight, true));
    x->append(block, true);
    Proposition::addProposition(fout, x);
    
    //implies_land
    x = new Proposition("implies_land", LOGIC, "\\forall a \\forall b \\forall c ((a \\implies b) \\implies ((a \\land c) \\implies (b \\land c)))");
    Proposition::addProposition(fout, x);
    
    //contrapositive
    x = new Proposition("contrapositive", LOGIC, "\\forall a \\forall b ((a \\implies b) \\iff ((\\lnot b) \\implies (\\lnot a)))");
    description = "Contrapositive";
    Proposition::addProposition(fout, x, description);
    
    //Transitive property of implies
    x = new Proposition("implies_transitive", LOGIC, "\\forall a \\forall b \\forall c (((a \\implies b) \\land (b \\implies c)) \\implies (a \\implies c))");
    description = "Transitive property of $\\implies$.";
    Proposition::addProposition(fout, x, description);
    
    //iff and implies
    x = new Proposition("iff_implies", LOGIC, "\\forall a \\forall b ((a \\iff b) \\iff ((a \\implies b) \\land (b \\implies a)))");
    Proposition::addProposition(fout, x);
    
    //iff
    x = new Proposition("iff_lor", LOGIC, "\\forall a \\forall b \\forall c ((a \\iff b) \\implies ((a \\lor c) \\iff (b \\lor c)))");
    Proposition::addProposition(fout, x);
    
    x = new Proposition("iff_land", LOGIC, "\\forall a \\forall b \\forall c ((a \\iff b) \\implies ((a \\land c) \\iff (b \\land c)))");
    Proposition::addProposition(fout, x);
    
    x = new Proposition("iff_symmetric", LOGIC, "\\forall a \\forall b \\forall c ((a \\iff b) \\iff (b \\iff a))");
    description = "Symmetric property of $\\iff$.";
    Proposition::addProposition(fout, x, description);
    
    x = new Proposition("iff_contrapositive", LOGIC, "\\forall a \\forall b ((a \\iff b) \\iff ((\\lnot a) \\iff (\\lnot b)))");
    Proposition::addProposition(fout, x);
    
    x = new Proposition("iff_transitive", LOGIC, "\\forall a \\forall b \\forall c (((a \\iff b) \\land (b \\iff c)) \\implies (a \\iff c))");
    description = "Transitive property of $\\iff$.";
    Proposition::addProposition(fout, x, description);
    
    x = new Proposition("iff_reflexive", LOGIC, "\\forall a (a \\iff a)");
    description = "Reflexive property of $\\iff$.";
    block = new proof_block("iff_reflexive", x, backward);
    block->append_binary_operator(input({}, "Definition:iff", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:land_idempotence", LeftToRight));
    block->append_binary_operator(input({2}, "Proposition:land_idempotence", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:lor_complement_1", LeftToRight, true));
    x->append(block, true);
    Proposition::addProposition(fout, x, description);
    
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
    
    fout<<"\\begin{prop}"<<endl;
    fout<<"\\label{Proposition:forall_land_commutativity}"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& \\forall x (P(x) \\land Q(x)) \\\\"<<endl;
    fout<<"\\iff & (\\forall x (P(x))) \\land (\\forall x (Q(x)))"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{prop}"<<endl;
    fout<<endl;
    
    fout<<"\\begin{prop}"<<endl;
    fout<<"\\label{Proposition:exists_lor_commutativity}"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& \\exists x (P(x) \\lor Q(x)) \\\\"<<endl;
    fout<<"\\iff & (\\exists x (P(x))) \\lor (\\exists x (Q(x)))"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{prop}"<<endl;
    fout<<endl;
    
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
    
    fout<<"\\begin{axm}"<<endl;
    fout<<"\\label{Axiom:De_Morgan_1}"<<endl;
    fout<<"De Morgan's law"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& \\lnot (\\forall x (P(x))) \\\\"<<endl;
    fout<<"\\iff & \\exists x (\\lnot (P(x)))"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{axm}"<<endl;
    fout<<endl;
    
    fout<<"\\begin{axm}"<<endl;
    fout<<"\\label{Axiom:De_Morgan_2}"<<endl;
    fout<<"De Morgan's law"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& \\lnot (\\exists x (P(x))) \\\\"<<endl;
    fout<<"\\iff & \\forall x (\\lnot (P(x)))"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{axm}"<<endl;
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
    
    x = new Proposition("land_implies_iff", LOGIC, "\\forall a \\forall b ((a \\land b) \\implies (a \\iff b))");
    Proposition::addProposition(fout, x);
    
    x = new Proposition("land_omit", LOGIC, "\\forall a \\forall b ((a \\land b) \\implies a)");
    Proposition::addProposition(fout, x);
    
    x = new Proposition("lemma_uniqueness", LOGIC, "\\forall a \\forall b \\forall c ((a \\land ((b \\land a) \\implies c)) \\implies (b \\implies c))");
    Proposition::addProposition(fout, x);
    
    x = new Proposition("implies_satisfy", LOGIC, "\\forall a \\forall b ((a \\land (a \\implies b)) \\implies b)");
    Proposition::addProposition(fout, x);
    
    x = new Proposition("iff_satisfy", LOGIC, "\\forall a \\forall b ((a \\land (a \\iff b)) \\implies b)");
    Proposition::addProposition(fout, x);
    
    fout.close();
}
