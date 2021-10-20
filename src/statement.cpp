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

vector<substitution*> createSubstitution(vector<variable*> forall_variable, expression* source, vector<vector<int> > path)
{
    vector<substitution*> sub;
    for(long i=0;i<forall_variable.size();i++)
    {
        variable* x = dynamic_cast<variable*>(forall_variable[i]->getCopy());
        expression* y = source->getPart(path[i])->getCopy();
        sub.push_back(new substitution(x,y));
    }
    
    return sub;
}

statement::statement(string newLabel, variable_type new_var_type, string input_latex, bool isPrint)
{
    //check whether the contend is logic_value
    content = dynamic_cast<logic_value*>(expression::createFromLatex(input_latex, new_var_type, isPrint));
    if(!content)
    {
        content = nullptr;
        label = "";
        cout<<"Error: the expression is not logic_value."<<endl;
        return;
    }
    
    label = newLabel;
    
    //check whether the input latex format is standard
    if(input_latex != content->getLatex().getNormal())
    {
        cout<<"Error: the input latex format is not standard."<<endl;
    }
    
    constructor_aux();
}

statement::statement(string newLabel, expression* x)
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
    if(logic_binary_operator_logic_logic* y = dynamic_cast<logic_binary_operator_logic_logic*>(x))
    {
        if(y->operator_latex == "\\iff" ||
           y->operator_latex == "\\implies")
        {
            binary_operator_type = LOGIC;
            binary_operator_logic = y;
            binary_operator_set = nullptr;
        }
        else
        {
            binary_operator_type = None;
            binary_operator_logic = nullptr;
            binary_operator_set = nullptr;
        }
    }
    else if(logic_binary_operator_set_set* y = dynamic_cast<logic_binary_operator_set_set*>(x))
    {
        if(y->operator_latex == "=")
        {
            binary_operator_type = SET;
            binary_operator_logic = nullptr;
            binary_operator_set = y;
        }
        else
        {
            binary_operator_type = None;
            binary_operator_logic = nullptr;
            binary_operator_set = nullptr;
        }
    }
    else
    {
        binary_operator_type = None;
        binary_operator_logic = nullptr;
        binary_operator_set = nullptr;
    }
    
    //check variable
    if(!content->check_variable({}))
    {
        cout<<"Error: Check fail for variable."<<endl;
        cout<<content->getLatex().getNormal()<<endl;
    }
}

