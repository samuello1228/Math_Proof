//
//  expression.cpp
//  Math_Proof
//
//  Created by Samuel on 15/9/2021.
//  Copyright © 2021 Samuel. All rights reserved.
//

#include "expression.hpp"

substitution::substitution(variable* new_x, expression* new_y)
{
    if(logic_variable* var = dynamic_cast<logic_variable*>(new_x))
    {
        logic_value* z = dynamic_cast<logic_value*>(new_y);
        if(!z)
        {
            cout << "Error: the variable type is not matched." << endl;
            x = nullptr;
            y = nullptr;
            return;
        }
    }
    else if(set_variable* var = dynamic_cast<set_variable*>(new_x))
    {
        Set* z = dynamic_cast<Set*>(new_y);
        if(!z)
        {
            cout << "Error: the variable type is not matched." << endl;
            x = nullptr;
            y = nullptr;
            return;
        }
    }

    x = new_x;
    y = new_y;
}

substitution::substitution(string x_latex, string y_latex, variable_type var_type)
{
    y = expression::createFromLatex(y_latex, var_type);
    if(dynamic_cast<logic_value*>(y))
    {
        x = dynamic_cast<variable*>(expression::createFromLatex(x_latex, LOGIC));
    }
    else if(dynamic_cast<Set*>(y))
    {
        x = dynamic_cast<variable*>(expression::createFromLatex(x_latex, SET));
    }

    if(!x)
    {
        cout << "Error: The substitution is not variable." << endl;
    }
}

substitution::~substitution()
{
    delete x;
    delete y;
}

string Print_Output::getNormal()
{
    return all_visible[0];
}

bool isEnglishLetter(string x)
{
    if(x.size() != 1) return false;

    int ascii = int(x[0]);
    if((ascii >= 65 && ascii <= 90) || (ascii >= 97 && ascii <= 122)) return true;
    else return false;
}

bool eraseParenthesis(string& latex)
{
    if(latex[0] != '(' || latex[latex.size() - 1] != ')') return false;

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
                if(index + 1 == latex.size()) isErase = true;
                else isErase = false;

                break;
            }
        }

        if(index + 1 == latex.size())
        {
            cout << "Error: Impossible case" << endl;
            break;
        }
        else index++;
    }

    if(isErase)
    {
        latex.erase(0, 1);
        latex.erase(latex.size() - 1, 1);
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
            latex.erase(0, 1);
            isErased = true;
        }

        if(latex[latex.size() - 1] == ' ')
        {
            latex.erase(latex.size() - 1, 1);
            isErased = true;
        }

        //erase "(" and ")"
        if(eraseParenthesis(latex)) isErased = true;

        if(!isErased) break;
    }
}

bool expression::needParenthesis(expression* operand)
{
    bool condition = dynamic_cast<logic_variable*>(operand);
    condition = condition || dynamic_cast<set_variable*>(operand);

    bool condition_set_element = false;
    if(set_element* x = dynamic_cast<set_element*>(operand))
    {
        condition_set_element = (x->latex == "\\emptyset" ||
                                 x->latex == "\\mathbb{N}" ||
                                 x->latex == "0" ||
                                 x->latex == "1");
    }
    condition = condition || condition_set_element;

    bool condition_curly_bracket = false;
    if(set_unary_operator_set* x = dynamic_cast<set_unary_operator_set*>(operand))
    {
        if(x->operator_latex == "singleton_set") condition_curly_bracket = true;
    }
    else if(set_binary_operator_set_set* x = dynamic_cast<set_binary_operator_set_set*>(operand))
    {
        if(x->operator_latex == "pair_set") condition_curly_bracket = true;
    }
    condition = condition || condition_curly_bracket;

    return !condition;
}

Print_Output expression::getLatex_aux_1_operand(vector<vector<int> > split_point, expression* operand, string prefix, string suffix, bool add_parenthesis)
{
    for(long i = 0; i < split_point.size(); i++)
    {
        if(split_point[i].size() == 1)
        {
            cout << "Error: Cannot split the operand " << split_point[i][0] << "." << endl;
        }
        else
        {
            if(split_point[i][0] == 1)
            {
                split_point[i].erase(split_point[i].begin());
            }
            else cout << "Error: Impossible path." << endl;
        }
    }

    if(add_parenthesis || expression::needParenthesis(operand))
    {
        prefix = prefix + "(";
        suffix = ")" + suffix;
    }

    Print_Output operand_latex = operand->getLatex(split_point);
    operand_latex.all_visible[0] = prefix + operand_latex.all_visible[0];
    for(long i = 1; i < operand_latex.all_phantom.size(); i++)
    {
        operand_latex.all_phantom[i] = prefix + operand_latex.all_phantom[i];
    }
    operand_latex.all_visible[operand_latex.all_visible.size() - 1] += suffix;
    return operand_latex;
}

Print_Output expression::getLatex_aux_2_operand(vector<vector<int> > split_point, expression* operand1, expression* operand2, string prefix_1, string suffix_1, string prefix_2, string suffix_2)
{
    bool is_split_operand_2 = false;
    vector<vector<int> > split_point_1;
    vector<vector<int> > split_point_2;
    for(long i = 0; i < split_point.size(); i++)
    {
        if(split_point[i].size() == 1)
        {
            if(split_point[i][0] == 2) is_split_operand_2 = true;
            else cout << "Error: Cannot split the operand " << split_point[i][0] << "." << endl;
        }
        else
        {
            if(split_point[i][0] == 1)
            {
                split_point[i].erase(split_point[i].begin());
                split_point_1.push_back(split_point[i]);
            }
            else if(split_point[i][0] == 2)
            {
                split_point[i].erase(split_point[i].begin());
                split_point_2.push_back(split_point[i]);
            }
            else cout << "Error: Impossible path." << endl;
        }
    }

    if(expression::needParenthesis(operand1))
    {
        prefix_1 = prefix_1 + "(";
        suffix_1 = ")" + suffix_1;
    }

    if(expression::needParenthesis(operand2))
    {
        prefix_2 = prefix_2 + "(";
        suffix_2 = ")" + suffix_2;
    }

    Print_Output operand1_latex = operand1->getLatex(split_point_1);
    operand1_latex.all_visible[0] = prefix_1 + operand1_latex.all_visible[0];
    for(long i = 1; i < operand1_latex.all_phantom.size(); i++)
    {
        operand1_latex.all_phantom[i] = prefix_1 + operand1_latex.all_phantom[i];
    }
    operand1_latex.all_visible[operand1_latex.all_visible.size() - 1] += suffix_1;

    Print_Output operand2_latex = operand2->getLatex(split_point_2);
    operand2_latex.all_visible[operand2_latex.all_visible.size() - 1] += suffix_2;
    if(is_split_operand_2)
    {
        operand2_latex.all_visible[0] = prefix_2 + operand2_latex.all_visible[0];
        for(long i = 1; i < operand2_latex.all_phantom.size(); i++)
        {
            operand2_latex.all_phantom[i] = prefix_2 + operand2_latex.all_phantom[i];
        }
    }
    else
    {
        string phantom_add = operand1_latex.all_phantom[operand1_latex.all_phantom.size() - 1] + operand1_latex.all_visible[operand1_latex.all_visible.size() - 1] + " " + prefix_2;

        operand1_latex.all_visible[operand1_latex.all_visible.size() - 1] += " " + prefix_2 + operand2_latex.all_visible[0];

        for(long i = 1; i < operand2_latex.all_phantom.size(); i++)
        {
            operand2_latex.all_phantom[i] = phantom_add + operand2_latex.all_phantom[i];
        }

        operand2_latex.all_visible.erase(operand2_latex.all_visible.begin());
        operand2_latex.all_phantom.erase(operand2_latex.all_phantom.begin());
    }

    for(long i = 0; i < operand2_latex.all_visible.size(); i++)
    {
        operand1_latex.all_visible.push_back(operand2_latex.all_visible[i]);
        operand1_latex.all_phantom.push_back(operand2_latex.all_phantom[i]);
    }

    return operand1_latex;
}

