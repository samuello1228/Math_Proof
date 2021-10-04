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
#include "set.hpp"

int main()
{
    logic();
    set();
    
    for(long i=0;i<Definition::All_Definition.size();i++)
    {
        delete Definition::All_Definition[i];
    }
    
    for(long i=0;i<Axiom::All_Axiom.size();i++)
    {
        delete Axiom::All_Axiom[i];
    }
    
    for(long i=0;i<Proposition::All_Proposition.size();i++)
    {
        delete Proposition::All_Proposition[i];
    }
    
    //while(true) {}
}