void statement::set_forall_variable(vector<variable*>& new_forall_variable, long depth)
{
    new_forall_variable.clear();
    logic_value* x = content;
    while(depth >= 1)
    {
        if(universal_quantifier* y = dynamic_cast<universal_quantifier*>(x))
        {
            new_forall_variable.push_back(y->var);
            x = y->operand;
        }
        else break;
        
        depth--;
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
    if(binary_operator_type == None)
    {
        if(isPrint) cout<<"Info: Cannot do auto substitution for all direction."<<endl;
        path_of_variable_operand1.clear();
        path_of_variable_operand2.clear();
        return;
    }
    
    //i=0 for path_of_variable_operand1
    //i=1 for path_of_variable_operand2
    for(long i=0;i<=1;i++)
    {
        bool isFound = true;
        for(long j=0;j<forall_variable.size();j++)
        {
            vector<vector<int> > all_path;
            if(i==0) get_oeprand(1)->find_path_of_variable(forall_variable[j], {}, all_path);
            else if(i==1) get_oeprand(2)->find_path_of_variable(forall_variable[j], {}, all_path);
            
            if(all_path.size() == 0)
            {
                if(i==0)
                {
                    isFound = false;
                    if(isPrint) cout<<"Info: Cannot do auto substitution for LeftToRight direction."<<endl;
                    path_of_variable_operand1.clear();
                    break;
                }
                else if(i==1)
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
            
            if(i==0) path_of_variable_operand1.push_back(min_path);
            else if(i==1) path_of_variable_operand2.push_back(min_path);
        }
        
        if(!isFound) continue;
        
        if(isPrint)
        {
            for(long j=0;j<forall_variable.size();j++)
            {
                cout<<"The path ";
                if(i==0) cout<<"in operand1 ";
                else if(i==1) cout<<"in operand2 ";
                cout<<"of the variable "<<forall_variable[j]->getLatex().getNormal()<<" is {";
                if(i==0) for(long k=0;k<path_of_variable_operand1[j].size();k++) cout<<path_of_variable_operand1[j][k]<<" ";
                else if(i==1) for(long k=0;k<path_of_variable_operand2[j].size();k++) cout<<path_of_variable_operand2[j][k]<<" ";
                cout<<"}"<<endl;
            }
        }
    }
}

statement::~statement()
{
    delete content;
}

logic_value* statement::get_binary_operator()
{
    if(binary_operator_type == LOGIC) return binary_operator_logic;
    else if(binary_operator_type == SET) return binary_operator_set;
    else
    {
        cout<<"Error: There does not exist any binary operator."<<endl;
        return nullptr;
    }
}

string statement::get_binary_operator_latex()
{
    if(binary_operator_type == LOGIC) return binary_operator_logic->operator_latex;
    else if(binary_operator_type == SET) return binary_operator_set->operator_latex;
    else
    {
        cout<<"Error: There does not exist any binary operator."<<endl;
        return "";
    }
}

expression* statement::get_oeprand(int x)
{
    if(x == 1)
    {
        if(binary_operator_type == LOGIC) return binary_operator_logic->operand1;
        else if(binary_operator_type == SET) return binary_operator_set->operand1;
        else
        {
            cout<<"Error: There does not exist any binary operator."<<endl;
            return nullptr;
        }
    }
    else if(x == 2)
    {
        if(binary_operator_type == LOGIC) return binary_operator_logic->operand2;
        else if(binary_operator_type == SET) return binary_operator_set->operand2;
        else
        {
            cout<<"Error: There does not exist any binary operator."<<endl;
            return nullptr;
        }
    }
    
    cout<<"Error: x is not 1 or 2."<<endl;
    return nullptr;
}

string statement::getLatex()
{
    string output = "";
    
    string quantifier_latex = "";
    for(long i=0;i<forall_variable.size();i++)
    {
        if(dynamic_cast<set_variable*>(forall_variable[i]))
        {
            quantifier_latex += "\\forall ";
            quantifier_latex += forall_variable[i]->getLatex().getNormal();
            quantifier_latex += " ";
        }
    }
    
    string operator_latex = "";
    if(binary_operator_type == LOGIC)
    {
        operator_latex = get_binary_operator_latex();
        if(Definition* x = dynamic_cast<Definition*>(this))
        {
            if(operator_latex == "\\iff")
            {
                operator_latex = "\\overset{\\operatorname{def}}{\\iff}";
            }
        }
    }
    else if(binary_operator_type == SET)
    {
        operator_latex = get_binary_operator_latex();
        if(Definition* x = dynamic_cast<Definition*>(this))
        {
            if(operator_latex == "=")
            {
                operator_latex = "\\overset{\\operatorname{def}}{=}";
            }
        }
    }
    
    if(quantifier_latex != "") output += "& " + quantifier_latex + "( \\\\" + "\n";
    
    if(binary_operator_type == None)
    {
        if(quantifier_latex != "") output += "& & ";
        output += get_expression_without_forall_variable()->getLatex().getNormal();
        if(quantifier_latex != "") output += " \\\\";
        output += "\n";
    }
    else
    {
        if(quantifier_latex != "") output += "& & ";
        output += "& " + get_oeprand(1)->getLatex().getNormal() + " \\\\" + "\n";
        
        if(quantifier_latex != "") output += "& & ";
        output += operator_latex + " & " + get_oeprand(2)->getLatex().getNormal();
        if(quantifier_latex != "") output += " \\\\";
        output += "\n";
    }
    
    if(quantifier_latex != "") output = output + "& )" + "\n";
    
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
        content = get_binary_operator();
    }
    else
    {
        x->operand = get_binary_operator();
    }
    
    y->operand = dynamic_cast<logic_value*>(expression::createFromLatex("\\text{True}", LOGIC));
    delete y;
    forall_variable.erase(forall_variable.end() -1);
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
        if(dir == TrueToP) binary_operator_logic = new logic_binary_operator_logic_logic("\\iff", True, content);
        if(dir == PToTrue) binary_operator_logic = new logic_binary_operator_logic_logic("\\iff", content, True);
        content = binary_operator_logic;
        binary_operator_type = LOGIC;
        binary_operator_set = nullptr;
    }
    else
    {
        if(dir == TrueToP) binary_operator_logic = new logic_binary_operator_logic_logic("\\iff", True, x->operand);
        if(dir == PToTrue) binary_operator_logic = new logic_binary_operator_logic_logic("\\iff", x->operand, True);
        x->operand = binary_operator_logic;
        binary_operator_type = LOGIC;
        binary_operator_set = nullptr;
    }
}

