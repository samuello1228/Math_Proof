//
//  logic.cpp
//  Math_Proof
//
//  Created by Samuel on 19/9/2021.
//  Copyright © 2021 Samuel. All rights reserved.
//

#include "logic.hpp"

void logic(vector<Definition*>& All_Definition, vector<Axiom*>& All_Axiom, vector<Proposition*>& All_Proposition)
{
    ofstream fout;
    fout.open("logic.tex");
    
    //Definition of Proposition
    fout<<"\\chapter{Logic}"<<endl;
    fout<<"\\begin{defn}"<<endl;
    fout<<"Proposition is a statement that is either true or false, but not both."<<endl;
    fout<<"\\end{defn}"<<endl;
    fout<<endl;
    
    fout<<"\\section{Logical operations}"<<endl;
    //Definition of NOT
    fout<<"\\subsection{Definition of $\\lnot$}"<<endl;
    Definition::addDefinition(All_Definition, fout, new Definition("lnot_True", LOGIC,"(\\lnot(\\text{True})) \\overset{\\operatorname{def}}{\\iff} \\text{False}"));
    Definition::addDefinition(All_Definition, fout, new Definition("lnot_False", LOGIC,"(\\lnot(\\text{False})) \\overset{\\operatorname{def}}{\\iff} \\text{True}"));
    
    //Definition of OR
    fout<<"\\subsection{Definition of $\\lor$}"<<endl;
    Definition::addDefinition(All_Definition, fout, new Definition("lor_True_True", LOGIC,"((\\text{True}) \\lor (\\text{True})) \\overset{\\operatorname{def}}{\\iff} \\text{True}"));
    Definition::addDefinition(All_Definition, fout, new Definition("lor_True_False", LOGIC,"((\\text{True}) \\lor (\\text{False})) \\overset{\\operatorname{def}}{\\iff} \\text{True}"));
    Definition::addDefinition(All_Definition, fout, new Definition("lor_False_True", LOGIC,"((\\text{False}) \\lor (\\text{True})) \\overset{\\operatorname{def}}{\\iff} \\text{True}"));
    Definition::addDefinition(All_Definition, fout, new Definition("lor_False_False", LOGIC,"((\\text{False}) \\lor (\\text{False})) \\overset{\\operatorname{def}}{\\iff} \\text{False}"));
    
    //Definition of AND
    fout<<"\\subsection{Definition of $\\land$}"<<endl;
    Definition::addDefinition(All_Definition, fout, new Definition("land_True_True", LOGIC,"((\\text{True}) \\land (\\text{True})) \\overset{\\operatorname{def}}{\\iff} \\text{True}"));
    Definition::addDefinition(All_Definition, fout, new Definition("land_True_False", LOGIC,"((\\text{True}) \\land (\\text{False})) \\overset{\\operatorname{def}}{\\iff} \\text{False}"));
    Definition::addDefinition(All_Definition, fout, new Definition("land_False_True", LOGIC,"((\\text{False}) \\land (\\text{True})) \\overset{\\operatorname{def}}{\\iff} \\text{False}"));
    Definition::addDefinition(All_Definition, fout, new Definition("land_False_False", LOGIC,"((\\text{False}) \\land (\\text{False})) \\overset{\\operatorname{def}}{\\iff} \\text{False}"));
    
    //Definition of iff
    fout<<"\\subsection{Definition of $\\iff$}"<<endl;
    Definition::addDefinition(All_Definition, fout, new Definition("iff", LOGIC,"\\forall x \\forall y ((x \\iff y) \\overset{\\operatorname{def}}{\\iff} ((x \\land y) \\lor ((\\lnot x) \\land (\\lnot y))))"));
    
    //Definition of implies
    fout<<"\\subsection{Definition of $\\implies$}"<<endl;
    Definition::addDefinition(All_Definition, fout, new Definition("implies", LOGIC,"\\forall x \\forall y ((x \\implies y) \\overset{\\operatorname{def}}{\\iff} ((\\lnot x) \\lor y))"));
    
    fout.close();
}
