//
//  set.cpp
//  Math_Proof
//
//  Created by Samuel on 2/10/2021.
//  Copyright © 2021 Samuel. All rights reserved.
//

#include "set.hpp"

void set()
{
    ofstream fout;
    fout.open("set.tex");
    fout<<"\\chapter{Set theory}"<<endl;
    fout<<"Set theory have one primitive notion, called set, and one binary relation, called set membership, denoted by $\\in$."<<endl;
    fout<<endl;
    
    Axiom* axiom = nullptr;
    statement* law = nullptr;
    proof_block* block = nullptr;
    vector<substitution*> sub;
    string description;
    
    //notin
    Definition::addDefinition(fout, new Definition("notin", SET, "\\forall a \\forall b ((a \\notin b) \\overset{\\operatorname{def}}{\\iff} (\\lnot (a \\in b)))"), "Definition of $\\notin$.");
    
    fout<<"\\begin{defn}"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& \\forall a \\in S, P(a) \\\\"<<endl;
    fout<<"\\overset{\\operatorname{def}}{\\iff} & \\forall a ((a \\in S) \\implies (P(a)))"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{defn}"<<endl;
    fout<<endl;
    
    fout<<"\\begin{defn}"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& \\exists a \\in S, P(a) \\\\"<<endl;
    fout<<"\\overset{\\operatorname{def}}{\\iff} & \\exists a ((a \\in S) \\land (P(a)))"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{defn}"<<endl;
    fout<<endl;
    
    Proposition::Current = new Proposition("forall_true", SET, "(\\forall a (\\text{True})) \\iff (\\text{True})");
    Proposition::addProposition(fout, Proposition::Current);
    
    //Equality
    fout<<"\\section{Equality of sets}"<<endl;
    Definition::addDefinition(fout, new Definition("equality", SET, "\\forall a \\forall b ((a = b) \\overset{\\operatorname{def}}{\\iff} (\\forall c ((c \\in a) \\iff (c \\in b))))"), "Definition of $=$.");
    
    Definition::addDefinition(fout, new Definition("equality_def", SET, "\\forall a \\forall b ((a \\overset{\\operatorname{def}}{=} b) \\overset{\\operatorname{def}}{\\iff} (\\forall c ((c \\in a) \\iff (c \\in b))))"), "Definition of $\\overset{\\operatorname{def}}{=}$.");
    
    Definition::addDefinition(fout, new Definition("neq", SET, "\\forall a \\forall b ((a \\neq b) \\overset{\\operatorname{def}}{\\iff} (\\lnot (a = b)))"), "Definition of $\\neq$.");
    
    Proposition::Current = new Proposition("equality_reflexive", SET, "\\forall a (a = a)");
    description = "Reflexive property of equality.";
    block = new proof_block("equality_reflexive", Proposition::Current, backward);
    block->append_binary_operator(input({}, "Definition:equality", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:iff_reflexive", PToTrue));
    block->append_binary_operator(input({}, "Proposition:forall_true", LeftToRight, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    Proposition::Current = new Proposition("equality_symmetric", SET, "\\forall a \\forall b ((a = b) \\iff (b = a))");
    description = "Symmetric property of equality.";
    block = new proof_block("equality_symmetric", Proposition::Current, deduction);
    block->append_binary_operator(input({}, "Definition:equality", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:iff_symmetric", LeftToRight));
    block->append_binary_operator(input({}, "Definition:equality", RightToLeft, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    Proposition::Current = new Proposition("equality_transitive", SET, "\\forall a \\forall b \\forall c (((a = b) \\land (b = c)) \\implies (a = c))");
    description = "Transitive property of equality.";
    block = new proof_block("equality_transitive", Proposition::Current, deduction);
    block->append_binary_operator(input({1}, "Definition:equality", LeftToRight));
    block->append_binary_operator(input({2}, "Definition:equality", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:forall_land_commutativity", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:iff_transitive", LeftToRight));
    block->append_binary_operator(input({}, "Definition:equality", RightToLeft, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    axiom = new Axiom("extensionality", SET, "\\forall a \\forall b ((a = b) \\implies (\\forall c ((a \\in c) \\iff (b \\in c))))");
    Axiom::addAxiom(fout, axiom, "Axiom of extensionality");
    
    axiom = new Axiom("existence_of_empty_set", SET, "\\forall a (a \\notin \\emptyset)");
    Axiom::addAxiom(fout, axiom, "Existence of empty set");
    
    Proposition::Current = new Proposition("uniqueness_of_empty_set", SET, "\\forall a ((\\forall b (b \\notin a)) \\iff (a = \\emptyset))");
    description = "Uniqueness of $\\emptyset$";
    block = new proof_block("uniqueness_of_empty_set", Proposition::Current, deduction);
    block->append_binary_operator(input({1}, "Proposition:true_statement", RightToLeft));
    sub.clear(); sub.push_back(new substitution("a", "b", SET));
    block->append_binary_operator(input({1,2}, "Axiom:existence_of_empty_set", TrueToP, sub));
    block->append_binary_operator(input({1,1}, "Definition:notin", LeftToRight));
    block->append_binary_operator(input({1,2}, "Definition:notin", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:iff_contrapositive", RightToLeft));
    block->append_binary_operator(input({}, "Definition:equality", RightToLeft, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    Proposition::Current = new Proposition("single_choice", SET, "\\forall a ((a \\neq \\emptyset) \\iff (\\exists b (b \\in a)))");
    description = "Single choice";
    block = new proof_block("single_choice", Proposition::Current, direct);
    sub.clear(); sub.push_back(new substitution("a", "a", SET));
    block->append_binary_operator(input({}, "Proposition:uniqueness_of_empty_set", TrueToP, sub));
    block->append_binary_operator(input({}, "Proposition:iff_symmetric", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:iff_contrapositive", LeftToRight));
    block->append_binary_operator(input({1}, "Definition:neq", RightToLeft));
    block->append_binary_operator(input({2}, "Proposition:De_Morgan_1", LeftToRight));
    block->append_binary_operator(input({2,1,1}, "Definition:notin", LeftToRight));
    block->append_binary_operator(input({2,1}, "Proposition:double_negation", LeftToRight, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    axiom = new Axiom("existence_of_pair_set", SET, "\\forall a \\forall b \\forall c ((c \\in \\{ a , b \\}) \\iff ((c = a) \\lor (c = b)))");
    Axiom::addAxiom(fout, axiom, "Existence of pair set");
    
    Proposition::Current = new Proposition("uniqueness_of_pair_set", SET, "\\forall a \\forall b \\forall c ((\\forall d ((d \\in c) \\iff ((d = a) \\lor (d = b)))) \\implies (c = \\{ a , b \\}))");
    description = "Uniqueness of pair set";
    block = new proof_block("uniqueness_of_pair_set", Proposition::Current, deduction);
    block->append_binary_operator(input({1}, "Proposition:land_identity_1", RightToLeft));
    sub.clear();
    sub.push_back(new substitution("a", "a", SET));
    sub.push_back(new substitution("b", "b", SET));
    sub.push_back(new substitution("c", "d", SET));
    block->append_binary_operator(input({1,2}, "Axiom:existence_of_pair_set", TrueToP, sub));
    block->set_split_point({{1,2}});
    block->append_binary_operator(input({1,2}, "Proposition:iff_symmetric", LeftToRight));
    block->set_split_point({{1,2}});
    block->append_binary_operator(input({1}, "Proposition:iff_transitive", LeftToRight));
    block->append_binary_operator(input({}, "Definition:equality", RightToLeft, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    Definition::addDefinition(fout, new Definition("singleton_set", SET, "\\forall a (\\{ a \\} \\overset{\\operatorname{def}}{=} \\{ a , a \\})"), "Definition of singleton set.");
    
    //Property of singleton set
    Proposition::Current = new Proposition("singleton_set_property", SET, "\\forall a \\forall b ((b \\in \\{ a \\}) \\iff (b = a))");
    description = "Property of singleton set.";
    
    block = new proof_block("1", Proposition("", SET, "\\forall a \\forall b ((b \\in \\{ a \\}) \\iff (b \\in \\{ a , a \\}))"), direct);
    block->set_target_forall_variable(1);
    sub.clear(); sub.push_back(new substitution("a", "a", SET));
    block->append_binary_operator(input({}, "Definition:singleton_set", TrueToP, sub));
    block->append_binary_operator(input({}, "Definition:equality_def", LeftToRight, true));
    Proposition::Current->append(block);
    
    block = new proof_block("singleton_set_property", Proposition::Current, deduction);
    block->append_binary_operator(input({}, "Local:1", LeftToRight));
    block->append_binary_operator(input({}, "Axiom:existence_of_pair_set", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:lor_idempotence", LeftToRight, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    //Uniqueness of singleton set
    Proposition::Current = new Proposition("uniqueness_of_singleton_set", SET, "\\forall a \\forall b ((\\forall c ((c \\in b) \\iff (c = a))) \\implies (b = \\{ a \\}))");
    description = "Uniqueness of singleton set.";
    block = new proof_block("uniqueness_of_singleton_set", Proposition::Current, deduction);
    block->append_binary_operator(input({1}, "Proposition:land_identity_1", RightToLeft));
    sub.clear();
    sub.push_back(new substitution("a", "a", SET));
    sub.push_back(new substitution("b", "c", SET));
    block->append_binary_operator(input({1,2}, "Proposition:singleton_set_property", TrueToP, sub));
    block->set_split_point({{1,2}});
    block->append_binary_operator(input({1,2}, "Proposition:iff_symmetric", LeftToRight));
    block->set_split_point({{1,2}});
    block->append_binary_operator(input({1}, "Proposition:iff_transitive", LeftToRight));
    block->append_binary_operator(input({}, "Definition:equality", RightToLeft, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    axiom = new Axiom("existence_of_union_set", SET, "\\forall a \\forall b ((b \\in (\\bigcup a)) \\iff (\\exists c ((b \\in c) \\land (c \\in a))))");
    Axiom::addAxiom(fout, axiom, "Existence of union set.");
    
    //Uniqueness of union set
    Proposition::Current = new Proposition("uniqueness_of_union_set", SET, "\\forall a \\forall b ((\\forall c ((c \\in b) \\iff (\\exists d ((c \\in d) \\land (d \\in a))))) \\implies (b = (\\bigcup a)))");
    description = "Uniqueness of union set.";
    block = new proof_block("uniqueness_of_union_set", Proposition::Current, deduction);
    block->append_binary_operator(input({1}, "Proposition:land_identity_1", RightToLeft));
    sub.clear();
    sub.push_back(new substitution("a", "a", SET));
    sub.push_back(new substitution("b", "c", SET));
    block->append_binary_operator(input({1,2}, "Axiom:existence_of_union_set", TrueToP, sub));
    block->set_split_point({{1,2}});
    block->append_binary_operator(input({1,2}, "Proposition:iff_symmetric", LeftToRight));
    block->set_split_point({{1,2}});
    block->append_binary_operator(input({1}, "Proposition:iff_transitive", LeftToRight));
    block->append_binary_operator(input({}, "Definition:equality", RightToLeft, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    fout.close();
}