void statement::apply_binary_operator(vector<variable*> forall_variable_proof, expression* source, vector<int> path, vector<substitution*> sub, bool isPrint)
{
    //print substitution
    if(isPrint)
    {
        cout<<"Substitution:"<<endl;
        for(long i=0;i<sub.size();i++)
        {
            cout<<sub[i]->x->getLatex().getNormal()<<" is replaced by "<<sub[i]->y->getLatex().getNormal()<<endl;
        }
        cout<<endl;
    }
    
    //get external dependence of source part
    vector<variable*> external_dependence_source_part = forall_variable_proof;
    source->getPartExternalDependence(path, external_dependence_source_part);
    if(isPrint)
    {
        cout<<"External dependence of source part:"<<endl;
        for(long i=0;i<external_dependence_source_part.size();i++)
        {
            cout<<external_dependence_source_part[i]->getLatex().getNormal()<<" ";
        }
        cout<<endl;
    }
    
    //get all dependence of source part
    expression* source_part = source->getPart(path);
    vector<variable*> all_dependence_source_part = external_dependence_source_part;
    source_part->getInternalDependence(all_dependence_source_part);
    if(isPrint)
    {
        cout<<"All dependence of source part:"<<endl;
        for(long i=0;i<all_dependence_source_part.size();i++)
        {
            cout<<all_dependence_source_part[i]->getLatex().getNormal()<<" ";
        }
        cout<<endl;
    }
    
    //get all dependence of law
    vector<variable*> all_dependence_law;
    get_binary_operator()->getInternalDependence(all_dependence_law);
    content->getInternalDependence(all_dependence_law);
    if(isPrint)
    {
        cout<<"All dependence of law:"<<endl;
        for(long i=0;i<all_dependence_law.size();i++)
        {
            cout<<all_dependence_law[i]->getLatex().getNormal()<<" ";
        }
        cout<<endl;
    }
    
    //create replacement by exclusion
    vector<substitution*> replacement = createReplacement(all_dependence_law, all_dependence_source_part);
    if(isPrint)
    {
        cout<<"Replacement:"<<endl;
        for(long i=0;i<replacement.size();i++)
        {
            cout<<replacement[i]->x->getLatex().getNormal()<<" is replaced by "<<replacement[i]->y->getLatex().getNormal()<<endl;
        }
        cout<<endl;
    }
    
    //do replacement for law
    content->replace_variable(replacement);
    if(isPrint) cout<<content->getLatex().getNormal()<<endl;
    
    //do replacement for sub
    for(long i=0;i<sub.size();i++)
    {
        for(long j=0;j<replacement.size();j++)
        {
            if(replacement[j]->x->isEqual(sub[i]->x))
            {
                delete sub[i]->x;
                sub[i]->x = dynamic_cast<variable*>(replacement[j]->y->getCopy());
                break;
            }
        }
    }
    if(isPrint)
    {
        for(long i=0;i<sub.size();i++)
        {
            cout<<sub[i]->x->getLatex().getNormal()<<" is replaced by "<<sub[i]->y->getLatex().getNormal()<<endl;
        }
        cout<<endl;
    }
    
    //delete replacement
    for(long i=0;i<replacement.size();i++)
    {
        delete replacement[i];
    }
    
    //do substitution
    content = dynamic_cast<logic_value*>(expression::substitute_forall_variable(content, sub));
    if(isPrint)
    {
        cout<<"Do substitution:"<<endl;
        cout<<content->getLatex().getNormal()<<endl<<endl;
    }
    
    //delete sub
    for(long i=0;i<sub.size();i++)
    {
        delete sub[i];
    }
    
    //add universal quantifier at the beginning
    forall_variable.clear();
    for(long i = external_dependence_source_part.size()-1; i>=0; i--)
    {
        variable* variable_copy = dynamic_cast<variable*>(external_dependence_source_part[i]->getCopy());
        content = new universal_quantifier(variable_copy, content);
        forall_variable.insert(forall_variable.begin(), variable_copy);
    }
    if(isPrint)
    {
        cout<<"Add universal quantifier at the beginning:"<<endl;
        cout<<content->getLatex().getNormal()<<endl<<endl;
    }
    
    //do replacement for internal dependence
    vector<variable*> internal_dependence_law;
    get_oeprand(1)->getInternalDependence(internal_dependence_law);
    
    vector<variable*> internal_dependence_source_part;
    source_part->getInternalDependence(internal_dependence_source_part);
    
    if(internal_dependence_law.size() != internal_dependence_source_part.size())
    {
        cout<<"Error: the operand1 of law and the source part are different."<<endl;
    }
    
    replacement.clear();
    for(long i=0;i<internal_dependence_law.size();i++)
    {
        variable* var_copy = dynamic_cast<variable*>(internal_dependence_law[i]->getCopy());
        replacement.push_back(new substitution(var_copy, internal_dependence_source_part[i]->getCopy()));
    }
    if(isPrint)
    {
        cout<<"Replacement for internal dependence:"<<endl;
        for(long i=0;i<replacement.size();i++)
        {
            cout<<replacement[i]->x->getLatex().getNormal()<<" is replaced by "<<replacement[i]->y->getLatex().getNormal()<<endl;
        }
        cout<<endl;
    }
    
    content->replace_variable(replacement);
    if(isPrint) cout<<content->getLatex().getNormal()<<endl<<endl;
    
    if(!get_oeprand(1)->isEqual(source_part))
    {
        cout<<"Error: the operand1 of law and the source part are different."<<endl;
        cout<<source_part->getLatex().getNormal()<<endl;
        cout<<get_oeprand(1)->getLatex().getNormal()<<endl;
    }
    
    //delete replacement
    for(long i=0;i<replacement.size();i++)
    {
        delete replacement[i];
    }
    
    //assemble to the original source
    if(isPrint) cout<<"Do the assembly:"<<endl;
    while(true)
    {
        if(path.size() == 0) break;
        
        int p = path[path.size() -1];
        path.erase(path.end() -1);
        
        bool isChanged = expression::assemble(this, source->getPart(path), p);
        if(isPrint && isChanged) cout<<content->getLatex().getNormal()<<endl;
    }
    if(isPrint) cout<<endl;
    
    //check whether the operand1 of law is equal to the source
    if(!get_oeprand(1)->isEqual(source))
    {
        cout<<"Error: the operand1 of law and the source are different."<<endl;
    }
    
    //check forall_variable
    if(forall_variable.size() != forall_variable_proof.size())
    {
        cout<<"Error: The forall_variable doese not matched."<<endl;
    }
    
    for(long i=0;i<forall_variable.size();i++)
    {
        if(! forall_variable[i]->isEqual(forall_variable_proof[i]))
        {
            cout<<"Error: The forall_variable does not matched."<<endl;
        }
    }
}

