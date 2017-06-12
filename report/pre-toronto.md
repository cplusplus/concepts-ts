
Pre-Toronto 2017: Concepts Issues
=================================

Andrew Sutton \<asutton@uakron.edu\>

Date: 2017-06-12

This is an analysis of open issues.


## Substitution and satisfaction

These issues aren't quite duplicates, but they are closely related.

- 18 -- Predicate constraints that are not constant expressions	
- 34 -- Premature substitution into associated constraints	
- 35 -- Handwaving around instantiation of constraining elements	
- 37 -- Redundant bool requirement on predicate constraints	

## Subsumption

There was discussion in Kona that would affect the wording for these rules,
so we're waiting on a paper with new wording. That proposals (as I recall)
would make atomic constraints comparable iff they appear in the same concept
definition. Presumably that paper would address these issues as well.

- 11 Concerns about subsumption and equivalence rules	
- 17 Wording for subsumption	
- 30 Normalization wording guarantees worst case performance for subsumption	

It would be worth noting that that paper could also affect [expr.prim.req]
if *requires-expression*s would no longer introduce atomic constraints, which
seems reasonable since none of those constraints would be comparable anyway.

However, we should review wording for this issue:

- 28 Ordering of constraints involving fold expressions	

## Requires expressions

- 3 -- allow requires in more contexts
- 29 -- Allow concepts to be evaluated in any context	

## Concept definitions

- 15 -- Partial specialization of non-concept variable template as a concept definition 
- 16 -- Concept and non-concept declarations of the same variable template
- 22 -- Initializers are never constraint-expressions	
- 27 -- Redundant restriction on function specifiers for concepts	

## Constrained type specifiers

- 31 -- update the grammar name constrained-type-specifier

## Constrained declarations

- 19 -- Wording makes all constrained function definitions ill-formed	
- 21 -- Disambiguation rules for requires-clauses	
- 24 -- Expression equivalence outside of declaration matching is novel	
- 25 -- Block scope template declarations	

## Unclassified

- 1 -- Relationship of implicit conversion constraints to is_convertible	
- 23 -- Associated constraints is a term defined for templates only	
- 36 -- Constraints on complete specializations	
