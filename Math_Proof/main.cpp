//
//  main.cpp
//  Math_Proof
//
//  Created by Samuel on 13/9/2021.
//  Copyright © 2021 Samuel. All rights reserved.
//

#include <iostream>
using namespace std;

#include "logic.hpp"

int main()
{
    vector<Definition*> All_Definition;
    vector<Axiom*> All_Axiom;
    vector<Proposition*> All_Proposition;
    
    logic(All_Definition, All_Axiom, All_Proposition);
    
    for(long i=0;i<All_Definition.size();i++)
    {
        delete All_Definition[i];
    }
    
    for(long i=0;i<All_Axiom.size();i++)
    {
        delete All_Axiom[i];
    }
    
    for(long i=0;i<All_Proposition.size();i++)
    {
        delete All_Proposition[i];
    }
}