vector<Definition*> Definition::All_Definition;
Definition::Definition(string newLabel, variable_type new_var_type, string x, bool isPrint) : statement(newLabel, new_var_type, x, isPrint)
{
}

Definition::Definition(string newLabel, expression* x) : statement(newLabel, x)
{
}

Definition::~Definition()
{
}

statement* Definition::getCopy()
{
    Definition* output = new Definition(label, content->getCopy());
    return output;
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

void Definition::addDefinition(ofstream& fout, Definition* x, string description)
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
    cout<< x->content->getLatex().getNormal() <<endl;
    cout<<endl;
    
    //write to file
    fout<<"\\begin{defn}"<<endl;
    fout<<"\\label{Definition:"<<x->label<<"}"<<endl;
    if(description != "") fout<< description <<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<< x->getLatex();
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{defn}"<<endl;
    fout<<endl;
}

vector<Axiom*> Axiom::All_Axiom;
Axiom::Axiom(string newLabel, variable_type new_var_type, string x, bool isPrint) : statement(newLabel, new_var_type, x, isPrint)
{
}

Axiom::Axiom(string newLabel, expression* x) : statement(newLabel, x)
{
}

Axiom::~Axiom()
{
}

statement* Axiom::getCopy()
{
    Axiom* output = new Axiom(label, content->getCopy());
    return output;
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

void Axiom::addAxiom(ofstream& fout, Axiom* x, string description)
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
    cout<< x->content->getLatex().getNormal() <<endl;
    cout<<endl;
    
    //write to file
    fout<<"\\begin{axm}"<<endl;
    fout<<"\\label{Axiom:"<<x->label<<"}"<<endl;
    if(description != "") fout<< description <<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<< x->getLatex();
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{axm}"<<endl;
    fout<<endl;
}

