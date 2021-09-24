//
//  expression.cpp
//  Math_Proof
//
//  Created by Samuel on 15/9/2021.
//  Copyright © 2021 Samuel. All rights reserved.
//

#include "expression.hpp"

bool isEnglishLetter(string x)
{
    if(x.size() != 1) return false;
    
    int ascii = int(x[0]);
    if((ascii >= 65 && ascii <= 90) || (ascii >= 97 && ascii <= 122)) return true;
    else return false;
}

bool eraseParenthesis(string& latex)
{
    if(latex[0] != '(' || latex[latex.size()-1] != ')') return false;
    
    bool isErase = false;
    unsigned int index = 0;
    int parenthesisLevel = 0;
    while(true)
    {
        if(latex[index] == '(') parenthesisLevel++;
        else if(latex[index] == ')')
        {
            parenthesisLevel--;
            if(parenthesisLevel == 0)
            {
                if(index+1 == latex.size()) isErase = true;
                else isErase = false;
                
                break;
            }
        }
        
        if(index+1 == latex.size())
        {
            cout<<"Error: Impossible case"<<endl;
            break;
        }
        else index++;
    }
    
    if(isErase)
    {
        latex.erase(0,1);
        latex.erase(latex.size()-1,1);
    }
    
    return isErase;
}

void eraseSpaceParenthesis(string& latex)
{
    //remove space and parenthesis at the beginning and the end.
    while(true)
    {
        bool isErased = false;
        if(latex[0] == ' ')
        {
            latex.erase(0,1);
            isErased = true;
        }
        
        if(latex[latex.size()-1] == ' ')
        {
            latex.erase(latex.size()-1,1);
            isErased = true;
        }
        
        //erase "(" and ")"
        if(eraseParenthesis(latex)) isErased = true;
        
        if(!isErased) break;
    }
}

