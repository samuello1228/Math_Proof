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

statement* statement::apply_binary_operator(statement* target, vector<int> path, vector<vector<int> > substitute_path, direction dir, bool isPrint)
{
    if(binary_operator == nullptr)
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
    logic_value* source_copy = dynamic_cast<logic_value*>(content->getCopy());
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
    if(isPrint) cout<<"Do the assembly:"<<endl;
    while(true)
    {
        if(path.size() == 0) break;
        
        int p = path[path.size() -1];
        path.erase(path.end() -1);
        
        bool isChanged = expression::assemble(output, target->content->getPart(path), p, target->forall_variable);
        if(isPrint && isChanged) cout<<output->content->getLatex()<<endl;
    }
    if(isPrint) cout<<endl;
    
    //for direction Right to Left
    if(dir == RightToLeft)
    {
        if(output->binary_operator->operator_latex == "\\overset{\\operatorname{def}}{\\iff}" ||
           output->binary_operator->operator_latex == "\\iff" )
        {
            //swap
            logic_value* temp = output->binary_operator->operand1;
            output->binary_operator->operand1 = output->binary_operator->operand2;
            output->binary_operator->operand2 = temp;
            if(isPrint)
            {
                cout<<"Swap two operands for the direction RightToLeft"<<endl;
                cout<<output->content->getLatex()<<endl;
            }
        }
        else
        {
            cout<<"Error: cannot apply for the RightToLeft direction."<<endl;
        }
    }
    
    //check whether the output->operand1 is equal to the source
    statement* copy_object_1 = output->getCopy();
    copy_object_1->collapse_to_operand(1);
    if(!copy_object_1->content->isEqual(target->content))
    {
        cout<<"Error: the operand1 of output and the target are different."<<endl;
    }
    delete copy_object_1;
    
    //check forall_variable
    if(output->forall_variable.size() != target->forall_variable.size())
    {
        cout<<"Error: The forall_variable doese not matched."<<endl;
    }
    
    for(long i=0;i<output->forall_variable.size();i++)
    {
        if(! output->forall_variable[i]->isEqual(target->forall_variable[i]))
        {
            cout<<"Error: The forall_variable does not matched."<<endl;
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

void proof_block::getLatex()
{
    
}

void proof_block::append_binary_operator(vector<int> path, statement* law, vector<vector<int> > substitute_path, direction dir, bool isFinished, bool isPrint)
{
    if(isPrint) cout<<"New step:"<<endl;
    if(method == deduction)
    {
        statement* source = nullptr;
        if(chain_of_deductive.size() == 0)
        {
            source = target->getCopy();
            source->collapse_to_operand(1);
        }
        else
        {
            long last_index = chain_of_deductive.size() -1;
            source = chain_of_deductive[last_index]->getCopy();
            source->collapse_to_operand(2);
        }
        
        if(isPrint)
        {
            cout<<source->content->getLatex()<<endl;
            cout<<law->content->getLatex()<<endl;
            cout<<endl;
        }
        statement* step = law->apply_binary_operator(source, path, substitute_path, dir, isPrint);
        delete source;
        
        if(step->binary_operator->operator_latex == "\\implies" && target->binary_operator->operator_latex == "\\iff")
        {
            cout<<"Error: The deduction cannot work for \\iff."<<endl;
            return;
        }
        
        if(isFinished)
        {
            statement* copy_target_2 = target->getCopy();
            copy_target_2->collapse_to_operand(2);
            
            statement* copy_step_2 = step->getCopy();
            copy_step_2->collapse_to_operand(2);
            if(!copy_step_2->content->isEqual(copy_target_2->content))
            {
                cout<<"Error: The operand2 does not matched the operand2 of target."<<endl;
            }
            
            delete copy_target_2;
            delete copy_step_2;
        }
        
        chain_of_deductive.push_back(step);
    }
}

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