input::input(vector<int> new_relative_path, string new_law_label, direction new_dir, bool new_isFinished, bool new_isPrint)
{
    relative_path = new_relative_path;
    
    law = nullptr;
    law_label = new_law_label;
    
    dir = new_dir;
    
    sub_type = automatic;
    
    isFinished = new_isFinished;
    isPrint = new_isPrint;
}

input::input(vector<int> new_relative_path, string new_law_label, direction new_dir, vector<vector<int> > sub, bool new_isFinished, bool new_isPrint)
{
    relative_path = new_relative_path;
    
    law = nullptr;
    law_label = new_law_label;
    
    dir = new_dir;
    
    sub_type = source_specified;
    source_specified_substitution = sub;
    
    isFinished = new_isFinished;
    isPrint = new_isPrint;
}

input::input(vector<int> new_relative_path, string new_law_label, direction new_dir, vector<substitution*> sub, bool new_isFinished, bool new_isPrint)
{
    relative_path = new_relative_path;
    
    law = nullptr;
    law_label = new_law_label;
    
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
    forall_variable_proof = target->forall_variable;
}

proof_block::proof_block(string newLabel, Proposition x, proof_method new_method)
{
    label = newLabel;
    target = x.getCopy();
    method = new_method;
    forall_variable_proof = target->forall_variable;
}

proof_block::~proof_block()
{
    delete target;
    for(long i=0;i<chain_of_deductive.size();i++)
    {
        delete chain_of_deductive[i];
    }
}

void proof_block::set_split_point(vector<vector<int> > new_split_point)
{
    print_info[print_info.size()-1].split_point = new_split_point;
}

