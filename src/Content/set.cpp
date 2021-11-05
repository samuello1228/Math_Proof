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
    ofstream& fout = statement::fout;
    fout.open("../tex/set.tex");
    fout<<"\\chapter{Set theory}"<<endl;
    fout<<"Set theory have one primitive notion, called set, and one binary relation, called set membership, denoted by $\\in$."<<endl;
    fout<<endl;
    
    proof_block* block = nullptr;
    vector<substitution*> sub;
    string description;
    
    //notin
    Definition::Current = new Definition("notin", SET, "\\forall a \\forall b ((a \\notin b) \\iff (\\lnot (a \\in b)))");
    Definition::addDefinition("Definition of $\\notin$.");
    
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
    Definition::Current = new Definition("equality", SET, "\\forall a \\forall b ((a = b) \\iff (\\forall c ((c \\in a) \\iff (c \\in b))))");
    Definition::addDefinition("Definition of $=$.");
    
    Definition::Current = new Definition("neq", SET, "\\forall a \\forall b ((a \\neq b) \\iff (\\lnot (a = b)))");
    Definition::addDefinition("Definition of $\\neq$.");
    
    Proposition::Current = new Proposition("equality_reflexive", SET, "\\forall a (a = a)");
    description = "Reflexive property of equality.";
    block = new proof_block(backward);
    block->append(input({}, "Definition:equality", LeftToRight));
    block->append(input({1}, "Proposition:iff_reflexive", PToTrue));
    block->append(input({}, "Axiom:forall_independent_variable", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
    Proposition::Current = new Proposition("equality_symmetric", SET, "\\forall a \\forall b ((a = b) \\iff (b = a))");
    description = "Symmetric property of equality.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Definition:equality", LeftToRight));
    block->append(input({1}, "Proposition:iff_symmetric", LeftToRight));
    block->append(input({}, "Definition:equality", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
    Proposition::Current = new Proposition("equality_transitive", SET, "\\forall a \\forall b \\forall c (((a = b) \\land (b = c)) \\implies (a = c))");
    description = "Transitive property of equality.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({1}, "Definition:equality", LeftToRight));
    block->append(input({2}, "Definition:equality", LeftToRight));
    block->append(input({}, "Proposition:forall_land_commutativity", LeftToRight));
    block->append(input({1}, "Proposition:iff_transitive", LeftToRight));
    block->append(input({}, "Definition:equality", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
    Axiom::Current = new Axiom("extensionality", SET, "\\forall a \\forall b ((a = b) \\implies (\\forall c ((a \\in c) \\iff (b \\in c))))");
    Axiom::addAxiom("Axiom of extensionality");
    
    fout<<"\\subsection{Axiom of Substitution for $\\in$}"<<endl;
    Proposition::Current = new Proposition("equality_substitution_in_1", SET, "\\forall a \\forall b \\forall c ((a = b) \\implies ((c \\in a) \\iff (c \\in b)))");
    description = "Substitution of $=$ for $\\in$.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Definition:equality", LeftToRight));
    block->append(input({}, expression::createFromLatex("c", SET)));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
    Proposition::Current = new Proposition("equality_substitution_in_2", SET, "\\forall a \\forall b \\forall c ((a = b) \\implies ((a \\in c) \\iff (b \\in c)))");
    description = "Substitution of $=$ for $\\in$.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Axiom:extensionality", LeftToRight));
    block->append(input({}, expression::createFromLatex("c", SET)));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
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
    block->append(input({}, "Definition:land_True_True", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
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
    block->append(input({2,1,2}, "Proposition:equality_symmetric", LeftToRight));
    Proposition::Current->append(block);
    
    block = new proof_block("2", Proposition("", SET, "\\forall a \\forall b ((\\forall c ((c = a) \\iff (c = b))) \\implies (a = b))"), deduction_LeftToRight);
    block->append(input({}, expression::createFromLatex("a", SET)));
    block->append(input({1}, "Proposition:equality_reflexive", PToTrue));
    block->append(input({}, "Proposition:iff_symmetric", LeftToRight));
    block->append(input({}, "Proposition:true_statement", LeftToRight));
    Proposition::Current->append(block);
    
    block = new proof_block(backward);
    block->append(input({}, "Proposition:iff_implies", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({1}, "Local:1", PToTrue));
    block->append(input({2}, "Local:2", PToTrue));
    block->append(input({}, "Definition:land_True_True", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
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
    block->append(input({1}, "Proposition:iff_substitution_lor", LeftToRight, sub));
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
    block->append(input({}, "Proposition:lor_idempotence", LeftToRight));
    Proposition::Current->append(block);
    
    block = new proof_block(backward);
    block->append(input({}, "Proposition:iff_implies", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({1}, "Local:1", PToTrue));
    block->set_split_point({{2}});
    block->append(input({2}, "Local:2", PToTrue));
    block->append(input({}, "Definition:land_True_True", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
    fout<<"\\subsection{Empty set}"<<endl;
    Axiom::Current = new Axiom("existence_of_empty_set", SET, "\\forall a (a \\notin \\emptyset)");
    Axiom::addAxiom("Existence of empty set");
    
    Proposition::Current = new Proposition("uniqueness_of_empty_set", SET, "\\forall a ((\\forall b (b \\notin a)) \\iff (a = \\emptyset))");
    description = "Uniqueness of $\\emptyset$";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({1}, "Proposition:true_statement", RightToLeft));
    sub.clear(); sub.push_back(new substitution("a", "b", SET));
    block->append(input({1,2}, "Axiom:existence_of_empty_set", TrueToP, sub));
    block->append(input({1,1}, "Definition:notin", LeftToRight));
    block->append(input({1,2}, "Definition:notin", LeftToRight));
    block->append(input({1}, "Proposition:iff_substitution_lnot", RightToLeft));
    block->append(input({}, "Definition:equality", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
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
    block->append(input({2,1}, "Proposition:double_negation", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
    fout<<"\\subsection{Pair set}"<<endl;
    Axiom::Current = new Axiom("existence_of_pair_set", SET, "\\forall a \\forall b \\forall c ((c \\in \\{ a , b \\}) \\iff ((c = a) \\lor (c = b)))");
    Axiom::addAxiom("Existence of pair set");
    
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
    block->append(input({}, "Definition:equality", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
    Proposition::Current = new Proposition("equality_substitution_pair_set", SET, "\\forall a \\forall b \\forall c ((a = b) \\iff (\\{ a , c \\} = \\{ b , c \\}))");
    description = "Axiom of Substitution for pair set.";
    block = new proof_block(deduction_RightToLeft);
    block->append(input({}, "Definition:equality", LeftToRight));
    block->append(input({1,1}, "Axiom:existence_of_pair_set", LeftToRight));
    block->append(input({1,2}, "Axiom:existence_of_pair_set", LeftToRight));
    block->append(input({}, "Proposition:equality_property_2", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
    Proposition::Current = new Proposition("pair_set_commutativity", SET, "\\forall a \\forall b (\\{ a , b \\} = \\{ b , a \\})");
    description = "Commutativity of pair set.";
    block = new proof_block(backward);
    block->append(input({}, "Definition:equality", LeftToRight));
    block->append(input({1,1}, "Axiom:existence_of_pair_set", LeftToRight));
    block->append(input({1,2}, "Axiom:existence_of_pair_set", LeftToRight));
    block->append(input({1,2}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({1}, "Proposition:iff_reflexive", PToTrue));
    block->append(input({}, "Axiom:forall_independent_variable", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
    fout<<"\\subsection{Singleton set}"<<endl;
    Definition::Current = new Definition("singleton_set", SET, "\\forall a (\\{ a \\} = \\{ a , a \\})");
    Definition::addDefinition("Definition of singleton set.");
    
    //Property of singleton set
    Proposition::Current = new Proposition("singleton_set_property", SET, "\\forall a \\forall b ((b \\in \\{ a \\}) \\iff (b = a))");
    description = "Property of singleton set.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({2}, "Definition:singleton_set", LeftToRight));
    block->append(input({}, "Axiom:existence_of_pair_set", LeftToRight));
    block->append(input({}, "Proposition:lor_idempotence", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
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
    block->append(input({}, "Definition:equality", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
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
    block->append(input({}, "Proposition:equality_property_1", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
    fout<<"\\subsection{Union set}"<<endl;
    Axiom::Current = new Axiom("existence_of_union_set", SET, "\\forall a \\forall b ((b \\in (\\bigcup a)) \\iff (\\exists c ((b \\in c) \\land (c \\in a))))");
    Axiom::addAxiom("Existence of union set.");
    
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
    block->append(input({}, "Definition:equality", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
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
    block->append(input({}, "Definition:equality", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
    fout<<"\\subsection{Pairwise union}"<<endl;
    Definition::Current = new Definition("pairwise_union", SET, "\\forall a \\forall b ((a \\cup b) = (\\bigcup \\{ a , b \\}))");
    Definition::addDefinition("Definition of pairwise union $a \\cup b$.");
    
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
    block->append(input({2}, "Axiom:axiom_of_existence", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
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
    block->append(input({}, "Definition:equality", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
    Proposition::Current = new Proposition("pairwise_union_commutativity", SET, "\\forall a \\forall b ((a \\cup b) = (b \\cup a))");
    description = "Commutativity of $\\cup$.";
    block = new proof_block(backward);
    block->append(input({}, "Definition:equality", LeftToRight));
    block->append(input({1,1}, "Proposition:pairwise_union_property", LeftToRight));
    block->append(input({1,2}, "Proposition:pairwise_union_property", LeftToRight));
    block->append(input({1,2}, "Proposition:lor_commutativity", LeftToRight));
    block->append(input({1}, "Proposition:iff_reflexive", PToTrue));
    block->append(input({}, "Axiom:forall_independent_variable", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
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
    block->append(input({}, "Axiom:forall_independent_variable", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
    Proposition::Current = new Proposition("pair_pairwise_union_singleton", SET, "\\forall a \\forall b (\\{ a , b \\} = (\\{ a \\} \\cup \\{ b \\}))");
    block = new proof_block(backward);
    block->append(input({}, "Definition:equality", LeftToRight));
    block->append(input({1,2}, "Proposition:pairwise_union_property", LeftToRight));
    block->append(input({1,2,1}, "Proposition:singleton_set_property", LeftToRight));
    block->append(input({1,2,2}, "Proposition:singleton_set_property", LeftToRight));
    block->append(input({1,1}, "Axiom:existence_of_pair_set", LeftToRight));
    block->append(input({1}, "Proposition:iff_reflexive", PToTrue));
    block->append(input({}, "Axiom:forall_independent_variable", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition();
    
    //Axiom of regularity
    fout<<"\\subsection{Axiom of regularity}"<<endl;
    Axiom::Current = new Axiom("axiom_of_regularity", SET, "\\forall a ((a \\neq \\emptyset) \\implies (\\exists b ((b \\in a) \\land ((b \\cup a) = \\emptyset))))");
    Axiom::addAxiom("Axiom of regularity.");
    
    Proposition::Current = new Proposition("in_property_1", SET, "\\forall a (a \\notin a)");
    description = "Property of $\\in$.";
    block = new proof_block(direct);
    sub.clear(); sub.push_back(new substitution("a", "a", SET));
    block->append(input({}, "Proposition:equality_reflexive", TrueToP, sub));
    block->append(input({}, "Proposition:singleton_set_property", RightToLeft));
    block->append(input({}, "Axiom:axiom_of_existence", LeftToRight, {{1}}));
    block->append(input({1}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({1}, "Proposition:a_land_b_implies_a", LeftToRight));
    block->append(input({}, "Proposition:single_choice", RightToLeft));
    block->append(input({}, "Axiom:axiom_of_regularity", LeftToRight));
    block->append(input({1,1}, "Proposition:singleton_set_property", LeftToRight));
    block->append(input({}, "Axiom:axiom_of_existence", RightToLeft));
    block->append(input({}, "Proposition:uniqueness_of_empty_set", RightToLeft));
    block->append(input({1}, "Definition:notin", LeftToRight));
    block->append(input({1,1}, "Proposition:pairwise_union_property", LeftToRight));
    block->append(input({}, expression::createFromLatex("a", SET)));
    block->append(input({}, "Proposition:De_Morgan_lor", LeftToRight));
    block->append(input({}, "Proposition:a_land_b_implies_a", LeftToRight));
    block->append(input({}, "Definition:notin", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
    Proposition::Current = new Proposition("in_property_2", SET, "\\forall a \\forall b ((a \\notin b) \\lor (b \\notin a))");
    description = "Property of $\\in$.";
    
    block = new proof_block("1", Proposition("", SET, "\\forall a \\forall b (((a \\cup \\{ a , b \\}) = \\emptyset) \\implies (b \\notin a))"), deduction_LeftToRight);
    block->append(input({}, "Proposition:uniqueness_of_empty_set", RightToLeft));
    block->append(input({1}, "Definition:notin", LeftToRight));
    block->append(input({1,1}, "Proposition:pairwise_union_property", LeftToRight));
    block->append(input({}, expression::createFromLatex("b", SET)));
    block->append(input({}, "Proposition:De_Morgan_lor", LeftToRight));
    block->append(input({}, "Proposition:a_land_b_implies_a", LeftToRight));
    block->append(input({}, "Definition:notin", RightToLeft));
    Proposition::Current->append(block);
    
    block = new proof_block(direct);
    sub.clear(); sub.push_back(new substitution("a", "a = b", SET));
    block->append(input({}, "Proposition:lor_annihilator_2", RightToLeft, sub));
    sub.clear(); sub.push_back(new substitution("a", "a", SET));
    block->append(input({1}, "Proposition:equality_reflexive", TrueToP, sub));
    block->append(input({}, "Axiom:existence_of_pair_set", RightToLeft));
    block->append(input({}, "Axiom:axiom_of_existence", LeftToRight, {{1}}));
    block->append(input({1}, "Proposition:land_commutativity", LeftToRight));
    block->append(input({1}, "Proposition:a_land_b_implies_a", LeftToRight));
    block->append(input({}, "Proposition:single_choice", RightToLeft));
    block->append(input({}, "Axiom:axiom_of_regularity", LeftToRight));
    block->append(input({1,1}, "Axiom:existence_of_pair_set", LeftToRight));
    block->append(input({1}, "Proposition:land_lor_distributivity_2", LeftToRight));
    block->set_split_point({{1,2}});
    block->append(input({}, "Proposition:exists_lor_commutativity", RightToLeft));
    block->set_split_point({{2}});
    block->append(input({1}, "Axiom:axiom_of_existence", RightToLeft));
    block->set_split_point({{2}});
    block->append(input({2}, "Axiom:axiom_of_existence", RightToLeft));
    block->append(input({1}, "Local:1", LeftToRight));
    block->append(input({2,1,2}, "Proposition:pair_set_commutativity", LeftToRight));
    block->append(input({2}, "Local:1", LeftToRight));
    block->append(input({}, "Proposition:lor_commutativity", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
    Proposition::Current = new Proposition("equality_property_3", SET, "\\forall a \\forall b ((a = b) \\iff (\\forall c (((c \\in a) \\lor (c = a)) \\iff ((c \\in b) \\lor (c = b)))))");
    description = "Property of $=$.";
    
    block = new proof_block("1", Proposition("", SET, "\\forall a \\forall b ((a = b) \\implies (\\forall c (((c \\in a) \\lor (c = a)) \\iff ((c \\in b) \\lor (c = b)))))"), deduction_LeftToRight);
    block->append(input({}, "Axiom:forall_independent_variable", RightToLeft));
    block->append(input({1}, "Proposition:land_idempotence", RightToLeft));
    sub.clear();
    sub.push_back(new substitution("a", "a", SET));
    sub.push_back(new substitution("b", "b", SET));
    sub.push_back(new substitution("c", "c", SET));
    block->append(input({1,1}, "Proposition:equality_substitution_in_1", LeftToRight, sub));
    sub.clear();
    sub.push_back(new substitution("a", "a", SET));
    sub.push_back(new substitution("b", "b", SET));
    sub.push_back(new substitution("c", "c", SET));
    block->append(input({1,2}, "Proposition:equality_substitution_equality", LeftToRight, sub));
    block->append(input({1}, "Proposition:iff_substitution_exists_1", LeftToRight));
    block->append(input({1,1,2}, "Proposition:equality_symmetric", LeftToRight));
    block->append(input({1,2,2}, "Proposition:equality_symmetric", LeftToRight));
    Proposition::Current->append(block);
    
    block = new proof_block("2", Proposition("", SET, "\\forall a \\forall b ((\\forall c (((c \\in a) \\lor (c = a)) \\iff ((c \\in b) \\lor (c = b)))) \\implies (a = b))"), deduction_LeftToRight);
    block->append(input({}, "Proposition:land_idempotence", RightToLeft));
    block->set_split_point({{2}});
    block->append(input({1}, expression::createFromLatex("a", SET)));
    block->set_split_point({{2}});
    block->append(input({2}, expression::createFromLatex("b", SET)));
    block->set_split_point({{2}});
    block->append(input({1,1,2}, "Proposition:equality_reflexive", PToTrue));
    block->set_split_point({{2}});
    block->append(input({1,1}, "Proposition:lor_annihilator_1", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({1}, "Proposition:iff_symmetric", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({1}, "Proposition:true_statement", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({2,2,2}, "Proposition:equality_reflexive", PToTrue));
    block->set_split_point({{2}});
    block->append(input({2,2}, "Proposition:lor_annihilator_1", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({2}, "Proposition:true_statement", LeftToRight));
    block->append(input({2,2}, "Proposition:equality_symmetric", LeftToRight));
    block->append(input({}, "Proposition:lor_land_distributivity_2", RightToLeft));
    block->append(input({1}, "Proposition:double_negation", RightToLeft));
    block->append(input({1,1}, "Proposition:De_Morgan_land", LeftToRight));
    block->append(input({1,1,1}, "Definition:notin", RightToLeft));
    block->append(input({1,1,2}, "Definition:notin", RightToLeft));
    block->append(input({1,1}, "Proposition:in_property_2", PToTrue));
    block->append(input({1}, "Definition:lnot_True", LeftToRight));
    block->append(input({}, "Proposition:lor_identity_2", LeftToRight));
    Proposition::Current->append(block);
    
    block = new proof_block(backward);
    block->append(input({}, "Proposition:iff_implies", LeftToRight));
    block->set_split_point({{2}});
    block->append(input({1}, "Local:1", PToTrue));
    block->set_split_point({{2}});
    block->append(input({2}, "Local:2", PToTrue));
    block->append(input({}, "Definition:land_True_True", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
    //subset
    fout<<"\\subsection{Subset}"<<endl;
    Definition::Current = new Definition("subset", SET, "\\forall a \\forall b ((a \\subseteq b) \\iff (\\forall c ((c \\in a) \\implies (c \\in b))))");
    Definition::addDefinition("Definition of $\\subseteq$.");
    
    Proposition::Current = new Proposition("equality_substitution_subset_1", SET, "\\forall a \\forall b \\forall c ((a = b) \\implies ((a \\subseteq c) \\iff (b \\subseteq c)))");
    description = "Axiom of Substitution for subset.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Definition:equality", LeftToRight));
    sub.clear();
    sub.push_back(new substitution("a", "d \\in a", SET));
    sub.push_back(new substitution("b", "d \\in b", SET));
    sub.push_back(new substitution("c", "d \\in c", SET));
    block->append(input({1}, "Proposition:iff_substitution_implies_1", LeftToRight, sub));
    block->append(input({}, "Proposition:iff_substitution_forall_2", LeftToRight));
    block->append(input({1}, "Definition:subset", RightToLeft));
    block->append(input({2}, "Definition:subset", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
    Proposition::Current = new Proposition("equality_substitution_subset_2", SET, "\\forall a \\forall b \\forall c ((a = b) \\implies ((c \\subseteq a) \\iff (c \\subseteq b)))");
    description = "Axiom of Substitution for subset.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Definition:equality", LeftToRight));
    sub.clear();
    sub.push_back(new substitution("a", "d \\in a", SET));
    sub.push_back(new substitution("b", "d \\in b", SET));
    sub.push_back(new substitution("c", "d \\in c", SET));
    block->append(input({1}, "Proposition:iff_substitution_implies_2", LeftToRight, sub));
    block->append(input({}, "Proposition:iff_substitution_forall_2", LeftToRight));
    block->append(input({1}, "Definition:subset", RightToLeft));
    block->append(input({2}, "Definition:subset", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
    Proposition::Current = new Proposition("subset_transitive", SET, "\\forall a \\forall b \\forall c (((a \\subseteq b) \\land (b \\subseteq c)) \\implies (a \\subseteq c))");
    description = "Transitive property of subset.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({1}, "Definition:subset", LeftToRight));
    block->append(input({2}, "Definition:subset", LeftToRight));
    block->append(input({}, "Proposition:forall_land_commutativity", LeftToRight));
    block->append(input({1}, "Proposition:implies_transitive", LeftToRight));
    block->append(input({}, "Definition:subset", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
    Proposition::Current = new Proposition("subset_equality", SET, "\\forall a \\forall b (((a \\subseteq b) \\land (b \\subseteq a)) \\implies (a = b))");
    block = new proof_block(deduction_LeftToRight);
    block->append(input({1}, "Definition:subset", LeftToRight));
    block->append(input({2}, "Definition:subset", LeftToRight));
    block->append(input({}, "Proposition:forall_land_commutativity", LeftToRight));
    block->append(input({1}, "Proposition:iff_implies", RightToLeft));
    block->append(input({}, "Definition:equality", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition();
    
    //Peano axioms
    fout<<"\\subsection{Peano axioms}"<<endl;
    //zero
    Definition::Current = new Definition("zero", SET, "0 = \\emptyset");
    Definition::addDefinition("Definition of 0.");
    
    //successor
    Definition::Current = new Definition("successor", SET, "\\forall a ((S(a)) = (a \\cup \\{ a \\}))");
    Definition::addDefinition("Definition of successor $S(x)$.");
    
    Proposition::Current = new Proposition("equality_substitution_successor", SET, "\\forall a \\forall b ((a = b) \\iff ((S(a)) = (S(b))))");
    description = "Axiom of Substitution for successor.";
    block = new proof_block(deduction_RightToLeft);
    block->append(input({}, "Definition:equality", LeftToRight));
    block->append(input({1,1,2}, "Definition:successor", LeftToRight));
    block->append(input({1,2,2}, "Definition:successor", LeftToRight));
    block->append(input({1,1}, "Proposition:pairwise_union_property", LeftToRight));
    block->append(input({1,2}, "Proposition:pairwise_union_property", LeftToRight));
    block->append(input({1,1,2}, "Proposition:singleton_set_property", LeftToRight));
    block->append(input({1,2,2}, "Proposition:singleton_set_property", LeftToRight));
    block->append(input({}, "Proposition:equality_property_3", RightToLeft));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
    //one
    Definition::Current = new Definition("one", SET, "1 = (S(0))");
    Definition::addDefinition("Definition of 1.");
    
    Proposition::Current = new Proposition("one_expand", SET, "1 = \\{ \\emptyset \\}");
    description = "Express 1 in term of $\\emptyset$.";
    block = new proof_block(deduction_LeftToRight);
    block->append(input({}, "Definition:one", LeftToRight));
    block->append(input({1}, "Definition:zero", LeftToRight));
    block->append(input({}, "Definition:successor", LeftToRight));
    block->append(input({}, "Proposition:pairwise_union_commutativity", LeftToRight));
    block->append(input({}, "Proposition:pairwise_union_identity", LeftToRight));
    Proposition::Current->append(block);
    Proposition::addProposition(description);
    
    Axiom::Current = new Axiom("zero_is_natural_number", SET, "0 \\in \\mathbb{N}");
    Axiom::addAxiom("0 is a natural number.");
    
    Axiom::Current = new Axiom("successor_is_natural_number", SET, "\\forall a ((a \\in \\mathbb{N}) \\implies ((S(a)) \\in \\mathbb{N}))");
    Axiom::addAxiom("Successor is a natural number.");
    
    Axiom::Current = new Axiom("induction", SET, "\\forall a (((0 \\in a) \\land (\\forall b (((b \\in \\mathbb{N}) \\land (b \\in a)) \\implies ((S(b)) \\in a)))) \\implies (\\mathbb{N} \\subseteq a))");
    Axiom::addAxiom("Axiom of induction.");
    
    fout.close();
}
