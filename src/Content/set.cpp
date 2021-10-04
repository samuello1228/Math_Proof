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
    Definition::addDefinition(fout, new Definition("notin", SET, "\\forall x \\forall y ((x \\notin y) \\overset{\\operatorname{def}}{\\iff} (\\lnot (x \\in y)))"), "Definition of $\\notin$.");
    
    fout<<"\\begin{defn}"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& \\forall x \\in S, P(x) \\\\"<<endl;
    fout<<"\\overset{\\operatorname{def}}{\\iff} & \\forall x ((x \\in S) \\implies (P(x)))"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{defn}"<<endl;
    fout<<endl;
    
    fout<<"\\begin{defn}"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& \\exists x \\in S, P(x) \\\\"<<endl;
    fout<<"\\overset{\\operatorname{def}}{\\iff} & \\exists x ((x \\in S) \\land (P(x)))"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{defn}"<<endl;
    fout<<endl;
    
    x = new Proposition("forall_true", SET, "(\\forall x (\\text{True})) \\iff (\\text{True})");
    Proposition::addProposition(fout, x);
    
    //Equality
    fout<<"\\section{Equality of sets}"<<endl;
    Definition::addDefinition(fout, new Definition("equality", SET, "\\forall x \\forall y ((x = y) \\overset{\\operatorname{def}}{\\iff} (\\forall z ((z \\in x) \\iff (z \\in y))))"), "Definition of $=$.");
    
    Definition::addDefinition(fout, new Definition("neq", SET, "\\forall x \\forall y ((x \\neq y) \\overset{\\operatorname{def}}{\\iff} (\\lnot (x = y)))"), "Definition of $\\neq$.");
    
    x = new Proposition("equality_reflexive", SET, "\\forall x (x = x)");
    description = "Reflexive property of equality.";
    block = new proof_block("equality_reflexive", x, backward);
    block->append_binary_operator(input({}, "Definition:equality", LeftToRight));
    block->append_binary_operator(input({1}, "Proposition:iff_reflexive", PToTrue));
    block->append_binary_operator(input({}, "Proposition:forall_true", LeftToRight, true));
    x->append(block, true);
    Proposition::addProposition(fout, x, description);
    
    fout.close();
}
