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
    
    Proposition* x = nullptr;
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
    
    x = new Proposition("forall_true", SET, "(\\forall a (\\text{True})) \\iff (\\text{True})");
    Proposition::addProposition(fout, x);
    
    //Equality
    fout<<"\\section{Equality of sets}"<<endl;
    Definition::addDefinition(fout, new Definition("equality", SET, "\\forall a \\forall b ((a = b) \\overset{\\operatorname{def}}{\\iff} (\\forall c ((c \\in a) \\iff (c \\in b))))"), "Definition of $=$.");
    
    Definition::addDefinition(fout, new Definition("neq", SET, "\\forall a \\forall b ((a \\neq b) \\overset{\\operatorname{def}}{\\iff} (\\lnot (a = b)))"), "Definition of $\\neq$.");
    
    x = new Proposition("equality_reflexive", SET, "\\forall a (a = a)");
    description = "Reflexive property of equality.";
    block = new proof_block("equality_reflexive", x, backward);
    block->append_binary_operator(input({}, "Definition:equality", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:iff_reflexive", PToTrue));
    block->append_binary_operator(input({}, "Proposition:forall_true", LeftToRight, true));
    x->append(block, true);
    Proposition::addProposition(fout, x, description);
    
    x = new Proposition("equality_symmetric", SET, "\\forall a \\forall b ((a = b) \\iff (b = a))");
    description = "Symmetric property of equality.";
    block = new proof_block("equality_symmetric", x, deduction);
    block->append_binary_operator(input({}, "Definition:equality", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:iff_symmetric", LeftToRight));
    block->append_binary_operator(input({}, "Definition:equality", RightToLeft, true));
    x->append(block, true);
    Proposition::addProposition(fout, x, description);
    
    x = new Proposition("equality_transitive", SET, "\\forall a \\forall b \\forall c (((a = b) \\land (b = c)) \\implies (a = c))");
    description = "Transitive property of equality.";
    block = new proof_block("equality_transitive", x, deduction);
    block->append_binary_operator(input({1}, "Definition:equality", LeftToRight));
    block->append_binary_operator(input({2}, "Definition:equality", LeftToRight));
    block->append_binary_operator(input({}, "Proposition:forall_land_commutativity", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:iff_transitive", LeftToRight));
    block->append_binary_operator(input({}, "Definition:equality", RightToLeft, true));
    x->append(block, true);
    Proposition::addProposition(fout, x, description);
    
    fout.close();
}
