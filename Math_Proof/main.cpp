//
//  main.cpp
//  Math_Proof
//
//  Created by Samuel on 13/9/2021.
//  Copyright © 2021 Samuel. All rights reserved.
//

#include <iostream>
using namespace std;

#include "statement.hpp"

int main()
{
    //expression* x = expression::createFromLatex("(\\text{True} ) \\lor (\\lnot (\\text{False}))", LOGIC);
    expression* x = expression::createFromLatex("\\forall x (x \\land (\\lnot (\\text{False})))", LOGIC);
    if(x != nullptr)
    {
        cout<< x->getLatex() <<endl;
        delete x;
    }
}
