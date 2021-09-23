//
//  statement.cpp
//  Math_Proof
//
//  Created by Samuel on 14/9/2021.
//  Copyright © 2021 Samuel. All rights reserved.
//

#include "statement.hpp"

statement::statement(string newLabel)
{
    label = newLabel;
}

statement::~statement()
{
}

Definition::Definition(string newLabel, variable_type var_type, string x) : statement(newLabel)
{
    compound_logic* y = dynamic_cast<compound_logic*>(expression::createFromLatex(x, var_type));
    
    if(y) content = y;
    else cout<<"Error: the expression is not compound logic."<<endl;
}

Definition::~Definition()
{
    delete content;
}

string Definition::getLatex()
{
    string output = "";
    
    string quantifier_latex = "";
    logic_value* x = content;
    while(true)
    {
        universal_quantifier* y = dynamic_cast<universal_quantifier*>(x);
        if(y)
        {
            quantifier_latex += "\\forall ";
            quantifier_latex += y->var->getLatex();
            quantifier_latex += " ";
            x = y->operand;
        }
        else break;
    }
    
    string operator_latex = "";
    string operand1;
    string operand2;
    logic_binary_operator_logic_logic* y = dynamic_cast<logic_binary_operator_logic_logic*>(x);
    if(y)
    {
        if(y->operator_latex == "\\overset{\\operatorname{def}}{\\iff}")
        {
            operator_latex = y->operator_latex;
            operand1 = y->operand1->getLatex();
            operand2 = y->operand2->getLatex();
        }
    }
    
    if(quantifier_latex == "")
    {
        if(operator_latex == "")
        {
            output = x->getLatex();
        }
        else
        {
            output += "& " + operand1 + " \\\\" + "\n";
            output += operator_latex + " & " + operand2 + "\n";
        }
    }
    else
    {
        if(operator_latex == "")
        {
            output += "& " + quantifier_latex + "( \\\\" + "\n";
            output += "& \\quad && " + x->getLatex() + " \\\\" + "\n";
            output = output + "& )" + "\n";
        }
        else
        {
            output += "& " + quantifier_latex + "( \\\\" + "\n";
            output += "& \\quad && && " + operand1 + " \\\\" + "\n";
            output += "& \\quad && " + operator_latex + " && " + operand2 + " \\\\" + "\n";
            output = output + "& )" + "\n";
        }
    }
    
    return output;
}

void Definition::addDefinition(vector<Definition*>& All_Definition, ofstream& fout, Definition* x)
{
    All_Definition.push_back(x);
    
    cout<< "Definition:" << x->label <<endl;
    cout<< x->content->getLatex() <<endl;
    cout<<endl;
    
    fout<<"\\begin{defn}"<<endl;
    fout<<"\\label{Definition:"<<x->label<<"}"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<< x->getLatex();
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{defn}"<<endl;
    fout<<endl;
}

Axiom::Axiom(string newLabel, compound_logic* x) : statement(newLabel)
{
    content = x;
}

Axiom::~Axiom()
{
    delete content;
}

Proposition::Proposition(string newLabel, compound_logic* x) : statement(newLabel)
{
    content = x;
}

Proposition::~Proposition()
{
    delete content;
}