expression* expression::createFromLatex(string latex, variable_type var_type)
{
    //remove space and parenthesis at the beginning and the end.
    eraseSpaceParenthesis(latex);
    
    if(latex.size() == 0)
    {
        cout<<"Syntax Error: the expression is empty"<<endl;
        return nullptr;
    }
    
    //split the expression by whitespace and parenthesis, at the topmost parenthesis level
    vector<string> elements;
    {
        unsigned int index = 0;
        int parenthesisLevel = 0;
        string element;
        while(true)
        {
            if(parenthesisLevel == 0)
            {
                if(latex[index] == ' ')
                {
                    if(element.size() != 0)
                    {
                        elements.push_back(element);
                        element.clear();
                    }
                }
                else if(latex[index] == '(')
                {
                    if(element.size() != 0)
                    {
                        elements.push_back(element);
                        element.clear();
                    }
                    parenthesisLevel++;
                }
                else if(latex[index] == ')')
                {
                    cout<<"Error: Impossible case"<<endl;
                    return nullptr;
                }
                else element += latex[index];
            }
            else if(latex[index] == ')' && parenthesisLevel == 1)
            {
                if(element.size() != 0)
                {
                    elements.push_back(element);
                    element.clear();
                }
                parenthesisLevel--;
            }
            else
            {
                element += latex[index];
                if(latex[index] == '(') parenthesisLevel++;
                else if(latex[index] == ')') parenthesisLevel--;
            }
            
            if(index == latex.size()-1)
            {
                if(parenthesisLevel != 0)
                {
                    cout<<"Error: "<< parenthesisLevel <<" closing parenthesis is missing."<<endl;
                    return nullptr;
                }
                
                if(element.size() != 0)
                {
                    elements.push_back(element);
                    element.clear();
                }
                break;
            }
            else index++;
        }
    }
    
    for(long i=0; i<elements.size(); i++) eraseSpaceParenthesis(elements[i]);
    
    if(elements.size() == 1)
    {
        if(elements[0] == "\\text{True}")
        {
            //For logic element True
            expression* output = new logic_element(true);
            return output;
        }
        else if(elements[0] == "\\text{False}")
        {
            //For logic element False
            expression* output = new logic_element(false);
            return output;
        }
        else if(isEnglishLetter(elements[0]))
        {
            //For variables with English letter
            if(var_type == LOGIC)
            {
                expression* output = new logic_variable(elements[0]);
                return output;
            }
            else if(var_type == SET)
            {
                expression* output = new set_variable(elements[0]);
                return output;
            }
        }
    }
    else if(elements.size() == 2)
    {
        if(elements[0] == "\\lnot")
        {
            //For logical NOT
            logic_value* operand = dynamic_cast<logic_value*>(expression::createFromLatex(elements[1], var_type));
            if(!operand)
            {
                cout<<"Type Error: the operand is not logic value: "<<elements[1]<<endl;
                return nullptr;
            }
            
            expression* output = new logic_unary_operator_logic(elements[0], operand);
            return output;
        }
    }
    else if(elements.size() == 3)
    {
        if(elements[1] == "\\overset{\\operatorname{def}}{\\iff}" ||
           elements[1] == "\\lor"  ||
           elements[1] == "\\land" ||
           elements[1] == "\\iff" ||
           elements[1] == "\\implies"
           )
        {
            //For logical OR/AND
            logic_value* operand1 = dynamic_cast<logic_value*>(expression::createFromLatex(elements[0], var_type));
            logic_value* operand2 = dynamic_cast<logic_value*>(expression::createFromLatex(elements[2], var_type));
            if(!operand1 || !operand2)
            {
                cout<<"Type Error: the two operands are not logic values: "<<elements[0]<<endl;
                cout<<elements[2]<<endl;
                return nullptr;
            }
            expression* output = new logic_binary_operator_logic_logic(elements[1], operand1, operand2);
            return output;
        }
    }
    
    //For quantifier
    if(elements.size() >= 3 && elements.size() % 2 == 1)
    {
        bool isQuantifier = true;
        for(long i=0;i<= elements.size()-2;i++)
        {
            if(i%2==0)
            {
                if(elements[i] != "\\forall" && elements[i] != "\\exists") isQuantifier = false;
            }
        }
        
        if(isQuantifier)
        {
            vector<string> quantifier_list;
            vector<variable*> var_list;
            for(long i=0;i<= elements.size()-2;i++)
            {
                if(i%2==0)
                {
                    quantifier_list.push_back(elements[i]);
                }
                else
                {
                    variable* var = nullptr;
                    if(!isEnglishLetter(elements[i]))
                    {
                        cout<<"Variale Error: the variable for the quantifier is not English letter: "<<elements[i]<<endl;
                        return nullptr;
                    }
                    else
                    {
                        if(var_type == LOGIC) var = new logic_variable(elements[i]);
                        else if(var_type == SET) var = new set_variable(elements[i]);
                    }
                    var_list.push_back(var);
                }
            }
            
            logic_value* operand = dynamic_cast<logic_value*>(expression::createFromLatex(elements[elements.size()-1], var_type));
            if(!operand)
            {
                cout<<"Type Error: the operand is not logic value: "<<elements[elements.size()-1]<<endl;
                return nullptr;
            }
            
            long index = quantifier_list.size() -1;
            while(true)
            {
                if(quantifier_list[index] == "\\forall")
                {
                    operand = new universal_quantifier(var_list[index], operand);
                    
                }
                else if(quantifier_list[index] == "\\exists")
                {
                    operand = new existential_quantifier(var_list[index], operand);
                }
                
                if(index == 0) break;
                else index --;
            }
            
            return operand;
        }
    }
    
    cout<<"Syntax Error: the expression cannot be processed: "<<latex<<endl;
    return nullptr;
}

expression::~expression()
{
}

string expression::getLatex()
{
    string x = "";
    return x;
}

variable::variable(const string& newLatex)
{
    latex = newLatex;
}

variable::~variable()
{
}

string variable::getLatex()
{
    return latex;
}

logic_element::logic_element(bool x)
{
    value = x;
}

