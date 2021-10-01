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
    //check whether the contend is logic_value
    content = dynamic_cast<logic_value*>(expression::createFromLatex(input_latex, new_var_type));
    if(!content)
    {
        content = nullptr;
        label = "";
        cout<<"Error: the expression is not logic_value."<<endl;
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
    content = dynamic_cast<logic_value*>(x);
    if(!content)
    {
        content = nullptr;
        label = "";
        cout<<"Error: the expression is not logic_value."<<endl;
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
        }
        else
        {
            binary_operator = nullptr;
        }
    }
    else
    {
        binary_operator = nullptr;
    }
    
    //check variable
    if(!content->check_variable(var_type, {}))
    {
        cout<<"Error: Check fail for variable."<<endl;
    }
}

logic_value* statement::get_expression_without_forall_variable()
{
    logic_value* x = content;
    while(true)
    {
        if(universal_quantifier* y = dynamic_cast<universal_quantifier*>(x))
        {
            x = y->operand;
        }
        else break;
    }
    
    return x;
}

void statement::find_all_path_of_variable(bool isPrint)
{
    logic_value*x = get_expression_without_forall_variable();
    
    vector<int> type;
    //0 for path_of_variable
    //1 for path_of_variable_operand1
    //2 for path_of_variable_operand2
    type.push_back(0);
    if(binary_operator)
    {
        type.push_back(1);
        type.push_back(2);
    }
    
    for(long i=0;i<type.size();i++)
    {
        bool isFound = true;
        for(long j=0;j<forall_variable.size();j++)
        {
            vector<vector<int> > all_path;
            if(i==0) x->find_path_of_variable(forall_variable[j], {}, all_path);
            else if(i==1) binary_operator->operand1->find_path_of_variable(forall_variable[j], {}, all_path);
            else if(i==2) binary_operator->operand2->find_path_of_variable(forall_variable[j], {}, all_path);
            
            if(all_path.size() == 0)
            {
                if(i==0) cout<<"Error: Cannot find path of the variable: "<<forall_variable[j]->getLatex()<<endl;
                else if(i==1)
                {
                    isFound = false;
                    if(isPrint) cout<<"Info: Cannot do auto substitution for LeftToRight direction."<<endl;
                    path_of_variable_operand1.clear();
                    break;
                }
                else if(i==2)
                {
                    isFound = false;
                    if(isPrint) cout<<"Info: Cannot do auto substitution for RightToLeft direction."<<endl;
                    path_of_variable_operand2.clear();
                    break;
                }
            }
            
            //find the minimum path
            vector<int> min_path = all_path[0];
            long min_depth = min_path.size();
            for(long k=0;k<all_path.size();k++)
            {
                if(all_path[k].size() < min_depth)
                {
                    min_path = all_path[k];
                    min_depth = min_path.size();
                }
            }
            
            if(i==0) path_of_variable.push_back(min_path);
            else if(i==1) path_of_variable_operand1.push_back(min_path);
            else if(i==2) path_of_variable_operand2.push_back(min_path);
        }
        
        if(!isFound) continue;
        
        if(isPrint)
        {
            for(long j=0;j<forall_variable.size();j++)
            {
                cout<<"The path ";
                if(i==1) cout<<"in operand1 ";
                else if(i==2) cout<<"in operand2 ";
                cout<<"of the variable "<<forall_variable[j]->getLatex()<<" is {";
                if(i==0) for(long k=0;k<path_of_variable[j].size();k++) cout<<path_of_variable[j][k]<<" ";
                else if(i==1) for(long k=0;k<path_of_variable_operand1[j].size();k++) cout<<path_of_variable_operand1[j][k]<<" ";
                else if(i==2) for(long k=0;k<path_of_variable_operand2[j].size();k++) cout<<path_of_variable_operand2[j][k]<<" ";
                cout<<"}"<<endl;
            }
        }
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
        if(binary_operator == nullptr)
        {
            output = content->getLatex();
        }
        else
        {
            output += "& " + binary_operator->operand1->getLatex() + " \\\\" + "\n";
            output += binary_operator->operator_latex + " & " + binary_operator->operand2->getLatex() + "\n";
        }
    }
    else
    {
        if(binary_operator == nullptr)
        {
            output += "& " + quantifier_latex + "( \\\\" + "\n";
            output += "& \\quad && " + content->getLatex() + " \\\\" + "\n";
            output = output + "& )" + "\n";
        }
        else
        {
            output += "& " + quantifier_latex + "( \\\\" + "\n";
            output += "& \\quad && && " + binary_operator->operand1->getLatex() + " \\\\" + "\n";
            output += "& \\quad && " + binary_operator->operator_latex + " && " + binary_operator->operand2->getLatex() + " \\\\" + "\n";
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

void statement::delete_the_last_universal_quantifier()
{
    universal_quantifier* x = nullptr;
    universal_quantifier* y = dynamic_cast<universal_quantifier*>(content);
    if(!y)
    {
        cout<<"Error: There does not exist any universal quantifier. cannot delete."<<endl;
        return;
    }
    
    while(true)
    {
        if(universal_quantifier* z = dynamic_cast<universal_quantifier*>(y->operand))
        {
            x = y;
            y = z;
        }
        else break;
    }
    
    if(x == nullptr)
    {
        content = binary_operator;
    }
    else
    {
        x->operand = binary_operator;
    }
    
    y->operand = dynamic_cast<logic_value*>(expression::createFromLatex("\\text{True}", LOGIC));
    delete y;
    forall_variable.erase(forall_variable.end() -1);
}

void statement::collapse_to_operand(int p)
{
    if(binary_operator == nullptr)
    {
        cout<<"Error: There does not exist a binary operator. cannot collapse."<<endl;
        return;
    }
    
    universal_quantifier* x = nullptr;
    universal_quantifier* y = dynamic_cast<universal_quantifier*>(content);
    while(true)
    {
        if(y)
        {
            x = y;
            y = dynamic_cast<universal_quantifier*>(y->operand);
        }
        else break;
    }
    
    logic_value* operand = nullptr;
    if(p==1) operand = binary_operator->operand1;
    if(p==2) operand = binary_operator->operand2;
    
    if(x == nullptr)
    {
        content = operand;
    }
    else
    {
        x->operand = operand;
    }
    
    if(p==1) binary_operator->operand1 = dynamic_cast<logic_value*>(expression::createFromLatex("\\text{True}", LOGIC));
    if(p==2) binary_operator->operand2 = dynamic_cast<logic_value*>(expression::createFromLatex("\\text{True}", LOGIC));
    delete binary_operator;
    binary_operator = nullptr;
}

void statement::collapse_to_true()
{
    universal_quantifier* x = nullptr;
    universal_quantifier* y = dynamic_cast<universal_quantifier*>(content);
    while(true)
    {
        if(y)
        {
            x = y;
            y = dynamic_cast<universal_quantifier*>(y->operand);
        }
        else break;
    }
    
    if(x == nullptr)
    {
        delete content;
        content = dynamic_cast<logic_value*>(expression::createFromLatex("\\text{True}", LOGIC));
    }
    else
    {
        delete x->operand;
        x->operand = dynamic_cast<logic_value*>(expression::createFromLatex("\\text{True}", LOGIC));
    }
}

void statement::upgrade_to_true(direction dir)
{
    universal_quantifier* x = nullptr;
    universal_quantifier* y = dynamic_cast<universal_quantifier*>(content);
    while(true)
    {
        if(y)
        {
            x = y;
            y = dynamic_cast<universal_quantifier*>(y->operand);
        }
        else break;
    }
    
    logic_value* True = dynamic_cast<logic_value*>(expression::createFromLatex("\\text{True}", LOGIC));
    if(x == nullptr)
    {
        if(dir == LeftToRight) binary_operator = new logic_binary_operator_logic_logic("\\iff", True, content);
        if(dir == RightToLeft) binary_operator = new logic_binary_operator_logic_logic("\\iff", content, True);
        content = binary_operator;
    }
    else
    {
        if(dir == LeftToRight) binary_operator = new logic_binary_operator_logic_logic("\\iff", True, x->operand);
        if(dir == RightToLeft) binary_operator = new logic_binary_operator_logic_logic("\\iff", x->operand, True);
        x->operand = binary_operator;
    }
}

statement* statement::apply_binary_operator(statement* source, vector<int> path, vector<substitution*> sub, direction dir, bool isPrint)
{
    if(binary_operator == nullptr)
    {
        cout<<"Error: cannot use applyLeftToRight."<<endl;
        return nullptr;
    }
    
    //print substitution
    if(isPrint)
    {
        cout<<"Substitution:"<<endl;
        for(long i=0;i<sub.size();i++)
        {
            cout<<sub[i]->x->getLatex()<<" is replaced by "<<sub[i]->y->getLatex()<<endl;
        }
        cout<<endl;
    }
    
    //get external dependence of source part
    vector<variable*> external_dependence_source_part;
    source->content->getPartExternalDependence(path, external_dependence_source_part);
    if(isPrint)
    {
        cout<<"External dependence of source part:"<<endl;
        for(long i=0;i<external_dependence_source_part.size();i++)
        {
            cout<<external_dependence_source_part[i]->getLatex()<<" ";
        }
        cout<<endl;
    }
    
    //get all dependence of source part
    expression* source_part = source->content->getPart(path);
    vector<variable*> all_dependence_source_part = external_dependence_source_part;
    source_part->getInternalDependence(all_dependence_source_part);
    if(isPrint)
    {
        cout<<"All dependence of source part:"<<endl;
        for(long i=0;i<all_dependence_source_part.size();i++)
        {
            cout<<all_dependence_source_part[i]->getLatex()<<" ";
        }
        cout<<endl;
    }
    
    //get internal dependence of law
    vector<variable*> internal_dependence_law;
    content->getInternalDependence(internal_dependence_law);
    if(isPrint)
    {
        cout<<"Internal dependence of law:"<<endl;
        for(long i=0;i<internal_dependence_law.size();i++)
        {
            cout<<internal_dependence_law[i]->getLatex()<<" ";
        }
        cout<<endl;
    }
    
    //create replacement by exclusion
    vector<substitution*> replacement = createReplacement(internal_dependence_law, all_dependence_source_part);
    if(isPrint)
    {
        cout<<"Replacement:"<<endl;
        for(long i=0;i<replacement.size();i++)
        {
            cout<<replacement[i]->x->getLatex()<<" is replaced by "<<replacement[i]->y->getLatex()<<endl;
        }
        cout<<endl;
    }
    
    //do replacement for law_copy
    logic_value* law_copy = dynamic_cast<logic_value*>(content->getCopy());
    law_copy->replace_variable(replacement);
    if(isPrint) cout<<law_copy->getLatex()<<endl;
    
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
    for(long i = external_dependence_source_part.size()-1; i>=0; i--)
    {
        variable* variable_copy = dynamic_cast<variable*>(external_dependence_source_part[i]->getCopy());
        law_copy = new universal_quantifier(variable_copy, law_copy);
    }
    if(isPrint) cout<<law_copy->getLatex()<<endl;
    
    //do substitution
    expression* x = expression::substitute_forall_variable(law_copy, sub);
    if(isPrint) cout<<x->getLatex()<<endl<<endl;
    
    //delete sub
    for(long i=0;i<sub.size();i++)
    {
        delete sub[i];
    }
    
    //assemble to the original source
    statement* step = new statement("", source->var_type, x);
    if(isPrint) cout<<"Do the assembly:"<<endl;
    while(true)
    {
        if(path.size() == 0) break;
        
        int p = path[path.size() -1];
        path.erase(path.end() -1);
        
        bool isChanged = expression::assemble(step, source->content->getPart(path), p, source->forall_variable);
        if(isPrint && isChanged) cout<<step->content->getLatex()<<endl;
    }
    if(isPrint) cout<<endl;
    
    //for direction Right to Left
    if(dir == RightToLeft)
    {
        if(step->binary_operator->operator_latex == "\\overset{\\operatorname{def}}{\\iff}" ||
           step->binary_operator->operator_latex == "\\iff" )
        {
            //swap
            logic_value* temp = step->binary_operator->operand1;
            step->binary_operator->operand1 = step->binary_operator->operand2;
            step->binary_operator->operand2 = temp;
            if(isPrint)
            {
                cout<<"Swap two operands for the direction RightToLeft"<<endl;
                cout<<step->content->getLatex()<<endl;
            }
        }
        else
        {
            cout<<"Error: cannot apply for the RightToLeft direction."<<endl;
        }
    }
    
    //check whether the step->operand1 is equal to the source
    statement* copy_step_1 = step->getCopy();
    copy_step_1->collapse_to_operand(1);
    if(!copy_step_1->content->isEqual(source->content))
    {
        cout<<"Error: the operand1 of step and the source are different."<<endl;
    }
    delete copy_step_1;
    
    //check forall_variable
    if(step->forall_variable.size() != source->forall_variable.size())
    {
        cout<<"Error: The forall_variable doese not matched."<<endl;
    }
    
    for(long i=0;i<step->forall_variable.size();i++)
    {
        if(! step->forall_variable[i]->isEqual(source->forall_variable[i]))
        {
            cout<<"Error: The forall_variable does not matched."<<endl;
        }
    }
    
    return step;
}

vector<Definition*> Definition::All_Definition;
Definition::Definition(string newLabel, variable_type var_type, string x) : statement(newLabel, var_type, x)
{
}

Definition::~Definition()
{
}

Definition* Definition::FindByRef(string Name)
{
    for(long i=0;i<All_Definition.size();i++)
    {
        if(All_Definition[i]->label == Name)
        {
            return All_Definition[i];
        }
    }
    return nullptr;
}

void Definition::addDefinition(ofstream& fout, Definition* x)
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
    x->find_all_path_of_variable(false);
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

vector<Axiom*> Axiom::All_Axiom;
Axiom::Axiom(string newLabel, variable_type var_type, string x) : statement(newLabel, var_type, x)
{
}

Axiom::~Axiom()
{
}

Axiom* Axiom::FindByRef(string Name)
{
    for(long i=0;i<All_Axiom.size();i++)
    {
        if(All_Axiom[i]->label == Name)
        {
            return All_Axiom[i];
        }
    }
    return nullptr;
}

void Axiom::addAxiom(ofstream& fout, Axiom* x)
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
    x->find_all_path_of_variable(false);
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

input::input(vector<int> new_relative_path, statement* new_law, direction new_dir, bool new_isFinished, bool new_isPrint)
{
    relative_path = new_relative_path;
    
    law = new_law;
    law_label = "";
    
    dir = new_dir;
    
    sub_type = automatic;
    
    isFinished = new_isFinished;
    isPrint = new_isPrint;
}

input::input(vector<int> new_relative_path, statement* new_law, direction new_dir, vector<vector<int> > sub, bool new_isFinished, bool new_isPrint)
{
    relative_path = new_relative_path;
    
    law = new_law;
    law_label = "";
    
    dir = new_dir;
    
    sub_type = source_specified;
    source_specified_substitution = sub;
    
    isFinished = new_isFinished;
    isPrint = new_isPrint;
}

input::input(vector<int> new_relative_path, statement* new_law, direction new_dir, vector<substitution*> sub, bool new_isFinished, bool new_isPrint)
{
    relative_path = new_relative_path;
    
    law = new_law;
    law_label = "";
    
    dir = new_dir;
    
    sub_type = full;
    full_substitution = sub;
    
    isFinished = new_isFinished;
    isPrint = new_isPrint;
}

proof_block::proof_block(string newLabel, statement* x, proof_method new_method)
{
    label = newLabel;
    target = x->getCopy();
    method = new_method;
}

proof_block::~proof_block()
{
    delete target;
    for(long i=0;i<chain_of_deductive.size();i++)
    {
        delete chain_of_deductive[i];
    }
}

statement* proof_block::get_next_source()
{
    statement* source = nullptr;
    if(chain_of_deductive.size() == 0)
    {
        if(method == deduction)
        {
            source = target->getCopy();
            source->collapse_to_operand(1);
        }
        else if(method == direct)
        {
            source = target->getCopy();
            source->collapse_to_true();
        }
        else if(method == backward)
        {
            source = target->getCopy();
        }
    }
    else
    {
        long last_index = chain_of_deductive.size() -1;
        source = chain_of_deductive[last_index]->getCopy();
        source->collapse_to_operand(2);
    }
    
    return source;
}

void proof_block::check_finished(statement* step)
{
    if(method == deduction || method == direct || method == backward)
    {
        statement* copy_target_2 = target->getCopy();
        if(method == deduction) copy_target_2->collapse_to_operand(2);
        if(method == backward) copy_target_2->collapse_to_true();
        
        statement* copy_step_2 = step->getCopy();
        copy_step_2->collapse_to_operand(2);
        if(!copy_step_2->content->isEqual(copy_target_2->content))
        {
            if(method == deduction) cout<<"Error: The operand2 does not matched the operand2 of target."<<endl;
            if(method == direct) cout<<"Error: The operand2 does not matched the target."<<endl;
            if(method == backward) cout<<"Error: The operand2 is not True."<<endl;
        }
        
        delete copy_target_2;
        delete copy_step_2;
    }
}

void proof_block::append_binary_operator(input x)
{
    if(x.isPrint) cout<<"New step:"<<endl;
    statement* source = get_next_source();
    
    if(x.isPrint)
    {
        cout<<"source:"<<endl;
        cout<<source->content->getLatex()<<endl;
    }
    
    //fill the x->law
    if(x.law == nullptr)
    {
        
    }
    else
    {

    }
    
    if(method == direct && chain_of_deductive.size() == 0)
    {
        x.law = x.law->getCopy();
        x.law->upgrade_to_true(LeftToRight);
    }
    
    if(x.isPrint)
    {
        cout<<"law:"<<endl;
        cout<<x.law->content->getLatex()<<endl;
        cout<<endl;
    }
    
    //fill the absolute_path
    vector<int> absolute_path;
    for(long i=0;i<source->forall_variable.size();i++)
    {
        absolute_path.push_back(1);
    }
    for(long i=0;i<x.relative_path.size();i++)
    {
        absolute_path.push_back(x.relative_path[i]);
    }
    
    //fill the x->full_substitution
    if(method == direct && chain_of_deductive.size() == 0)
    {
        if(x.sub_type != full)
        {
            cout<<"Error: cannot do this. please use the full substitution."<<endl;
            return;
        }
    }
    else
    {
        if(x.sub_type == source_specified)
        {
            expression* source_part = source->content->getPart(absolute_path);
            x.full_substitution = createSubstitution(x.law->forall_variable, source_part, x.source_specified_substitution);
        }
        else if(x.sub_type == automatic)
        {
            vector<vector<int> > substitute_path = {};
            if(x.law->forall_variable.size() != 0)
            {
                if(x.dir == LeftToRight)
                {
                    if(x.law->path_of_variable_operand1.size() == 0)
                    {
                        cout<<"Error: cannot do automatic substitution."<<endl;
                        return;
                    }
                    substitute_path = x.law->path_of_variable_operand1;
                }
                else if(x.dir == RightToLeft)
                {
                    if(x.law->path_of_variable_operand2.size() == 0)
                    {
                        cout<<"Error: cannot do automatic substitution."<<endl;
                        return;
                    }
                    substitute_path = x.law->path_of_variable_operand2;
                }
            }
            
            expression* source_part = source->content->getPart(absolute_path);
            x.full_substitution = createSubstitution(x.law->forall_variable, source_part, substitute_path);
        }
    }
    
    statement* step = x.law->apply_binary_operator(source, absolute_path, x.full_substitution, x.dir, x.isPrint);
    delete source;
    
    if(method == direct && chain_of_deductive.size() == 0) delete x.law;
    
    if(step->binary_operator->operator_latex == "\\implies" && target->binary_operator->operator_latex == "\\iff")
    {
        cout<<"Error: The deduction cannot work for \\iff."<<endl;
        return;
    }
    
    if(x.isFinished) check_finished(step);
    chain_of_deductive.push_back(step);
    if(dynamic_cast<Definition*>(x.law)) ref_type.push_back("Definition");
    if(dynamic_cast<Axiom*>(x.law)) ref_type.push_back("Axiom");
    if(dynamic_cast<Proposition*>(x.law)) ref_type.push_back("Proposition");
    ref.push_back(x.law->label);
}

vector<Proposition*> Proposition::All_Proposition;
Proposition::Proposition(string newLabel, variable_type var_type, string x) : statement(newLabel, var_type, x)
{
}

Proposition::~Proposition()
{
    for(long i=0;i<proof.size();i++)
    {
        delete proof[i];
    }
}

Proposition* Proposition::FindByRef(string Name)
{
    for(long i=0;i<All_Proposition.size();i++)
    {
        if(All_Proposition[i]->label == Name)
        {
            return All_Proposition[i];
        }
    }
    return nullptr;
}

void Proposition::addProposition(ofstream& fout, Proposition* x, string description)
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
    x->find_all_path_of_variable(false);
    cout<<endl;
    
    //write to file
    fout<<"\\begin{prop}"<<endl;
    fout<<"\\label{Proposition:"<<x->label<<"}"<<endl;
    if(description != "") fout<< description <<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<< x->getLatex();
    fout<<"\\end{align*}"<<endl;
    
    //Proof
    for(long i=0;i<x->proof.size();i++)
    {
        fout<< "Proof of Proposition \\ref{Proposition:" << x->proof[i]->label << "}" <<endl;
        fout<<"\\begin{align*}"<<endl;
        
        string quantifier_latex = "";
        if(x->var_type == SET)
        {
            for(long j=0;j<x->forall_variable.size();j++)
            {
                quantifier_latex += "\\forall ";
                quantifier_latex += x->forall_variable[j]->getLatex();
                quantifier_latex += " ";
            }
            fout << "& " << quantifier_latex << "( \\\\" <<endl;
        }
        
        for(long j=0;j<x->proof[i]->chain_of_deductive.size();j++)
        {
            statement* element = x->proof[i]->chain_of_deductive[j];
            string ref_type = x->proof[i]->ref_type[j];
            string ref = x->proof[i]->ref[j];
            
            if(quantifier_latex == "")
            {
                if(j==0) fout << "& " << element->binary_operator->operand1->getLatex() << " \\\\" <<endl;
                fout<<element->binary_operator->operator_latex << " & " << element->binary_operator->operand2->getLatex() <<endl;
            }
            else
            {
                if(j==0) fout << "& \\quad && && " << element->binary_operator->operand1->getLatex() << " \\\\" <<endl;
                fout << "& \\quad && " << element->binary_operator->operator_latex << " && " << element->binary_operator->operand2->getLatex() <<endl;
            }
            fout<< "&& \\text{" << ref_type << " \\ref{" << ref_type << ":" << ref << "}} \\\\" <<endl;
        }
        
        if(quantifier_latex != "") fout << "& )" <<endl;
        fout<<"\\end{align*}"<<endl;
    }
    
    fout<<"\\end{prop}"<<endl;
    fout<<endl;
}

void Proposition::append(proof_block* x, bool isFinished)
{
    if(isFinished)
    {
        if(!x->target->content->isEqual(content))
        {
            cout<<"Error: The proof does not matched the content."<<endl;
        }
    }
    
    proof.push_back(x);
}