string proof_block::getLatex()
{
    string output = "";
    string quantifier_latex = "";
    for(long i=0;i<forall_variable_proof.size();i++)
    {
        if(dynamic_cast<set_variable*>(forall_variable_proof[i]))
        {
            quantifier_latex += "\\forall ";
            quantifier_latex += forall_variable_proof[i]->getLatex().getNormal();
            quantifier_latex += " ";
        }
    }
    
    if(quantifier_latex != "") output += "& " + quantifier_latex + "( \\\\" + "\n";
    
    for(long i=0;i<chain_of_deductive.size();i++)
    {
        if(i==0)
        {
            if(quantifier_latex != "") output += "& & ";
            output += "& " + chain_of_deductive[i]->get_oeprand(1)->getLatex().getNormal() + " \\\\" + "\n";
        }
        
        Print_Output operand2_latex = chain_of_deductive[i]->get_oeprand(2)->getLatex(print_info[i].split_point);
        for(long j=0;j<operand2_latex.all_visible.size();j++)
        {
            if(quantifier_latex != "") output += "& & ";
            if(j==0)
            {
                string operator_latex = chain_of_deductive[i]->get_binary_operator_latex();
                if(Definition* x = dynamic_cast<Definition*>(chain_of_deductive[i]))
                {
                    if(operator_latex == "\\iff" ||
                       operator_latex == "=" )
                    {
                        operator_latex = "\\overset{\\operatorname{def}}{" + operator_latex + "}";
                    }
                }
                output += operator_latex + " ";
            }
            output += "& ";
            
            if(operand2_latex.all_phantom[j] != "") output += "\\phantom{" + operand2_latex.all_phantom[j] + "} ";
            output += operand2_latex.all_visible[j];
            
            if(j != operand2_latex.all_visible.size()-1) output += " \\\\";
            output += "\n";
        }
        
        if(print_info[i].ref_type != "Local") output += "& & \\text{" + print_info[i].ref_type + " \\ref{" + print_info[i].ref_type + ":" + print_info[i].ref + "}} \\\\" + "\n";
        else output += "& & \\text{Proposition (" + print_info[i].ref + ")} \\\\" + "\n";
    }
    
    if(quantifier_latex != "") output = output + "& )" + "\n";
    return output;
}

void proof_block::set_target_forall_variable(long depth)
{
    target->set_forall_variable(forall_variable_proof, depth);
}

expression* proof_block::get_next_source()
{
    expression* source = nullptr;
    if(chain_of_deductive.size() == 0)
    {
        if(method == deduction)
        {
            source = target->get_oeprand(1)->getCopy();
        }
        else if(method == direct)
        {
            source = expression::createFromLatex("\\text{True}", LOGIC);
        }
        else if(method == backward)
        {
            vector<int> path(forall_variable_proof.size(), 1);
            source = target->content->getPart(path)->getCopy();
        }
    }
    else
    {
        long last_index = chain_of_deductive.size() -1;
        source = chain_of_deductive[last_index]->get_oeprand(2)->getCopy();
    }
    
    return source;
}

void proof_block::check_finished(statement* step)
{
    if(method == deduction || method == direct || method == backward)
    {
        if(method == deduction)
        {
            if(!step->get_oeprand(2)->isEqual(target->get_oeprand(2)))
            {
                cout<<"Error: The operand2 does not matched the operand2 of target."<<endl;
            }
        }
        else if(method == direct)
        {
            vector<int> path(forall_variable_proof.size(), 1);
            if(!step->get_oeprand(2)->isEqual(target->content->getPart(path)))
            {
                cout<<"Error: The operand2 does not matched the target."<<endl;
            }
        }
        else if(method == backward)
        {
            expression* True = expression::createFromLatex("\\text{True}", LOGIC);
            if(!step->get_oeprand(2)->isEqual(True))
            {
                cout<<"Error: The operand2 is not True."<<endl;
            }
            delete True;
        }
    }
}

