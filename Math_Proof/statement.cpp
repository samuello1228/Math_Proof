//
//  statement.cpp
//  Math_Proof
//
//  Created by Samuel on 14/9/2021.
//  Copyright © 2021 Samuel. All rights reserved.
//

#include "statement.hpp"

vector<substitution*> createReplacement(vector<variable*> original_variable, vector<variable*> exclude)
{
    vector<substitution*> replacement;
    char letter = 'a';
    int index = 0;
    while(true)
    {
        if(index == original_variable.size()) break;
        
        if(letter == '{')
        {
            cout<<"Error: all letter have been already used."<<endl;
            return replacement;
        }
        
        string latex;
        latex.push_back(letter);
        
        //exclude the variable
        bool duplicate = false;
        for(long i=0;i<exclude.size();i++)
        {
            if(latex == exclude[i]->latex)
            {
                duplicate = true;
            }
        }
        
        if(duplicate)
        {
            letter += 1;
            continue;
        }
        
        //create substitution
        variable* x = dynamic_cast<variable*>(original_variable[index]->getCopy());
        substitution* element = new substitution(x, original_variable[index]->getCopy());
        variable* y = dynamic_cast<variable*>(element->y);
        y->latex = latex;
        replacement.push_back(element);
        
        index++;
        letter += 1;
    }
    
    return replacement;
}

vector<substitution*> createSubstitution(vector<variable*> forall_variable, expression* target_part, vector<vector<int> > path)
{
    vector<substitution*> sub;
    for(long i=0;i<forall_variable.size();i++)
    {
        variable* x = dynamic_cast<variable*>(forall_variable[i]->getCopy());
        expression* y = target_part->getPart(path[i])->getCopy();
        sub.push_back(new substitution(x,y));
    }
    
    return sub;
}

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
    
    //check whether the input latex format is standard
    if(input_latex != content->getLatex())
    {
        cout<<"Error: the input latex format is not standard."<<endl;
    }
    
    constructor_aux();
}

statement::statement(string newLabel, variable_type new_var_type, expression* x)
{
    content = dynamic_cast<compound_logic*>(x);
    if(!content)
    {
        content = nullptr;
        label = "";
        cout<<"Error: the expression is not compound logic."<<endl;
        return;
    }
    
    label = newLabel;
    var_type = new_var_type;
    constructor_aux();
}

void statement::constructor_aux()
{
    //set the forall_variable
    logic_value* x = content;
    while(true)
    {
        if(universal_quantifier* y = dynamic_cast<universal_quantifier*>(x))
        {
            forall_variable.push_back(y->var);
            x = y->operand;
        }
        else break;
    }
    
    //set the binary_operator, operator_latex
    binary_operator = dynamic_cast<logic_binary_operator_logic_logic*>(x);
    if(binary_operator)
    {
        if(binary_operator->operator_latex == "\\overset{\\operatorname{def}}{\\iff}" ||
           binary_operator->operator_latex == "\\iff" ||
           binary_operator->operator_latex == "\\implies"
           )
        {
            operator_latex = binary_operator->operator_latex;
        }
        else
        {
            binary_operator = nullptr;
            operator_latex = "";
        }
    }
    else
    {
        binary_operator = nullptr;
        operator_latex = "";
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
            output += "& " + binary_operator->operand1->getLatex() + " \\\\" + "\n";
            output += operator_latex + " & " + binary_operator->operand2->getLatex() + "\n";
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
            output += "& \\quad && && " + binary_operator->operand1->getLatex() + " \\\\" + "\n";
            output += "& \\quad && " + operator_latex + " && " + binary_operator->operand2->getLatex() + " \\\\" + "\n";
            output = output + "& )" + "\n";
        }
    }
    
    return output;
}

statement* statement::getCopy()
{
    statement* output = new statement(label, var_type, content->getCopy());
    return output;
}

