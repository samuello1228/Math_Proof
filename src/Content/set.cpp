//
//  set.cpp
//  Math_Proof
//
//  Created by Samuel on 2/10/2021.
//  Copyright © 2021 Samuel. All rights reserved.
//

#include "set.hpp"

void set()
{
    ofstream fout;
    fout.open("../tex/set.tex");
    fout<<"\\chapter{Set theory}"<<endl;
    fout<<"Set theory have one primitive notion, called set, and one binary relation, called set membership, denoted by $\\in$."<<endl;
    fout<<endl;
    
    Axiom* axiom = nullptr;
    proof_block* block = nullptr;
    vector<substitution*> sub;
    string description;
    
    //notin
    Definition::addDefinition(fout, new Definition("notin", SET, "\\forall a \\forall b ((a \\notin b) \\iff (\\lnot (a \\in b)))"), "Definition of $\\notin$.");
    
    fout<<"\\begin{defn}"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& \\forall a \\in S, P(a) \\\\"<<endl;
    fout<<"\\overset{\\operatorname{def}}{\\iff} & \\forall a ((a \\in S) \\implies (P(a)))"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{defn}"<<endl;
    fout<<endl;
    
    fout<<"\\begin{defn}"<<endl;
    fout<<"\\begin{align*}"<<endl;
    fout<<"& \\exists a \\in S, P(a) \\\\"<<endl;
    fout<<"\\overset{\\operatorname{def}}{\\iff} & \\exists a ((a \\in S) \\land (P(a)))"<<endl;
    fout<<"\\end{align*}"<<endl;
    fout<<"\\end{defn}"<<endl;
    fout<<endl;
    
    //Equality
    fout<<"\\section{Equality of sets}"<<endl;
    Definition::addDefinition(fout, new Definition("equality", SET, "\\forall a \\forall b ((a = b) \\iff (\\forall c ((c \\in a) \\iff (c \\in b))))"), "Definition of $=$.");
    
    Definition::addDefinition(fout, new Definition("neq", SET, "\\forall a \\forall b ((a \\neq b) \\iff (\\lnot (a = b)))"), "Definition of $\\neq$.");
    
    Proposition::Current = new Proposition("equality_reflexive", SET, "\\forall a (a = a)");
    description = "Reflexive property of equality.";
    block = new proof_block(backward);
    block->append(input({}, "Definition:equality", LeftToRight));
    block->append(input({1}, "Proposition:iff_reflexive", PToTrue));
    block->append(input({}, "Axiom:forall_independent_variable", LeftToRight, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    Proposition::Current = new Proposition("equality_symmetric", SET, "\\forall a \\forall b ((a = b) \\iff (b = a))");
    description = "Symmetric property of equality.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Definition:equality", LeftToRight));
    block->append(input({1}, "Proposition:iff_symmetric", LeftToRight));
    block->append(input({}, "Definition:equality", RightToLeft, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    Proposition::Current = new Proposition("equality_transitive", SET, "\\forall a \\forall b \\forall c (((a = b) \\land (b = c)) \\implies (a = c))");
    description = "Transitive property of equality.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({1}, "Definition:equality", LeftToRight));
    block->append(input({2}, "Definition:equality", LeftToRight));
    block->append(input({}, "Proposition:forall_land_commutativity", LeftToRight));
    block->append(input({1}, "Proposition:iff_transitive", LeftToRight));
    block->append(input({}, "Definition:equality", RightToLeft, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    axiom = new Axiom("extensionality", SET, "\\forall a \\forall b ((a = b) \\implies (\\forall c ((a \\in c) \\iff (b \\in c))))");
    Axiom::addAxiom(fout, axiom, "Axiom of extensionality");
    
    fout<<"\\subsection{Axiom of Substitution for $\\in$}"<<endl;
    Proposition::Current = new Proposition("equality_substitution_in_1", SET, "\\forall a \\forall b \\forall c ((a = b) \\implies ((c \\in a) \\iff (c \\in b)))");
    description = "Substitution of $=$ for $\\in$.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Definition:equality", LeftToRight));
    block->append(input({}, expression::createFromLatex("c", SET), true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    Proposition::Current = new Proposition("equality_substitution_in_2", SET, "\\forall a \\forall b \\forall c ((a = b) \\implies ((a \\in c) \\iff (b \\in c)))");
    description = "Substitution of $=$ for $\\in$.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Axiom:extensionality", LeftToRight));
    block->append(input({}, expression::createFromLatex("c", SET), true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    fout<<"\\subsection{Axiom of Substitution for $=$}"<<endl;
    Proposition::Current = new Proposition("equality_substitution_equality", SET, "\\forall a \\forall b \\forall c ((a = b) \\implies ((a = c) \\iff (b = c)))");
    description = "Substitution of $=$ for $=$.";
    block = new proof_block(backward);
    block->append(input({}, "Proposition:lemma_substitution", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({1,1,1}, "Proposition:equality_symmetric", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({1}, "Proposition:equality_transitive", PToTrue));
    block->set_split_point({{2}});
    block->append(input({2}, "Proposition:equality_transitive", PToTrue));
    block->append(input({}, "Definition:land_True_True", LeftToRight, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    fout<<"\\subsection{Basic Propositions}"<<endl;
    Proposition::Current = new Proposition("equality_property_1", SET, "\\forall a \\forall b ((a = b) \\iff (\\forall c ((c = a) \\iff (c = b))))");
    description = "Property of $=$.";
    
    block = new proof_block("1", Proposition("", SET, "\\forall a \\forall b ((a = b) \\implies (\\forall c ((c = a) \\iff (c = b))))"), direct);
    sub.clear();
    sub.push_back(new substitution("a", "a", SET));
    sub.push_back(new substitution("b", "b", SET));
    block->append(input({}, "Proposition:equality_substitution_equality", TrueToP, sub));
    block->append(input({}, "Proposition:implies_forall_distributivity", RightToLeft));
    block->append(input({2,1,1}, "Proposition:equality_symmetric", LeftToRight));
    block->append(input({2,1,2}, "Proposition:equality_symmetric", LeftToRight, true));
    Proposition::Current->append(block);
    
    block = new proof_block("2", Proposition("", SET, "\\forall a \\forall b ((\\forall c ((c = a) \\iff (c = b))) \\implies (a = b))"), deduction_LeftToRight);
    block->append(input({}, expression::createFromLatex("a", SET)));
    block->append(input({1}, "Proposition:equality_reflexive", PToTrue));
    block->append(input({}, "Proposition:iff_symmetric", LeftToRight));
    block->append(input({}, "Proposition:true_statement", LeftToRight, true));
    Proposition::Current->append(block);
    
    block = new proof_block(backward);
    block->append(input({}, "Proposition:iff_implies", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({1}, "Local:1", PToTrue));
    block->append(input({2}, "Local:2", PToTrue));
    block->append(input({}, "Definition:land_True_True", LeftToRight, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    Proposition::Current = new Proposition("equality_property_2", SET, "\\forall a \\forall b \\forall c ((a = b) \\iff (\\forall d (((d = a) \\lor (d = c)) \\iff ((d = b) \\lor (d = c)))))");
    description = "Property of $=$.";
    
    block = new proof_block("1", Proposition("", SET, "\\forall a \\forall b \\forall c ((a = b) \\implies (\\forall d (((d = a) \\lor (d = c)) \\iff ((d = b) \\lor (d = c)))))"), deduction_LeftToRight);
    block->append(input({}, "Proposition:equality_property_1", LeftToRight));
    {
        sub.clear();
        logic_variable* var = new logic_variable("a");
        expression* d = expression::createFromLatex("d = a", SET);
        sub.push_back(new substitution(var, d));
        
        var = new logic_variable("b");
        d = expression::createFromLatex("d = b", SET);
        sub.push_back(new substitution(var, d));
        
        var = new logic_variable("c");
        d = expression::createFromLatex("d = c", SET);
        sub.push_back(new substitution(var, d));
    }
    block->append(input({1}, "Proposition:iff_substitution_lor", LeftToRight, sub, true));
    Proposition::Current->append(block);
    
    block = new proof_block("2", Proposition("", SET, "\\forall a \\forall b \\forall c ((\\forall d (((d = a) \\lor (d = c)) \\iff ((d = b) \\lor (d = c)))) \\implies (a = b))"), deduction_LeftToRight);
    block->append(input({}, "Proposition:land_idempotence", RightToLeft));
    block->set_split_point({{2}});
    block->append(input({1}, expression::createFromLatex("a", SET)));
    block->set_split_point({{2}});
    block->append(input({2}, expression::createFromLatex("b", SET)));
    block->set_split_point({{2}});
    block->append(input({1,1,1}, "Proposition:equality_reflexive", PToTrue));
    block->set_split_point({{2}});
    block->append(input({1,1}, "Proposition:lor_annihilator_2", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({1}, "Proposition:iff_symmetric", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({1}, "Proposition:true_statement", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({2,2,1}, "Proposition:equality_reflexive", PToTrue));
    block->set_split_point({{2}});
    block->append(input({2,2}, "Proposition:lor_annihilator_2", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({2}, "Proposition:true_statement", LeftToRight));
    block->append(input({2,1}, "Proposition:equality_symmetric", LeftToRight));
    block->append(input({}, "Proposition:lor_land_distributivity_1", RightToLeft));
    block->append(input({2,2}, "Proposition:equality_symmetric", LeftToRight));
    block->append(input({2}, "Proposition:equality_transitive", LeftToRight));
    block->append(input({}, "Proposition:lor_idempotence", LeftToRight, true));
    Proposition::Current->append(block);
    
    block = new proof_block(backward);
    block->append(input({}, "Proposition:iff_implies", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({1}, "Local:1", PToTrue));
    block->set_split_point({{2}});
    block->append(input({2}, "Local:2", PToTrue));
    block->append(input({}, "Definition:land_True_True", LeftToRight, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    fout<<"\\subsection{Empty set}"<<endl;
    axiom = new Axiom("existence_of_empty_set", SET, "\\forall a (a \\notin \\emptyset)");
    Axiom::addAxiom(fout, axiom, "Existence of empty set");
    
    Proposition::Current = new Proposition("uniqueness_of_empty_set", SET, "\\forall a ((\\forall b (b \\notin a)) \\iff (a = \\emptyset))");
    description = "Uniqueness of $\\emptyset$";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({1}, "Proposition:true_statement", RightToLeft));
    sub.clear(); sub.push_back(new substitution("a", "b", SET));
    block->append(input({1,2}, "Axiom:existence_of_empty_set", TrueToP, sub));
    block->append(input({1,1}, "Definition:notin", LeftToRight));
    block->append(input({1,2}, "Definition:notin", LeftToRight));
    block->append(input({1}, "Proposition:iff_substitution_lnot", RightToLeft));
    block->append(input({}, "Definition:equality", RightToLeft, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    Proposition::Current = new Proposition("single_choice", SET, "\\forall a ((a \\neq \\emptyset) \\iff (\\exists b (b \\in a)))");
    description = "Single choice";
    block = new proof_block(direct);
    sub.clear(); sub.push_back(new substitution("a", "a", SET));
    block->append(input({}, "Proposition:uniqueness_of_empty_set", TrueToP, sub));
    block->append(input({}, "Proposition:iff_symmetric", LeftToRight));
    block->append(input({}, "Proposition:iff_substitution_lnot", LeftToRight));
    block->append(input({1}, "Definition:neq", RightToLeft));
    block->append(input({2}, "Proposition:De_Morgan_1", LeftToRight));
    block->append(input({2,1,1}, "Definition:notin", LeftToRight));
    block->append(input({2,1}, "Proposition:double_negation", LeftToRight, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    fout<<"\\subsection{Pair set}"<<endl;
    axiom = new Axiom("existence_of_pair_set", SET, "\\forall a \\forall b \\forall c ((c \\in \\{ a , b \\}) \\iff ((c = a) \\lor (c = b)))");
    Axiom::addAxiom(fout, axiom, "Existence of pair set");
    
    Proposition::Current = new Proposition("uniqueness_of_pair_set", SET, "\\forall a \\forall b \\forall c ((\\forall d ((d \\in c) \\iff ((d = a) \\lor (d = b)))) \\implies (c = \\{ a , b \\}))");
    description = "Uniqueness of pair set";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({1}, "Proposition:land_identity_1", RightToLeft));
    sub.clear();
    sub.push_back(new substitution("a", "a", SET));
    sub.push_back(new substitution("b", "b", SET));
    sub.push_back(new substitution("c", "d", SET));
    block->append(input({1,2}, "Axiom:existence_of_pair_set", TrueToP, sub));
    block->set_split_point({{1,2}});
    block->append(input({1,2}, "Proposition:iff_symmetric", LeftToRight));
    block->set_split_point({{1,2}});
    block->append(input({1}, "Proposition:iff_transitive", LeftToRight));
    block->append(input({}, "Definition:equality", RightToLeft, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    Proposition::Current = new Proposition("equality_substitution_pair_set", SET, "\\forall a \\forall b \\forall c ((a = b) \\iff (\\{ a , c \\} = \\{ b , c \\}))");
    description = "Axiom of Substitution for pair set.";
    block = new proof_block(deduction_RightToLeft);
    block->append(input({}, "Definition:equality", LeftToRight));
    block->append(input({1,1}, "Axiom:existence_of_pair_set", LeftToRight));
    block->append(input({1,2}, "Axiom:existence_of_pair_set", LeftToRight));
    block->append(input({}, "Proposition:equality_property_2", RightToLeft, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    fout<<"\\subsection{Singleton set}"<<endl;
    Definition::addDefinition(fout, new Definition("singleton_set", SET, "\\forall a (\\{ a \\} = \\{ a , a \\})"), "Definition of singleton set.");
    
    //Property of singleton set
    Proposition::Current = new Proposition("singleton_set_property", SET, "\\forall a \\forall b ((b \\in \\{ a \\}) \\iff (b = a))");
    description = "Property of singleton set.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({2}, "Definition:singleton_set", LeftToRight));
    block->append(input({}, "Axiom:existence_of_pair_set", LeftToRight));
    block->append(input({}, "Proposition:lor_idempotence", LeftToRight, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    //Uniqueness of singleton set
    Proposition::Current = new Proposition("uniqueness_of_singleton_set", SET, "\\forall a \\forall b ((\\forall c ((c \\in b) \\iff (c = a))) \\implies (b = \\{ a \\}))");
    description = "Uniqueness of singleton set.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({1}, "Proposition:land_identity_1", RightToLeft));
    sub.clear();
    sub.push_back(new substitution("a", "a", SET));
    sub.push_back(new substitution("b", "c", SET));
    block->append(input({1,2}, "Proposition:singleton_set_property", TrueToP, sub));
    block->set_split_point({{1,2}});
    block->append(input({1,2}, "Proposition:iff_symmetric", LeftToRight));
    block->set_split_point({{1,2}});
    block->append(input({1}, "Proposition:iff_transitive", LeftToRight));
    block->append(input({}, "Definition:equality", RightToLeft, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    Proposition::Current = new Proposition("equality_substitution_singleton_set", SET, "\\forall a \\forall b ((a = b) \\iff (\\{ a \\} = \\{ b \\}))");
    description = "Axiom of Substitution for singleton set.";
    block = new proof_block(deduction_RightToLeft);
    block->append(input({1}, "Definition:singleton_set", LeftToRight));
    block->append(input({2}, "Definition:singleton_set", LeftToRight));
    block->append(input({}, "Definition:equality", LeftToRight));
    block->append(input({1,1}, "Axiom:existence_of_pair_set", LeftToRight));
    block->append(input({1,2}, "Axiom:existence_of_pair_set", LeftToRight));
    block->append(input({1,1}, "Proposition:lor_idempotence", LeftToRight));
    block->append(input({1,2}, "Proposition:lor_idempotence", LeftToRight));
    block->append(input({}, "Proposition:equality_property_1", RightToLeft, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    fout<<"\\subsection{Union set}"<<endl;
    axiom = new Axiom("existence_of_union_set", SET, "\\forall a \\forall b ((b \\in (\\bigcup a)) \\iff (\\exists c ((b \\in c) \\land (c \\in a))))");
    Axiom::addAxiom(fout, axiom, "Existence of union set.");
    
    //Uniqueness of union set
    Proposition::Current = new Proposition("uniqueness_of_union_set", SET, "\\forall a \\forall b ((\\forall c ((c \\in b) \\iff (\\exists d ((c \\in d) \\land (d \\in a))))) \\implies (b = (\\bigcup a)))");
    description = "Uniqueness of union set.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({1}, "Proposition:land_identity_1", RightToLeft));
    sub.clear();
    sub.push_back(new substitution("a", "a", SET));
    sub.push_back(new substitution("b", "c", SET));
    block->append(input({1,2}, "Axiom:existence_of_union_set", TrueToP, sub));
    block->set_split_point({{1,2}});
    block->append(input({1,2}, "Proposition:iff_symmetric", LeftToRight));
    block->set_split_point({{1,2}});
    block->append(input({1}, "Proposition:iff_transitive", LeftToRight));
    block->append(input({}, "Definition:equality", RightToLeft, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    Proposition::Current = new Proposition("equality_substitution_union_set", SET, "\\forall a \\forall b ((a = b) \\implies ((\\bigcup a) = (\\bigcup b)))");
    description = "Axiom of Substitution for union set.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Axiom:forall_independent_variable", RightToLeft));
    block->append(input({1}, "Axiom:forall_independent_variable", RightToLeft));
    sub.clear();
    sub.push_back(new substitution("a", "a", SET));
    sub.push_back(new substitution("b", "b", SET));
    sub.push_back(new substitution("c", "d", SET));
    block->append(input({1,1}, "Proposition:equality_substitution_in_1", LeftToRight, sub));
    sub.clear();
    sub.push_back(new substitution("a", "d \\in a", SET));
    sub.push_back(new substitution("b", "d \\in b", SET));
    sub.push_back(new substitution("c", "c \\in d", SET));
    block->append(input({1,1}, "Proposition:iff_substitution_land", LeftToRight, sub));
    block->append(input({1,1,1}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({1,1,2}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({1}, "Proposition:iff_substitution_exists_2", LeftToRight));
    block->append(input({1,1}, "Axiom:existence_of_union_set", RightToLeft));
    block->append(input({1,2}, "Axiom:existence_of_union_set", RightToLeft));
    block->append(input({}, "Definition:equality", RightToLeft, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    fout<<"\\subsection{Pairwise union}"<<endl;
    Definition::addDefinition(fout, new Definition("pairwise_union", SET, "\\forall a \\forall b ((a \\cup b) = (\\bigcup \\{ a , b \\}))"), "Definition of pairwise union $a \\cup b$.");
    
    //Property of pairwise union
    Proposition::Current = new Proposition("pairwise_union_property", SET, "\\forall a \\forall b \\forall c ((c \\in (a \\cup b)) \\iff ((c \\in a) \\lor (c \\in b)))");
    description = "Property of pairwise union.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({2}, "Definition:pairwise_union", LeftToRight));
    block->append(input({}, "Axiom:existence_of_union_set", LeftToRight));
    block->append(input({1,2}, "Axiom:existence_of_pair_set", LeftToRight));
    block->append(input({1}, "Proposition:land_lor_distributivity_1", LeftToRight));
    block->append(input({}, "Proposition:exists_lor_commutativity", RightToLeft));
    block->append(input({1,1}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({2,1}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({1}, "Axiom:axiom_of_existence", RightToLeft));
    block->append(input({2}, "Axiom:axiom_of_existence", RightToLeft, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    Proposition::Current = new Proposition("equality_substitution_pairwise_union", SET, "\\forall a \\forall b \\forall c ((a = b) \\implies ((a \\cup c) = (b \\cup c)))");
    description = "Axiom of Substitution for pairwise union.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Definition:equality", LeftToRight));
    sub.clear();
    sub.push_back(new substitution("a", "d \\in a", SET));
    sub.push_back(new substitution("b", "d \\in b", SET));
    sub.push_back(new substitution("c", "d \\in c", SET));
    block->append(input({1}, "Proposition:iff_substitution_lor", LeftToRight, sub));
    block->append(input({1,1}, "Proposition:pairwise_union_property", RightToLeft));
    block->append(input({1,2}, "Proposition:pairwise_union_property", RightToLeft));
    block->append(input({}, "Definition:equality", RightToLeft, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    Proposition::Current = new Proposition("pairwise_union_commutativity", SET, "\\forall a \\forall b ((a \\cup b) = (b \\cup a))");
    description = "Commutativity of $\\cup$.";
    block = new proof_block(backward);
    block->append(input({}, "Definition:equality", LeftToRight));
    block->append(input({1,1}, "Proposition:pairwise_union_property", LeftToRight));
    block->append(input({1,2}, "Proposition:pairwise_union_property", LeftToRight));
    block->append(input({1,2}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({1}, "Proposition:iff_reflexive", PToTrue));
    block->append(input({}, "Axiom:forall_independent_variable", LeftToRight, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    Proposition::Current = new Proposition("pairwise_union_identity", SET, "\\forall a ((a \\cup \\emptyset) = a)");
    description = "Identity of $\\cup$.";
    block = new proof_block(backward);
    block->append(input({}, "Definition:equality", LeftToRight));
    block->append(input({1,1}, "Proposition:pairwise_union_property", LeftToRight));
    block->append(input({1,1,2}, "Proposition:double_negation", RightToLeft));
    block->append(input({1,1,2,1}, "Definition:notin", RightToLeft));
    block->append(input({1,1,2,1}, "Axiom:existence_of_empty_set", PToTrue));
    block->append(input({1,1,2}, "Definition:lnot_True", LeftToRight));
    block->append(input({1,1}, "Proposition:lor_identity_1", LeftToRight));
    block->append(input({1}, "Proposition:iff_reflexive", PToTrue));
    block->append(input({}, "Axiom:forall_independent_variable", LeftToRight, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    fout<<"\\subsection{Integer}"<<endl;
    //zero
    Definition::addDefinition(fout, new Definition("zero", SET, "0 = \\emptyset"), "Definition of 0.");
    
    //successor
    Definition::addDefinition(fout, new Definition("successor", SET, "\\forall a ((S(a)) = (a \\cup \\{ a \\}))"), "Definition of successor $S(x)$.");
    
    //one
    Definition::addDefinition(fout, new Definition("one", SET, "1 = (S(0))"), "Definition of 1.");
    
    Proposition::Current = new Proposition("one_expand", SET, "1 = \\{ \\emptyset \\}");
    description = "Express 1 in term of $\\emptyset$.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Definition:one", LeftToRight));
    block->append(input({1}, "Definition:zero", LeftToRight));
    block->append(input({}, "Definition:successor", LeftToRight));
    block->append(input({}, "Proposition:pairwise_union_commutativity", LeftToRight));
    block->append(input({}, "Proposition:pairwise_union_identity", LeftToRight, true));
    Proposition::Current->append(block, true);
    Proposition::addProposition(fout, Proposition::Current, description);
    
    fout.close();
}