void proof_block::append_binary_operator(input x)
{
    if(x.isPrint) cout<<"New step:"<<endl;
    expression* source = get_next_source();
    
    if(x.isPrint)
    {
        cout<<"source:"<<endl;
        string forall_variable_latex = "";
        for(long i=0;i<forall_variable_proof.size();i++)
        {
            forall_variable_latex += "\\forall " + forall_variable_proof[i]->getLatex().getNormal() + " ";
        }
        if(forall_variable_latex != "") cout<<"(";
        cout<<source->getLatex().getNormal();
        if(forall_variable_latex != "") cout<<")";
        cout<<endl;
    }
    
    //fill the x.law
    string Local_label = "";
    if(x.law == nullptr)
    {
        string statement_type;
        string statement_label;
        long index = x.law_label.find(":");
        if(index != string::npos)
        {
            statement_type = x.law_label.substr(0, index);
            statement_label = x.law_label.substr(index+1, x.law_label.size());
        }
        else
        {
            cout<<"Error: cannot process the law label: "<<x.law_label<<endl;
            return;
        }
        
        if(statement_type == "Definition") x.law = Definition::FindByRef(statement_label);
        else if(statement_type == "Axiom") x.law = Axiom::FindByRef(statement_label);
        else if(statement_type == "Proposition") x.law = Proposition::FindByRef(statement_label);
        else if(statement_type == "Local")
        {
            for(long i=0;i<Proposition::Current->proof.size();i++)
            {
                if(Proposition::Current->proof[i]->label == statement_label)
                {
                    x.law = Proposition::Current->proof[i]->target;
                    Local_label = statement_label;
                    break;
                }
            }
        }
        
        if(!x.law)
        {
            cout<<"Error: cannot find the law label: "<<x.law_label<<endl;
            return;
        }
    }
    
    //get a copy of law
    string Definition_label = "";
    string Axiom_label = "";
    if(x.dir == TrueToP || x.dir == PToTrue)
    {
        if(dynamic_cast<Definition*>(x.law)) Definition_label = x.law->label;
        if(dynamic_cast<Axiom*>(x.law)) Axiom_label = x.law->label;
        
        x.law = new Proposition(x.law->label, x.law->content->getCopy());
        x.law->upgrade_to_true(x.dir);
    }
    else
    {
        x.law = x.law->getCopy();
    }
    
    if(x.isPrint)
    {
        cout<<"law:"<<endl;
        cout<<x.law->content->getLatex().getNormal()<<endl;
        cout<<endl;
    }
    
    //fill the x.full_substitution
    if(method == direct && chain_of_deductive.size() == 0)
    {
        if(x.sub_type != full && x.law->forall_variable.size() >= 1)
        {
            cout<<"Error: cannot do this. please use the full substitution."<<endl;
            return;
        }
    }
    else
    {
        if(x.sub_type == source_specified)
        {
            x.full_substitution = createSubstitution(x.law->forall_variable, source, x.source_specified_substitution);
        }
        else if(x.sub_type == automatic)
        {
            vector<vector<int> > substitute_path = {};
            if(x.law->forall_variable.size() != 0)
            {
                if(x.dir == LeftToRight)
                {
                    x.law->find_all_path_of_variable(x.isPrint);
                    if(x.law->path_of_variable_operand1.size() == 0)
                    {
                        cout<<"Error: cannot do automatic substitution for LeftToRight."<<endl;
                        return;
                    }
                    substitute_path = x.law->path_of_variable_operand1;
                }
                else if(x.dir == RightToLeft)
                {
                    x.law->find_all_path_of_variable(x.isPrint);
                    if(x.law->path_of_variable_operand2.size() == 0)
                    {
                        cout<<"Error: cannot do automatic substitution for RightToLeft."<<endl;
                        return;
                    }
                    substitute_path = x.law->path_of_variable_operand2;
                }
                else if(x.dir == PToTrue)
                {
                    x.law->find_all_path_of_variable(x.isPrint);
                    if(x.law->path_of_variable_operand1.size() == 0)
                    {
                        cout<<"Error: cannot do automatic substitution for PToTrue."<<endl;
                        return;
                    }
                    substitute_path = x.law->path_of_variable_operand1;
                }
                else if(x.dir == TrueToP)
                {
                    cout<<"Error: cannot do automatic substitution for TrueToP."<<endl;
                    return;
                }
            }
            
            expression* source_part = source->getPart(x.relative_path);
            x.full_substitution = createSubstitution(x.law->forall_variable, source_part, substitute_path);
        }
    }
    
    //Swap for direction Right to Left
    if(x.dir == RightToLeft)
    {
        if(x.law->get_binary_operator_latex() == "\\iff")
        {
            //swap
            if(x.law->binary_operator_type == LOGIC)
            {
                logic_value* temp = x.law->binary_operator_logic->operand1;
                x.law->binary_operator_logic->operand1 = x.law->binary_operator_logic->operand2;
                x.law->binary_operator_logic->operand2 = temp;
            }
            else if(x.law->binary_operator_type == SET)
            {
                Set* temp = x.law->binary_operator_set->operand1;
                x.law->binary_operator_set->operand1 = x.law->binary_operator_set->operand2;
                x.law->binary_operator_set->operand2 = temp;
            }
            
            if(x.isPrint)
            {
                cout<<"Swap two operands for the direction RightToLeft"<<endl;
                cout<<x.law->content->getLatex().getNormal()<<endl;
            }
        }
        else
        {
            cout<<"Error: cannot apply for the RightToLeft direction."<<endl;
        }
    }
    
    x.law->apply_binary_operator(forall_variable_proof, source, x.relative_path, x.full_substitution, x.isPrint);
    delete source;
    
    if(method == deduction)
    {
        if(x.law->get_binary_operator_latex() == "\\implies" && target->get_binary_operator_latex() == "\\iff")
        {
            cout<<"Error: The deduction method cannot work for \\implies."<<endl;
            return;
        }
    }
    else if(method == backward)
    {
        if(x.law->get_binary_operator_latex() == "\\implies")
        {
            cout<<"Error: The backward method cannot work for \\implies."<<endl;
            return;
        }
    }
    
    if(x.isFinished) check_finished(x.law);
    
    //fill print_info
    Print_Info element;
    if(Definition_label != "")
    {
        element.ref_type = "Definition";
        element.ref = Definition_label;
    }
    else if(Axiom_label != "")
    {
        element.ref_type = "Axiom";
        element.ref = Axiom_label;
    }
    else if(Local_label != "")
    {
        element.ref_type = "Local";
        element.ref = Local_label;
    }
    else if(dynamic_cast<Definition*>(x.law))
    {
        element.ref_type= "Definition";
        element.ref = x.law->label;
    }
    else if(dynamic_cast<Axiom*>(x.law))
    {
        element.ref_type = "Axiom";
        element.ref = x.law->label;
    }
    else if(dynamic_cast<Proposition*>(x.law))
    {
        element.ref_type = "Proposition";
        element.ref = x.law->label;
    }
    
    element.split_point.clear();
    print_info.push_back(element);
    
    chain_of_deductive.push_back(x.law);
}