string logic_element::getLatex()
{
    string x = "";
    if(value) x = "\\text{True}";
    else x = "\\text{False}";
    return x;
}

logic_variable::logic_variable(const string& newLatex) : variable(newLatex)
{
}

string logic_variable::getLatex()
{
    return latex;
}

bool compound_logic::isIff()
{
    return false;
}

bool compound_logic::isImplies()
{
    return false;
}

set_variable::set_variable(const string& newLatex) : variable(newLatex)
{
}

string set_variable::getLatex()
{
    return latex;
}

quantifier::quantifier(variable* x, logic_value* y)
{
    var = x;
    operand = y;
}

quantifier::~quantifier()
{
    delete var;
    delete operand;
}

string quantifier::getLatex()
{
    string output = "";
    logic_value* x = this;
    while(true)
    {
        universal_quantifier* y = dynamic_cast<universal_quantifier*>(x);
        existential_quantifier* z = dynamic_cast<existential_quantifier*>(x);
        if(y)
        {
            output += "\\forall " + y->var->getLatex() + " ";
            x = y->operand;
        }
        else if(z)
        {
            output += "\\exists " + z->var->getLatex() + " ";
            x = z->operand;
        }
        else break;
    }
    
    string operand_latex = x->getLatex();
    output += "(" + operand_latex + ")";
    return output;
}

universal_quantifier::universal_quantifier(variable* x, logic_value* y) : quantifier(x,y)
{
}

existential_quantifier::existential_quantifier(variable* x, logic_value* y) : quantifier(x,y)
{
}

logic_unary_operator_logic::logic_unary_operator_logic(const string& newLatex, logic_value* x)
{
    operator_latex = newLatex;
    operand = x;
}

string logic_unary_operator_logic::getLatex()
{
    string operand_latex = operand->getLatex();
    variable* var = dynamic_cast<variable*>(operand);
    if(!var)
    {
        operand_latex = "(" + operand_latex + ")";
    }
    
    if(operator_latex == "\\lnot")
    {
        //For logical not
        string output = "\\lnot " + operand_latex;
        return output;
    }
    else
    {
        cout<<"Syntax Error: the operator cannot be processed: "<<operator_latex<<endl;
        string output = "";
        return output;
    }
}

logic_unary_operator_logic::~logic_unary_operator_logic()
{
    delete operand;
}

logic_binary_operator_logic_logic::logic_binary_operator_logic_logic(const string& newLatex, logic_value* x, logic_value* y)
{
    operator_latex = newLatex;
    operand1 = x;
    operand2 = y;
}

logic_binary_operator_logic_logic::~logic_binary_operator_logic_logic()
{
    delete operand1;
    delete operand2;
}

string logic_binary_operator_logic_logic::getLatex()
{
    string operand1_latex = operand1->getLatex();
    variable* var1 = dynamic_cast<variable*>(operand1);
    if(!var1)
    {
        operand1_latex = "(" + operand1_latex + ")";
    }
    
    string operand2_latex = operand2->getLatex();
    variable* var2 = dynamic_cast<variable*>(operand2);
    if(!var2)
    {
        operand2_latex = "(" + operand2_latex + ")";
    }
    
    if(operator_latex == "\\overset{\\operatorname{def}}{\\iff}" ||
       operator_latex == "\\lor"  ||
       operator_latex == "\\land" ||
       operator_latex == "\\iff" ||
       operator_latex == "\\implies"
       )
    {
        //For logical OR/AND
        string output = operand1_latex + " " + operator_latex + " " + operand2_latex;
        return output;
    }
    else
    {
        cout<<"Syntax Error: the operator cannot be processed: "<<operator_latex<<endl;
        string output = "";
        return output;
    }
}

bool logic_binary_operator_logic_logic::isIff()
{
    if(operator_latex == "\\iff") return true;
    else return false;
}

bool logic_binary_operator_logic_logic::isImplies()
{
    if(operator_latex == "\\implies") return true;
    else return false;
}