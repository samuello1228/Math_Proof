//
//  statement.cpp
//  Math_Proof
//
//  Created by Samuel on 14/9/2021.
//  Copyright © 2021 Samuel. All rights reserved.
//

#include "statement.hpp"

statement::statement(string newLabel, variable_type new_var_type, string input_latex)
{
    //check whether the contend is compound_logic
    content = dynamic_cast<compound_logic*>(expression::createFromLatex(input_latex, new_var_type));
    if(!content)
    {
        content = nullptr;
        label = "";
        cout<<"Error: the expression is not compound logic."<<endl;
        return;
    }
    
    label = newLabel;
    var_type = new_var_type;
    
    //set the forall_variable
    logic_value* x = content;
    while(true)
    {
        universal_quantifier* y = dynamic_cast<universal_quantifier*>(x);
        if(y)
        {
            forall_variable.push_back(y->var);
            x = y->operand;
        }
        else break;
    }
    
    //set the operator_latex, operand1 and operand2
    logic_binary_operator_logic_logic* y = dynamic_cast<logic_binary_operator_logic_logic*>(x);
    if(y)
    {
        if(y->operator_latex == "\\overset{\\operatorname{def}}{\\iff}" ||
           y->operator_latex == "\\iff" ||
           y->operator_latex == "\\implies"
           )
        {
            operator_latex = y->operator_latex;
            operand1 = y->operand1;
            operand2 = y->operand2;
        }
        else
        {
            operator_latex = "";
        }
    }
    else
    {
        operator_latex = "";
    }
    
    //check whether the input latex format is standard
    if(input_latex != content->getLatex())
    {
        cout<<"Error: the input latex format is not standard."<<endl;
    }
    
    //check variable
    if(!content->check_variable(var_type, {}))
    {
        cout<<"Error: Check fail for variable."<<endl;
    }
}

statement::~statement()
{
    delete content;
}

string statement::getLatex()
{
    string output = "";
    
    string quantifier_latex = "";
    if(var_type == SET)
    {
        for(long i=0;i<forall_variable.size();i++)
        {
            quantifier_latex += "\\forall ";
            quantifier_latex += forall_variable[i]->getLatex();
            quantifier_latex += " ";
        }
    }
    
    if(quantifier_latex == "")
    {
        if(operator_latex == "")
        {
            output = content->getLatex();
        }
        else
        {
            output += "& " + operand1->getLatex() + " \\\\" + "\n";
            output += operator_latex + " & " + operand2->getLatex() + "\n";
        }
    }
    else
    {
        if(operator_latex == "")
        {
            output += "& " + quantifier_latex + "( \\\\" + "\n";
            output += "& \\quad && " + content->getLatex() + " \\\\" + "\n";
            output = output + "& )" + "\n";
        }
        else
        {
            output += "& " + quantifier_latex + "( \\\\" + "\n";
            output += "& \\quad && && " + operand1->getLatex() + " \\\\" + "\n";
            output += "& \\quad && " + operator_latex + " && " + operand2->getLatex() + " \\\\" + "\n";
            output = output + "& )" + "\n";
        }
    }
    
    return output;
}

Definition::Definition(string newLabel, variable_type var_type, string x) : statement(newLabel, var_type, x)
{
}

Definition::~Definition()
{
}

void Definition::addDefinition(vector<Definition*>& All_Definition, ofstream& fout, Definition* x)
{
    //check whether the label is distinct
    for(long i=0;i<All_Definition.size();i++)
    {
        if(x->label == All_Definition[i]->label)
        {
            cout<<"Error: the label is not distinct: "<<x->label<<endl;
            return;
        }
    }
    
    All_Definition.push_back(x);
    
    cout<< "Definition:" << x->label <<endl;
    cout<< x->content->getLatex() <<endl;
    cout<<endl;
    
    //write to file
    fout<<"\\begin{defn}"<<endl;
    fout<<"\\label{Definition:"<<x->label<<"}"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<< x->getLatex();
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{defn}"<<endl;
    fout<<endl;
}

Axiom::Axiom(string newLabel, variable_type var_type, string x) : statement(newLabel, var_type, x)
{
}

Axiom::~Axiom()
{
}

void Axiom::addAxiom(vector<Axiom*>& All_Axiom, ofstream& fout, Axiom* x)
{
    //check whether the label is distinct
    for(long i=0;i<All_Axiom.size();i++)
    {
        if(x->label == All_Axiom[i]->label)
        {
            cout<<"Error: the label is not distinct: "<<x->label<<endl;
            return;
        }
    }
    
    All_Axiom.push_back(x);
    
    cout<< "Axiom:" << x->label <<endl;
    cout<< x->content->getLatex() <<endl;
    cout<<endl;
    
    //write to file
    fout<<"\\begin{axm}"<<endl;
    fout<<"\\label{Axiom:"<<x->label<<"}"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<< x->getLatex();
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{axm}"<<endl;
    fout<<endl;
}

Proposition::Proposition(string newLabel, variable_type var_type, string x) : statement(newLabel, var_type, x)
{
}

Proposition::~Proposition()
{
}

void Proposition::addProposition(vector<Proposition*>& All_Proposition, ofstream& fout, Proposition* x)
{
    //check whether the label is distinct
    for(long i=0;i<All_Proposition.size();i++)
    {
        if(x->label == All_Proposition[i]->label)
        {
            cout<<"Error: the label is not distinct: "<<x->label<<endl;
            return;
        }
    }
    
    All_Proposition.push_back(x);
    
    cout<< "Proposition:" << x->label <<endl;
    cout<< x->content->getLatex() <<endl;
    cout<<endl;
    
    //write to file
    fout<<"\\begin{prop}"<<endl;
    fout<<"\\label{Proposition:"<<x->label<<"}"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<< x->getLatex();
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{prop}"<<endl;
    fout<<endl;
}