vector<Proposition*> Proposition::All_Proposition;
Proposition* Proposition::Current;
Proposition::Proposition(string newLabel, variable_type new_var_type, string x, bool isPrint) : statement(newLabel, new_var_type, x, isPrint)
{
}

Proposition::Proposition(string newLabel, expression* x) : statement(newLabel, x)
{
}

Proposition::~Proposition()
{
    for(long i=0;i<proof.size();i++)
    {
        delete proof[i];
    }
}

statement* Proposition::getCopy()
{
    Proposition* output = new Proposition(label, content->getCopy());
    return output;
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
    cout<< x->content->getLatex().getNormal() <<endl;
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
        if(x->proof[i]->target->label != "")
        {
            fout<< "Proof of Proposition \\ref{Proposition:" << x->proof[i]->target->label << "}" <<endl;
        }
        else
        {
            fout<< "Proposition (" << x->proof[i]->label << ")" <<endl;
            fout<<"\\begin{align*}"<<endl;
            fout<< x->proof[i]->target->getLatex();
            fout<<"\\end{align*}"<<endl;
            fout<< "Proof of Proposition (" << x->proof[i]->label << ")" <<endl;
        }
        
        fout<<"\\begin{align*}"<<endl;
        fout<<x->proof[i]->getLatex();
        cout<<x->proof[i]->getLatex()<<endl;
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
        
        if(x->label != label)
        {
            cout<<"Error: The label does not matched the content."<<endl;
        }
    }
    
    proof.push_back(x);
}