expression* expression::createFromLatex(string latex, variable_type var_type, bool isPrint)
{
    //remove space and parenthesis at the beginning and the end.
    eraseSpaceParenthesis(latex);

    if(latex.size() == 0)
    {
        cout << "Syntax Error: the expression is empty" << endl;
        return nullptr;
    }

    if(isPrint) cout << latex << endl;

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
                    cout << "Error: the number of closing parenthesis is more than expected." << endl;
                    cout << latex << endl;
                    return nullptr;
                }
                else if(latex[index] == '\\' && latex[index + 1] == '{')
                {
                    if(element.size() != 0)
                    {
                        elements.push_back(element);
                    }
                    element = "\\{";
                    index++;
                    parenthesisLevel++;
                }
                else if(latex[index] == '\\' && latex[index + 1] == '}')
                {
                    cout << "Error: Impossible case" << endl;
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
            else if(latex[index] == '\\' && latex[index + 1] == '}' && parenthesisLevel == 1)
            {
                element += "\\}";
                index++;
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
                if(latex[index] == '\\')
                {
                    if(latex[index + 1] == '{')
                    {
                        index++;
                        element += latex[index];
                        parenthesisLevel++;
                    }
                    else if(latex[index + 1] == '}')
                    {
                        index++;
                        element += latex[index];
                        parenthesisLevel--;
                    }
                }
            }

            if(index == latex.size() - 1)
            {
                if(parenthesisLevel != 0)
                {
                    cout << "Error: " << parenthesisLevel << " closing parenthesis is missing." << endl;
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

    if(isPrint)
    {
        for(long i = 0; i < elements.size(); i++)
        {
            cout << i << ": " << elements[i] << endl;
        }
        cout << endl;
    }

    for(long i = 0; i < elements.size(); i++) eraseSpaceParenthesis(elements[i]);

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
        else if(elements[0] == "\\emptyset" ||
                elements[0] == "\\mathbb{N}" ||
                elements[0] == "0" ||
                elements[0] == "1")
        {
            expression* output = new set_element(elements[0]);
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
        if(elements[0].size() >= 4 &&
           elements[0][0] == '\\' &&
           elements[0][1] == '{' &&
           elements[0][elements[0].size() - 2] == '\\' &&
           elements[0][elements[0].size() - 1] == '}')
        {
            bool is_pair_set = false;
            long comma_index = -1;
            for(long i = 2; i <= elements[0].size() - 3; i++)
            {
                if(elements[0][i] == ',')
                {
                    is_pair_set = true;
                    comma_index = i;
                    break;
                }
            }

            if(is_pair_set)
            {
                //For pair_set
                string operand1_latex = "";
                for(long i = 2; i <= comma_index - 1; i++)
                {
                    operand1_latex += elements[0][i];
                }

                string operand2_latex = "";
                for(long i = comma_index + 1; i <= elements[0].size() - 3; i++)
                {
                    operand2_latex += elements[0][i];
                }

                Set* operand1 = dynamic_cast<Set*>(expression::createFromLatex(operand1_latex, var_type, isPrint));
                Set* operand2 = dynamic_cast<Set*>(expression::createFromLatex(operand2_latex, var_type, isPrint));
                if(!operand1 || !operand2)
                {
                    cout << "Type Error: the two operands are not set: " << operand1_latex << endl;
                    cout << operand2_latex << endl;
                    return nullptr;
                }

                expression* output = new set_binary_operator_set_set("pair_set", operand1, operand2);
                return output;
            }
            else
            {
                //For singleton_set
                string operand_latex = "";
                for(long i = 2; i <= elements[0].size() - 3; i++)
                {
                    operand_latex += elements[0][i];
                }

                Set* operand = dynamic_cast<Set*>(expression::createFromLatex(operand_latex, var_type, isPrint));
                if(!operand)
                {
                    cout << "Type Error: the operand are not set: " << operand_latex << endl;
                    return nullptr;
                }

                expression* output = new set_unary_operator_set("singleton_set", operand);
                return output;
            }
        }
    }
    else if(elements.size() == 2)
    {
        if(elements[0] == "\\lnot")
        {
            //For logical NOT
            logic_value* operand = dynamic_cast<logic_value*>(expression::createFromLatex(elements[1], var_type, isPrint));
            if(!operand)
            {
                cout << "Type Error: the operand is not logic value: " << elements[1] << endl;
                return nullptr;
            }

            expression* output = new logic_unary_operator_logic(elements[0], operand);
            return output;
        }
        else if(elements[0] == "\\bigcup")
        {
            Set* operand = dynamic_cast<Set*>(expression::createFromLatex(elements[1], var_type, isPrint));
            if(!operand)
            {
                cout << "Type Error: the operand is not set: " << elements[1] << endl;
                return nullptr;
            }

            expression* output = new set_unary_operator_set(elements[0], operand);
            return output;
        }
        else if(elements[0] == "S")
        {
            Set* operand = dynamic_cast<Set*>(expression::createFromLatex(elements[1], var_type, isPrint));
            if(!operand)
            {
                cout << "Type Error: the operand is not set: " << elements[1] << endl;
                return nullptr;
            }

            expression* output = new set_unary_operator_set("successor", operand);
            return output;
        }
    }
    else if(elements.size() == 3)
    {
        if(elements[1] == "\\lor" ||
           elements[1] == "\\land" ||
           elements[1] == "\\iff" ||
           elements[1] == "\\implies"
           )
        {
            logic_value* operand1 = dynamic_cast<logic_value*>(expression::createFromLatex(elements[0], var_type, isPrint));
            logic_value* operand2 = dynamic_cast<logic_value*>(expression::createFromLatex(elements[2], var_type, isPrint));
            if(!operand1 || !operand2)
            {
                cout << "Type Error: the two operands are not logic values: " << elements[0] << endl;
                cout << elements[2] << endl;
                return nullptr;
            }
            expression* output = new logic_binary_operator_logic_logic(elements[1], operand1, operand2);
            return output;
        }
        else if(elements[1] == "\\in" ||
                elements[1] == "\\notin" ||
                elements[1] == "=" ||
                elements[1] == "\\neq" ||
                elements[1] == "\\subseteq"
                )
        {
            Set* operand1 = dynamic_cast<Set*>(expression::createFromLatex(elements[0], var_type, isPrint));
            Set* operand2 = dynamic_cast<Set*>(expression::createFromLatex(elements[2], var_type, isPrint));
            if(!operand1 || !operand2)
            {
                cout << "Type Error: the two operands are not set: " << elements[0] << endl;
                cout << elements[2] << endl;
                return nullptr;
            }
            expression* output = new logic_binary_operator_set_set(elements[1], operand1, operand2);
            return output;
        }
        else if(elements[1] == "\\cup" ||
                elements[1] == "+")
        {
            Set* operand1 = dynamic_cast<Set*>(expression::createFromLatex(elements[0], var_type, isPrint));
            Set* operand2 = dynamic_cast<Set*>(expression::createFromLatex(elements[2], var_type, isPrint));
            if(!operand1 || !operand2)
            {
                cout << "Type Error: the two operands are not set: " << elements[0] << endl;
                cout << elements[2] << endl;
                return nullptr;
            }
            expression* output = new set_binary_operator_set_set(elements[1], operand1, operand2);
            return output;
        }
    }

    //For quantifier
    if(elements.size() >= 3 && elements.size() % 2 == 1)
    {
        bool isQuantifier = true;
        for(long i = 0; i <= elements.size() - 2; i++)
        {
            if(i % 2 == 0)
            {
                if(elements[i] != "\\forall" && elements[i] != "\\exists") isQuantifier = false;
            }
        }

        if(isQuantifier)
        {
            vector<string> quantifier_list;
            vector<variable*> var_list;
            for(long i = 0; i <= elements.size() - 2; i++)
            {
                if(i % 2 == 0)
                {
                    quantifier_list.push_back(elements[i]);
                }
                else
                {
                    variable* var = nullptr;
                    if(!isEnglishLetter(elements[i]))
                    {
                        cout << "Variale Error: the variable for the quantifier is not English letter: " << elements[i] << endl;
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

            logic_value* operand = dynamic_cast<logic_value*>(expression::createFromLatex(elements[elements.size() - 1], var_type, isPrint));
            if(!operand)
            {
                cout << "Type Error: the operand is not logic value: " << elements[elements.size() - 1] << endl;
                return nullptr;
            }

            long index = quantifier_list.size() - 1;
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
                else index--;
            }

            return operand;
        }
    }

    cout << "Syntax Error: the expression cannot be processed: " << latex << endl;
    return nullptr;
}

expression* expression::substitute_forall_variable(expression* x, vector<substitution*> sub)
{
    if(variable* y = dynamic_cast<variable*>(x))
    {
        for(long i = 0; i < sub.size(); i++)
        {
            if(y->isEqual(sub[i]->x))
            {
                expression* output = sub[i]->y->getCopy();
                delete x;
                return output;
            }
        }
    }
    else if(universal_quantifier* y = dynamic_cast<universal_quantifier*>(x))
    {
        for(long i = 0; i < sub.size(); i++)
        {
            if(y->var->isEqual(sub[i]->x))
            {
                expression* output = expression::substitute_forall_variable(y->operand, sub);
                y->operand = dynamic_cast<logic_value*>(expression::createFromLatex("\\text{True}", LOGIC));
                delete y;
                return output;
            }
        }

        y->operand = dynamic_cast<logic_value*>(expression::substitute_forall_variable(y->operand, sub));
    }
    else if(existential_quantifier* y = dynamic_cast<existential_quantifier*>(x))
    {
        y->operand = dynamic_cast<logic_value*>(expression::substitute_forall_variable(y->operand, sub));
    }
    else if(logic_unary_operator_logic* y = dynamic_cast<logic_unary_operator_logic*>(x))
    {
        y->operand = dynamic_cast<logic_value*>(expression::substitute_forall_variable(y->operand, sub));
    }
    else if(set_unary_operator_set* y = dynamic_cast<set_unary_operator_set*>(x))
    {
        y->operand = dynamic_cast<Set*>(expression::substitute_forall_variable(y->operand, sub));
    }
    else if(logic_binary_operator_logic_logic* y = dynamic_cast<logic_binary_operator_logic_logic*>(x))
    {
        y->operand1 = dynamic_cast<logic_value*>(expression::substitute_forall_variable(y->operand1, sub));
        y->operand2 = dynamic_cast<logic_value*>(expression::substitute_forall_variable(y->operand2, sub));
    }
    else if(logic_binary_operator_set_set* y = dynamic_cast<logic_binary_operator_set_set*>(x))
    {
        y->operand1 = dynamic_cast<Set*>(expression::substitute_forall_variable(y->operand1, sub));
        y->operand2 = dynamic_cast<Set*>(expression::substitute_forall_variable(y->operand2, sub));
    }
    else if(set_binary_operator_set_set* y = dynamic_cast<set_binary_operator_set_set*>(x))
    {
        y->operand1 = dynamic_cast<Set*>(expression::substitute_forall_variable(y->operand1, sub));
        y->operand2 = dynamic_cast<Set*>(expression::substitute_forall_variable(y->operand2, sub));
    }

    return x;
}

void expression::replace_by_set(logic_value* x, vector<int> path, Set* y)
{
    if(path.size() == 0)
    {
        cout << "Error: it is not allowed. The part must be set, not logic value." << endl;
        return;
    }

    //get the last class that contain x as operand.
    int p = path.back();
    path.pop_back();
    expression* z = x->getPart(path);
    if(logic_binary_operator_set_set* z_copy = dynamic_cast<logic_binary_operator_set_set*>(z))
    {
        if(p == 1)
        {
            delete z_copy->operand1;
            z_copy->operand1 = dynamic_cast<Set*>(y->getCopy());
        }
        else if(p == 2)
        {
            delete z_copy->operand2;
            z_copy->operand2 = dynamic_cast<Set*>(y->getCopy());
        }
        else cout << "Error: The path for binary operator is not 1 or 2." << endl;
    }
    else if(set_unary_operator_set* z_copy = dynamic_cast<set_unary_operator_set*>(z))
    {
        if(p == 1)
        {
            delete z_copy->operand;
            z_copy->operand = dynamic_cast<Set*>(y->getCopy());
        }
        else cout << "Error: The path for unary operator is not 1." << endl;
    }
    else if(set_binary_operator_set_set* z_copy = dynamic_cast<set_binary_operator_set_set*>(z))
    {
        if(p == 1)
        {
            delete z_copy->operand1;
            z_copy->operand1 = dynamic_cast<Set*>(y->getCopy());
        }
        else if(p == 2)
        {
            delete z_copy->operand2;
            z_copy->operand2 = dynamic_cast<Set*>(y->getCopy());
        }
        else cout << "Error: The path for binary operator is not 1 or 2." << endl;
    }
    else
    {
        cout << "Error: it is not allowed. The part must be set, not logic value." << endl;
    }
}

bool expression::assemble(statement* step, expression* source_part, int p)
{
    if(quantifier* source_part_copy = dynamic_cast<quantifier*>(source_part))
    {
        bool condition = (step->get_binary_operator_latex() == "\\iff" ||
                          step->get_binary_operator_latex() == "\\implies");

        if(condition)
        {
            variable* var1 = dynamic_cast<variable*>(source_part_copy->var->getCopy());
            variable* var2 = dynamic_cast<variable*>(source_part_copy->var->getCopy());
            if(universal_quantifier* z = dynamic_cast<universal_quantifier*>(source_part))
            {
                step->binary_operator_logic->operand1 = new universal_quantifier(var1, step->binary_operator_logic->operand1);
                step->binary_operator_logic->operand2 = new universal_quantifier(var2, step->binary_operator_logic->operand2);
            }
            else if(existential_quantifier* z = dynamic_cast<existential_quantifier*>(source_part))
            {
                step->binary_operator_logic->operand1 = new existential_quantifier(var1, step->binary_operator_logic->operand1);
                step->binary_operator_logic->operand2 = new existential_quantifier(var2, step->binary_operator_logic->operand2);
            }

            step->delete_the_last_universal_quantifier();
            return true;
        }
    }
    else if(logic_unary_operator_logic* source_part_copy = dynamic_cast<logic_unary_operator_logic*>(source_part))
    {
        bool condition_iff = (step->get_binary_operator_latex() == "\\iff");
        condition_iff = condition_iff && (source_part_copy->operator_latex == "\\lnot");

        if(condition_iff)
        {
            step->binary_operator_logic->operand1 = new logic_unary_operator_logic(source_part_copy->operator_latex, step->binary_operator_logic->operand1);
            step->binary_operator_logic->operand2 = new logic_unary_operator_logic(source_part_copy->operator_latex, step->binary_operator_logic->operand2);
            return true;
        }
    }
    else if(logic_binary_operator_logic_logic* source_part_copy = dynamic_cast<logic_binary_operator_logic_logic*>(source_part))
    {
        bool condition_iff = (step->get_binary_operator_latex() == "\\iff");
        condition_iff = condition_iff && (source_part_copy->operator_latex == "\\lor" ||
                                          source_part_copy->operator_latex == "\\land" ||
                                          source_part_copy->operator_latex == "\\iff" ||
                                          source_part_copy->operator_latex == "\\implies");

        bool condition_implies_1 = (step->get_binary_operator_latex() == "\\implies");
        condition_implies_1 = condition_implies_1 && (source_part_copy->operator_latex == "\\lor" ||
                                                      source_part_copy->operator_latex == "\\land");
        //Counter example for \\iff
        //(F \\implies T) \implies ( (F \\iff F) \implies (T \\iff F) )

        bool condition_implies_2 = (step->get_binary_operator_latex() == "\\implies");
        condition_implies_2 = condition_implies_2 && (source_part_copy->operator_latex == "\\implies");
        //Counter example for \\implies and p == 1
        //(F \\implies T) \implies ( (F \\implies F) \implies (T \\implies F) )

        if(p == 1 && (condition_iff || condition_implies_1))
        {
            logic_value* copy1 = dynamic_cast<logic_value*>(source_part_copy->operand2->getCopy());
            logic_value* copy2 = dynamic_cast<logic_value*>(source_part_copy->operand2->getCopy());
            step->binary_operator_logic->operand1 = new logic_binary_operator_logic_logic(source_part_copy->operator_latex, step->binary_operator_logic->operand1, copy1);
            step->binary_operator_logic->operand2 = new logic_binary_operator_logic_logic(source_part_copy->operator_latex, step->binary_operator_logic->operand2, copy2);
            return true;
        }
        else if(p == 2 && (condition_iff || condition_implies_1 || condition_implies_2))
        {
            logic_value* copy1 = dynamic_cast<logic_value*>(source_part_copy->operand1->getCopy());
            logic_value* copy2 = dynamic_cast<logic_value*>(source_part_copy->operand1->getCopy());
            step->binary_operator_logic->operand1 = new logic_binary_operator_logic_logic(source_part_copy->operator_latex, copy1, step->binary_operator_logic->operand1);
            step->binary_operator_logic->operand2 = new logic_binary_operator_logic_logic(source_part_copy->operator_latex, copy2, step->binary_operator_logic->operand2);
            return true;
        }
    }
    else if(logic_binary_operator_set_set* source_part_copy = dynamic_cast<logic_binary_operator_set_set*>(source_part))
    {
        bool condition_equality = (step->get_binary_operator_latex() == "=");
        condition_equality = condition_equality && (source_part_copy->operator_latex == "\\in" ||
                                                    source_part_copy->operator_latex == "\\notin" ||
                                                    source_part_copy->operator_latex == "=" ||
                                                    source_part_copy->operator_latex == "\\neq" ||
                                                    source_part_copy->operator_latex == "\\subseteq");

        if((p == 1 || p == 2) && condition_equality)
        {
            universal_quantifier* x = nullptr;
            universal_quantifier* y = dynamic_cast<universal_quantifier*>(step->content);
            while(true)
            {
                if(y)
                {
                    x = y;
                    y = dynamic_cast<universal_quantifier*>(y->operand);
                }
                else break;
            }

            logic_value* operand1 = nullptr;
            logic_value* operand2 = nullptr;
            if(p == 1)
            {
                Set* copy1 = dynamic_cast<Set*>(source_part_copy->operand2->getCopy());
                Set* copy2 = dynamic_cast<Set*>(source_part_copy->operand2->getCopy());
                operand1 = new logic_binary_operator_set_set(source_part_copy->operator_latex, step->binary_operator_set->operand1, copy1);
                operand2 = new logic_binary_operator_set_set(source_part_copy->operator_latex, step->binary_operator_set->operand2, copy2);
            }
            else if(p == 2)
            {
                Set* copy1 = dynamic_cast<Set*>(source_part_copy->operand1->getCopy());
                Set* copy2 = dynamic_cast<Set*>(source_part_copy->operand1->getCopy());
                operand1 = new logic_binary_operator_set_set(source_part_copy->operator_latex, copy1, step->binary_operator_set->operand1);
                operand2 = new logic_binary_operator_set_set(source_part_copy->operator_latex, copy2, step->binary_operator_set->operand2);
            }

            //delete step->binary_operator_set
            step->binary_operator_set->operand1 = dynamic_cast<Set*>(expression::createFromLatex("a", SET));
            step->binary_operator_set->operand2 = dynamic_cast<Set*>(expression::createFromLatex("a", SET));
            delete step->binary_operator_set;
            step->binary_operator_set = nullptr;

            //build step->binary_operator_logic
            step->binary_operator_type = LOGIC;
            step->binary_operator_logic = new logic_binary_operator_logic_logic("\\iff", operand1, operand2);
            if(x == nullptr)
            {
                step->content = step->binary_operator_logic;
            }
            else
            {
                x->operand = step->binary_operator_logic;
            }

            return true;
        }
    }
    else if(set_unary_operator_set* source_part_copy = dynamic_cast<set_unary_operator_set*>(source_part))
    {
        bool condition_equality = (step->get_binary_operator_latex() == "=");
        condition_equality = condition_equality && (source_part_copy->operator_latex == "singleton_set" ||
                                                    source_part_copy->operator_latex == "\\bigcup" ||
                                                    source_part_copy->operator_latex == "successor");

        if(condition_equality)
        {
            step->binary_operator_set->operand1 = new set_unary_operator_set(source_part_copy->operator_latex, step->binary_operator_set->operand1);
            step->binary_operator_set->operand2 = new set_unary_operator_set(source_part_copy->operator_latex, step->binary_operator_set->operand2);
            return true;
        }
    }
    else if(set_binary_operator_set_set* source_part_copy = dynamic_cast<set_binary_operator_set_set*>(source_part))
    {
        bool condition_equality = (step->get_binary_operator_latex() == "=");
        condition_equality = condition_equality && (source_part_copy->operator_latex == "pair_set" ||
                                                    source_part_copy->operator_latex == "\\cup" ||
                                                    source_part_copy->operator_latex == "+");

        if(p == 1 && condition_equality)
        {
            Set* copy1 = dynamic_cast<Set*>(source_part_copy->operand2->getCopy());
            Set* copy2 = dynamic_cast<Set*>(source_part_copy->operand2->getCopy());
            step->binary_operator_set->operand1 = new set_binary_operator_set_set(source_part_copy->operator_latex, step->binary_operator_set->operand1, copy1);
            step->binary_operator_set->operand2 = new set_binary_operator_set_set(source_part_copy->operator_latex, step->binary_operator_set->operand2, copy2);
            return true;
        }
        else if(p == 2 && condition_equality)
        {
            Set* copy1 = dynamic_cast<Set*>(source_part_copy->operand1->getCopy());
            Set* copy2 = dynamic_cast<Set*>(source_part_copy->operand1->getCopy());
            step->binary_operator_set->operand1 = new set_binary_operator_set_set(source_part_copy->operator_latex, copy1, step->binary_operator_set->operand1);
            step->binary_operator_set->operand2 = new set_binary_operator_set_set(source_part_copy->operator_latex, copy2, step->binary_operator_set->operand2);
            return true;
        }
    }
    else
    {
        cout << "Error: it is not allowed." << endl;
        return false;
    }

    return false;
}

variable::variable(const string& newLatex)
{
    latex = newLatex;
}

void variable::replace_variable(vector<substitution*> replacement)
{
    for(long i = 0; i < replacement.size(); i++)
    {
        if(replacement[i]->x->isEqual(this))
        {
            variable* z = dynamic_cast<variable*>(replacement[i]->y);
            latex = z->latex;
            break;
        }
    }
}

bool variable::check_variable(vector<variable*> var_list)
{
    for(long i = 0; i < var_list.size(); i++)
    {
        if(isEqual(var_list[i]))
        {
            return true;
        }
    }

    cout << "Error: variable " << getLatex().getNormal() << " is not declared in the quantifier." << endl;
    return false;
}

bool variable::contain_variable(variable* x)
{
    if(isEqual(x)) return true;
    else return false;
}

void variable::find_path_of_variable(variable* var, vector<int> current_path, vector<vector<int> >& all_path)
{
    if(isEqual(var)) all_path.push_back(current_path);
}

logic_element::logic_element(bool x)
{
    value = x;
}

Print_Output logic_element::getLatex(vector<vector<int> > split_point)
{
    Print_Output output;
    if(value) output.all_visible.push_back("\\text{True}");
    else output.all_visible.push_back("\\text{False}");
    output.all_phantom.push_back("");
    return output;
}

bool logic_element::isEqual(expression* x)
{
    logic_element* y = dynamic_cast<logic_element*>(x);
    if(!y) return false;
    if(y->value != value) return false;
    return true;
}

expression* logic_element::getCopy()
{
    logic_element* x = new logic_element(value);
    return x;
}

logic_variable::logic_variable(const string& newLatex) : variable(newLatex)
{
}

Print_Output logic_variable::getLatex(vector<vector<int> > split_point)
{
    Print_Output output;
    output.all_visible.push_back(latex);
    output.all_phantom.push_back("");
    return output;
}

bool logic_variable::isEqual(expression* x)
{
    logic_variable* y = dynamic_cast<logic_variable*>(x);
    if(!y) return false;
    if(y->latex != latex) return false;
    return true;
}

expression* logic_variable::getCopy()
{
    logic_variable* x = new logic_variable(latex);
    return x;
}

set_element::set_element(string x)
{
    latex = x;
}

Print_Output set_element::getLatex(vector<vector<int> > split_point)
{
    Print_Output output;
    output.all_visible.push_back(latex);
    output.all_phantom.push_back("");
    return output;
}

bool set_element::isEqual(expression* x)
{
    set_element* y = dynamic_cast<set_element*>(x);
    if(!y) return false;
    if(y->latex != latex) return false;
    return true;
}

expression* set_element::getCopy()
{
    set_element* x = new set_element(latex);
    return x;
}

set_variable::set_variable(const string& newLatex) : variable(newLatex)
{
}

Print_Output set_variable::getLatex(vector<vector<int> > split_point)
{
    Print_Output output;
    output.all_visible.push_back(latex);
    output.all_phantom.push_back("");
    return output;
}

bool set_variable::isEqual(expression* x)
{
    set_variable* y = dynamic_cast<set_variable*>(x);
    if(!y) return false;
    if(y->latex != latex) return false;
    return true;
}

expression* set_variable::getCopy()
{
    set_variable* x = new set_variable(latex);
    return x;
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

Print_Output quantifier::getLatex(vector<vector<int> > split_point)
{
    string prefix = "";
    logic_value* x = this;
    while(true)
    {
        if(universal_quantifier* y = dynamic_cast<universal_quantifier*>(x))
        {
            prefix += "\\forall " + y->var->getLatex().getNormal() + " ";
            x = y->operand;

            for(long i = 0; i < split_point.size(); i++)
            {
                if(split_point[i][0] != 1) cout << "Error: Impossible path." << endl;
                split_point[i].erase(split_point[i].begin());
            }
        }
        else if(existential_quantifier* y = dynamic_cast<existential_quantifier*>(x))
        {
            prefix += "\\exists " + y->var->getLatex().getNormal() + " ";
            x = y->operand;

            for(long i = 0; i < split_point.size(); i++)
            {
                if(split_point[i][0] != 1) cout << "Error: Impossible path." << endl;
                split_point[i].erase(split_point[i].begin());
            }
        }
        else break;
    }
    prefix += "(";

    Print_Output operand_latex = x->getLatex(split_point);
    operand_latex.all_visible[0] = prefix + operand_latex.all_visible[0];
    for(long i = 1; i < operand_latex.all_phantom.size(); i++)
    {
        operand_latex.all_phantom[i] = prefix + operand_latex.all_phantom[i];
    }
    operand_latex.all_visible[operand_latex.all_visible.size() - 1] += ")";
    return operand_latex;
}

void quantifier::replace_variable(vector<substitution*> replacement)
{
    for(long i = 0; i < replacement.size(); i++)
    {
        if(replacement[i]->x->isEqual(var))
        {
            variable* z = dynamic_cast<variable*>(replacement[i]->y);
            var->latex = z->latex;
            break;
        }
    }

    operand->replace_variable(replacement);
}

bool quantifier::check_variable(vector<variable*> var_list)
{
    //check whether the variable name is distinct
    for(long i = 0; i < var_list.size(); i++)
    {
        if(var_list[i]->isEqual(var))
        {
            cout << "Error: Two quantifiers have the same variable name." << endl;
            return false;
        }
    }

    //add the variable to the list
    var_list.push_back(var);
    return operand->check_variable(var_list);
}

expression* quantifier::getPart(vector<int> path)
{
    if(path.size() == 0) return this;

    if(path[0] != 1)
    {
        cout << "Error: The path for quantifier is not 1." << endl;
    }

    path.erase(path.begin());
    return operand->getPart(path);
}

void quantifier::getPartExternalDependence(vector<int> path, vector<variable*>& dependence)
{
    if(path.size() == 0) return;
    path.erase(path.begin());

    dependence.push_back(var);
    operand->getPartExternalDependence(path, dependence);
}

void quantifier::getInternalDependence(vector<variable*>& dependence)
{
    bool duplicate = false;
    for(long i = 0; i < dependence.size(); i++)
    {
        if(var->isEqual(dependence[i]))
        {
            duplicate = true;
        }
    }

    if(!duplicate) dependence.push_back(var);
    operand->getInternalDependence(dependence);
}

void quantifier::find_path_of_variable(variable* var, vector<int> current_path, vector<vector<int> >& all_path)
{
    vector<int> current_path_1 = current_path;
    current_path_1.push_back(1);
    operand->find_path_of_variable(var, current_path_1, all_path);
}

bool quantifier::contain_variable(variable* x)
{
    return operand->contain_variable(x);
}

universal_quantifier::universal_quantifier(variable* x, logic_value* y) : quantifier(x, y)
{
}

bool universal_quantifier::isEqual(expression* x)
{
    universal_quantifier* y = dynamic_cast<universal_quantifier*>(x);
    if(!y) return false;
    if(!y->var->isEqual(var)) return false;
    if(!y->operand->isEqual(operand)) return false;
    return true;
}

expression* universal_quantifier::getCopy()
{
    variable* var_copy = dynamic_cast<variable*>(var->getCopy());
    logic_value* operand_copy = dynamic_cast<logic_value*>(operand->getCopy());
    universal_quantifier* x = new universal_quantifier(var_copy, operand_copy);
    return x;
}

existential_quantifier::existential_quantifier(variable* x, logic_value* y) : quantifier(x, y)
{
}

bool existential_quantifier::isEqual(expression* x)
{
    existential_quantifier* y = dynamic_cast<existential_quantifier*>(x);
    if(!y) return false;
    if(!y->var->isEqual(var)) return false;
    if(!y->operand->isEqual(operand)) return false;
    return true;
}

expression* existential_quantifier::getCopy()
{
    variable* var_copy = dynamic_cast<variable*>(var->getCopy());
    logic_value* operand_copy = dynamic_cast<logic_value*>(operand->getCopy());
    existential_quantifier* x = new existential_quantifier(var_copy, operand_copy);
    return x;
}

template <class T>
bool isEqual_1_operand(T* x, expression* y)
{
    T* z = dynamic_cast<T*>(y);
    if(!z) return false;
    if(z->operator_latex != x->operator_latex) return false;
    if(!z->operand->isEqual(x->operand)) return false;
    return true;
}

template <class T>
bool isEqual_2_operand(T* x, expression* y)
{
    T* z = dynamic_cast<T*>(y);
    if(!z) return false;
    if(z->operator_latex != x->operator_latex) return false;
    if(!z->operand1->isEqual(x->operand1)) return false;
    if(!z->operand2->isEqual(x->operand2)) return false;
    return true;
}

template <class T, class value_type>
expression* getCopy_1_operand(T* x)
{
    value_type* operand_copy = dynamic_cast<value_type*>(x->operand->getCopy());
    T* y = new T(x->operator_latex, operand_copy);
    return y;
}

template <class T, class value_type>
expression* getCopy_2_operand(T* x)
{
    value_type* operand1_copy = dynamic_cast<value_type*>(x->operand1->getCopy());
    value_type* operand2_copy = dynamic_cast<value_type*>(x->operand2->getCopy());
    T* y = new T(x->operator_latex, operand1_copy, operand2_copy);
    return y;
}

template <class T>
expression* getPart_1_operand(T* x, vector<int>& path)
{
    if(path.size() == 0) return x;

    if(path[0] != 1)
    {
        cout << "Error: The path for unary operator is not 1." << endl;
    }

    path.erase(path.begin());
    return x->operand->getPart(path);
}

template <class T>
expression* getPart_2_operand(T* x, vector<int>& path)
{
    if(path.size() == 0) return x;

    int p = path[0];
    path.erase(path.begin());

    if(p == 1) return x->operand1->getPart(path);
    else if(p == 2) return x->operand2->getPart(path);
    else
    {
        cout << "Error: The path for binary operator is not 1 or 2." << endl;
        return nullptr;
    }
}

template <class T>
void getPartExternalDependence_1_operand(T* x, vector<int>& path, vector<variable*>& dependence)
{
    if(path.size() == 0) return;
    path.erase(path.begin());

    x->operand->getPartExternalDependence(path, dependence);
}

template <class T>
void getPartExternalDependence_2_operand(T* x, vector<int>& path, vector<variable*>& dependence)
{
    if(path.size() == 0) return;

    int p = path[0];
    path.erase(path.begin());

    if(p == 1) x->operand1->getPartExternalDependence(path, dependence);
    else if(p == 2) x->operand2->getPartExternalDependence(path, dependence);
    else return;
}

template <class T>
void find_path_of_variable_1_operand(T* x, variable* var, vector<int>& current_path, vector<vector<int> >& all_path)
{
    vector<int> current_path_1 = current_path;
    current_path_1.push_back(1);
    x->operand->find_path_of_variable(var, current_path_1, all_path);
}

template <class T>
void find_path_of_variable_2_operand(T* x, variable* var, vector<int>& current_path, vector<vector<int> >& all_path)
{
    vector<int> current_path_1 = current_path;
    current_path_1.push_back(1);
    x->operand1->find_path_of_variable(var, current_path_1, all_path);

    vector<int> current_path_2 = current_path;
    current_path_2.push_back(2);
    x->operand2->find_path_of_variable(var, current_path_2, all_path);
}

logic_unary_operator_logic::logic_unary_operator_logic(const string& newLatex, logic_value* x)
{
    operator_latex = newLatex;
    operand = x;
}

logic_unary_operator_logic::~logic_unary_operator_logic()
{
    delete operand;
}

Print_Output logic_unary_operator_logic::getLatex(vector<vector<int> > split_point)
{
    string prefix = "";
    string suffix = "";
    if(operator_latex == "\\lnot")
    {
        prefix = operator_latex + " ";
    }
    else
    {
        cout << "Syntax Error: the operator cannot be processed: " << operator_latex << endl;
        Print_Output output;
        return output;
    }

    return expression::getLatex_aux_1_operand(split_point, operand, prefix, suffix, false);
}

bool logic_unary_operator_logic::isEqual(expression* x)
{
    return isEqual_1_operand<logic_unary_operator_logic>(this, x);
}

expression* logic_unary_operator_logic::getCopy()
{
    return getCopy_1_operand<logic_unary_operator_logic, logic_value>(this);
}

void logic_unary_operator_logic::replace_variable(vector<substitution*> replacement)
{
    operand->replace_variable(replacement);
}

bool logic_unary_operator_logic::check_variable(vector<variable*> var_list)
{
    return operand->check_variable(var_list);
}

expression* logic_unary_operator_logic::getPart(vector<int> path)
{
    return getPart_1_operand<logic_unary_operator_logic>(this, path);
}

void logic_unary_operator_logic::getPartExternalDependence(vector<int> path, vector<variable*>& dependence)
{
    getPartExternalDependence_1_operand<logic_unary_operator_logic>(this, path, dependence);
}

void logic_unary_operator_logic::getInternalDependence(vector<variable*>& dependence)
{
    operand->getInternalDependence(dependence);
}

void logic_unary_operator_logic::find_path_of_variable(variable* var, vector<int> current_path, vector<vector<int> >& all_path)
{
    find_path_of_variable_1_operand<logic_unary_operator_logic>(this, var, current_path, all_path);
}

bool logic_unary_operator_logic::contain_variable(variable* x)
{
    return operand->contain_variable(x);
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

Print_Output logic_binary_operator_logic_logic::getLatex(vector<vector<int> > split_point)
{
    string prefix_1 = "";
    string suffix_1 = "";
    string prefix_2 = "";
    string suffix_2 = "";
    if(operator_latex == "\\lor" ||
       operator_latex == "\\land" ||
       operator_latex == "\\iff" ||
       operator_latex == "\\implies"
       )
    {
        prefix_1 = "";
        suffix_1 = "";
        prefix_2 = operator_latex + " ";
        suffix_2 = "";
    }
    else
    {
        cout << "Syntax Error: the operator cannot be processed: " << operator_latex << endl;
        Print_Output output;
        return output;
    }

    return expression::getLatex_aux_2_operand(split_point, operand1, operand2, prefix_1, suffix_1, prefix_2, suffix_2);
}

bool logic_binary_operator_logic_logic::isEqual(expression* x)
{
    return isEqual_2_operand<logic_binary_operator_logic_logic>(this, x);
}

expression* logic_binary_operator_logic_logic::getCopy()
{
    return getCopy_2_operand<logic_binary_operator_logic_logic, logic_value>(this);
}

void logic_binary_operator_logic_logic::replace_variable(vector<substitution*> replacement)
{
    operand1->replace_variable(replacement);
    operand2->replace_variable(replacement);
}

bool logic_binary_operator_logic_logic::check_variable(vector<variable*> var_list)
{
    return (operand1->check_variable(var_list) && operand2->check_variable(var_list));
}

expression* logic_binary_operator_logic_logic::getPart(vector<int> path)
{
    return getPart_2_operand<logic_binary_operator_logic_logic>(this, path);
}

void logic_binary_operator_logic_logic::getPartExternalDependence(vector<int> path, vector<variable*>& dependence)
{
    getPartExternalDependence_2_operand<logic_binary_operator_logic_logic>(this, path, dependence);
}

void logic_binary_operator_logic_logic::getInternalDependence(vector<variable*>& dependence)
{
    operand1->getInternalDependence(dependence);
    operand2->getInternalDependence(dependence);
}

void logic_binary_operator_logic_logic::find_path_of_variable(variable* var, vector<int> current_path, vector<vector<int> >& all_path)
{
    find_path_of_variable_2_operand<logic_binary_operator_logic_logic>(this, var, current_path, all_path);
}

bool logic_binary_operator_logic_logic::contain_variable(variable* x)
{
    return (operand1->contain_variable(x) || operand2->contain_variable(x));
}

logic_binary_operator_set_set::logic_binary_operator_set_set(const string& newLatex, Set* x, Set* y)
{
    operator_latex = newLatex;
    operand1 = x;
    operand2 = y;
}

logic_binary_operator_set_set::~logic_binary_operator_set_set()
{
    delete operand1;
    delete operand2;
}

Print_Output logic_binary_operator_set_set::getLatex(vector<vector<int> > split_point)
{
    string prefix_1 = "";
    string suffix_1 = "";
    string prefix_2 = "";
    string suffix_2 = "";
    if(operator_latex == "\\in" ||
       operator_latex == "\\notin" ||
       operator_latex == "=" ||
       operator_latex == "\\neq" ||
       operator_latex == "\\subseteq"
       )
    {
        prefix_1 = "";
        suffix_1 = "";
        prefix_2 = operator_latex + " ";
        suffix_2 = "";
    }
    else
    {
        cout << "Syntax Error: the operator cannot be processed: " << operator_latex << endl;
        Print_Output output;
        return output;
    }

    return expression::getLatex_aux_2_operand(split_point, operand1, operand2, prefix_1, suffix_1, prefix_2, suffix_2);
}

bool logic_binary_operator_set_set::isEqual(expression* x)
{
    return isEqual_2_operand<logic_binary_operator_set_set>(this, x);
}

expression* logic_binary_operator_set_set::getCopy()
{
    return getCopy_2_operand<logic_binary_operator_set_set, Set>(this);
}

void logic_binary_operator_set_set::replace_variable(vector<substitution*> replacement)
{
    operand1->replace_variable(replacement);
    operand2->replace_variable(replacement);
}

bool logic_binary_operator_set_set::check_variable(vector<variable*> var_list)
{
    return (operand1->check_variable(var_list) && operand2->check_variable(var_list));
}

expression* logic_binary_operator_set_set::getPart(vector<int> path)
{
    return getPart_2_operand<logic_binary_operator_set_set>(this, path);
}

void logic_binary_operator_set_set::getPartExternalDependence(vector<int> path, vector<variable*>& dependence)
{
    getPartExternalDependence_2_operand<logic_binary_operator_set_set>(this, path, dependence);
}

void logic_binary_operator_set_set::getInternalDependence(vector<variable*>& dependence)
{
    operand1->getInternalDependence(dependence);
    operand2->getInternalDependence(dependence);
}

void logic_binary_operator_set_set::find_path_of_variable(variable* var, vector<int> current_path, vector<vector<int> >& all_path)
{
    find_path_of_variable_2_operand<logic_binary_operator_set_set>(this, var, current_path, all_path);
}

bool logic_binary_operator_set_set::contain_variable(variable* x)
{
    return (operand1->contain_variable(x) || operand2->contain_variable(x));
}

set_unary_operator_set::set_unary_operator_set(const string& newLatex, Set* x)
{
    operator_latex = newLatex;
    operand = x;
}

set_unary_operator_set::~set_unary_operator_set()
{
    delete operand;
}

Print_Output set_unary_operator_set::getLatex(vector<vector<int> > split_point)
{
    string prefix = "";
    string suffix = "";
    bool add_parenthesis = false;
    if(operator_latex == "singleton_set")
    {
        prefix = "\\{ ";
        suffix = " \\}";
    }
    else if(operator_latex == "\\bigcup")
    {
        prefix = "\\bigcup ";
        suffix = "";
    }
    else if(operator_latex == "successor")
    {
        prefix = "S";
        add_parenthesis = true;
    }
    else
    {
        cout << "Syntax Error: the operator cannot be processed: " << operator_latex << endl;
        Print_Output output;
        return output;
    }

    return expression::getLatex_aux_1_operand(split_point, operand, prefix, suffix, add_parenthesis);
}

bool set_unary_operator_set::isEqual(expression* x)
{
    return isEqual_1_operand<set_unary_operator_set>(this, x);
}

expression* set_unary_operator_set::getCopy()
{
    return getCopy_1_operand<set_unary_operator_set, Set>(this);
}

void set_unary_operator_set::replace_variable(vector<substitution*> replacement)
{
    operand->replace_variable(replacement);
}

bool set_unary_operator_set::check_variable(vector<variable*> var_list)
{
    return operand->check_variable(var_list);
}

expression* set_unary_operator_set::getPart(vector<int> path)
{
    return getPart_1_operand<set_unary_operator_set>(this, path);
}

void set_unary_operator_set::getPartExternalDependence(vector<int> path, vector<variable*>& dependence)
{
    getPartExternalDependence_1_operand<set_unary_operator_set>(this, path, dependence);
}

void set_unary_operator_set::getInternalDependence(vector<variable*>& dependence)
{
    operand->getInternalDependence(dependence);
}

void set_unary_operator_set::find_path_of_variable(variable* var, vector<int> current_path, vector<vector<int> >& all_path)
{
    find_path_of_variable_1_operand<set_unary_operator_set>(this, var, current_path, all_path);
}

bool set_unary_operator_set::contain_variable(variable* x)
{
    return operand->contain_variable(x);
}

set_binary_operator_set_set::set_binary_operator_set_set(const string& newLatex, Set* x, Set* y)
{
    operator_latex = newLatex;
    operand1 = x;
    operand2 = y;
}

set_binary_operator_set_set::~set_binary_operator_set_set()
{
    delete operand1;
    delete operand2;
}

Print_Output set_binary_operator_set_set::getLatex(vector<vector<int> > split_point)
{
    string prefix_1 = "";
    string suffix_1 = "";
    string prefix_2 = "";
    string suffix_2 = "";
    if(operator_latex == "pair_set")
    {
        prefix_1 = "\\{ ";
        suffix_1 = " ,";
        suffix_2 = " \\}";
    }
    else if(operator_latex == "\\cup" ||
            operator_latex == "+")
    {
        prefix_2 = operator_latex + " ";
    }
    else
    {
        cout << "Syntax Error: the operator cannot be processed: " << operator_latex << endl;
        Print_Output output;
        return output;
    }

    return expression::getLatex_aux_2_operand(split_point, operand1, operand2, prefix_1, suffix_1, prefix_2, suffix_2);
}

bool set_binary_operator_set_set::isEqual(expression* x)
{
    return isEqual_2_operand<set_binary_operator_set_set>(this, x);
}

expression* set_binary_operator_set_set::getCopy()
{
    return getCopy_2_operand<set_binary_operator_set_set, Set>(this);
}

void set_binary_operator_set_set::replace_variable(vector<substitution*> replacement)
{
    operand1->replace_variable(replacement);
    operand2->replace_variable(replacement);
}

bool set_binary_operator_set_set::check_variable(vector<variable*> var_list)
{
    return (operand1->check_variable(var_list) && operand2->check_variable(var_list));
}

expression* set_binary_operator_set_set::getPart(vector<int> path)
{
    return getPart_2_operand<set_binary_operator_set_set>(this, path);
}

void set_binary_operator_set_set::getPartExternalDependence(vector<int> path, vector<variable*>& dependence)
{
    getPartExternalDependence_2_operand<set_binary_operator_set_set>(this, path, dependence);
}

void set_binary_operator_set_set::getInternalDependence(vector<variable*>& dependence)
{
    operand1->getInternalDependence(dependence);
    operand2->getInternalDependence(dependence);
}

void set_binary_operator_set_set::find_path_of_variable(variable* var, vector<int> current_path, vector<vector<int> >& all_path)
{
    find_path_of_variable_2_operand<set_binary_operator_set_set>(this, var, current_path, all_path);
}

bool set_binary_operator_set_set::contain_variable(variable* x)
{
    return (operand1->contain_variable(x) || operand2->contain_variable(x));
}