statement* statement::apply_binary_operator(statement* target, vector<int> path, vector<vector<int> > substitute_path, direction dir, bool isPrint)
{
    if(operator_latex == "")
    {
        cout<<"Error: cannot use applyLeftToRight."<<endl;
        return nullptr;
    }
    
    //create substitution
    expression* target_part = target->content->getPart(path);
    vector<substitution*> sub = createSubstitution(forall_variable, target_part, substitute_path);
    if(isPrint)
    {
        cout<<"Substitution:"<<endl;
        for(long i=0;i<sub.size();i++)
        {
            cout<<sub[i]->x->getLatex()<<" is replaced by "<<sub[i]->y->getLatex()<<endl;
        }
        cout<<endl;
    }
    
    //get external dependence of target part
    vector<variable*> external_dependence_target_part;
    target->content->getPartExternalDependence(path, external_dependence_target_part);
    if(isPrint)
    {
        cout<<"External dependence of target part:"<<endl;
        for(long i=0;i<external_dependence_target_part.size();i++)
        {
            cout<<external_dependence_target_part[i]->getLatex()<<" ";
        }
        cout<<endl;
    }
    
    //get all dependence of target part
    vector<variable*> all_dependence_target_part = external_dependence_target_part;
    target_part->getInternalDependence(all_dependence_target_part);
    if(isPrint)
    {
        cout<<"All dependence of target part:"<<endl;
        for(long i=0;i<all_dependence_target_part.size();i++)
        {
            cout<<all_dependence_target_part[i]->getLatex()<<" ";
        }
        cout<<endl;
    }
    
    //get internal dependence of source
    vector<variable*> internal_dependence_source;
    content->getInternalDependence(internal_dependence_source);
    if(isPrint)
    {
        cout<<"Internal dependence of source:"<<endl;
        for(long i=0;i<internal_dependence_source.size();i++)
        {
            cout<<internal_dependence_source[i]->getLatex()<<" ";
        }
        cout<<endl;
    }
    
    //create replacement by exclusion
    vector<substitution*> replacement = createReplacement(internal_dependence_source,all_dependence_target_part);
    if(isPrint)
    {
        cout<<"Replacement:"<<endl;
        for(long i=0;i<replacement.size();i++)
        {
            cout<<replacement[i]->x->getLatex()<<" is replaced by "<<replacement[i]->y->getLatex()<<endl;
        }
        cout<<endl;
    }
    
    //do replacement for source_copy
    compound_logic* source_copy = dynamic_cast<compound_logic*>(content->getCopy());
    source_copy->replace_variable(replacement);
    if(isPrint) cout<<source_copy->getLatex()<<endl;
    
    //do replacement for sub
    for(long i=0;i<sub.size();i++)
    {
        for(long j=0;j<replacement.size();j++)
        {
            if(replacement[j]->x->isEqual(sub[i]->x))
            {
                delete sub[i]->x;
                sub[i]->x = dynamic_cast<variable*>(replacement[j]->y->getCopy());
            }
        }
    }
    if(isPrint)
    {
        for(long i=0;i<sub.size();i++)
        {
            cout<<sub[i]->x->getLatex()<<" is replaced by "<<sub[i]->y->getLatex()<<endl;
        }
        cout<<endl;
    }
    
    //delete replacement
    for(long i=0;i<replacement.size();i++)
    {
        delete replacement[i];
    }
    
    //add universal quantifier at the beginning
    for(long i = external_dependence_target_part.size()-1; i>=0; i--)
    {
        variable* variable_copy = dynamic_cast<variable*>(external_dependence_target_part[i]->getCopy());
        source_copy = new universal_quantifier(variable_copy, source_copy);
    }
    if(isPrint) cout<<source_copy->getLatex()<<endl;

    //do substitution
    expression* x = expression::substitute_forall_variable(source_copy, sub);
    if(isPrint) cout<<x->getLatex()<<endl<<endl;
    
    //delete sub
    for(long i=0;i<sub.size();i++)
    {
        delete sub[i];
    }
    
    //assemble to the original source
    statement* output = new statement("", target->var_type, x);
    output->forall_variable.clear();
    while(true)
    {
        if(path.size() == 0) break;
        
        int p = path[path.size() -1];
        path.erase(path.end() -1);
        
        expression::assemble(output, target->content->getPart(path), p);
        if(isPrint) cout<<output->content->getLatex()<<endl;;
    }
    if(isPrint) cout<<endl;;
    
    //check whether the output->operand1 is equal to the source
    if(logic_binary_operator_logic_logic* output_content = dynamic_cast<logic_binary_operator_logic_logic*>(output->content))
    {
        if(!output_content->operand1->isEqual(target->content))
        {
            cout<<"Error: the output and the source are different."<<endl;
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
