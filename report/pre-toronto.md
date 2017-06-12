
Pre-Toronto 2017: Concepts Issues
=================================

Andrew Sutton \<asutton@uakron.edu\>

Date: 2017-06-12

The active issues list can be found here: 
<http://cplusplus.github.io/concepts-ts/ts-active.html>.

I've gone through and grouped all related open issues and added notes.

## Substitution and satisfaction

- [18](http://cplusplus.github.io/concepts-ts/ts-active.html#18) -- Predicate constraints that are not constant expressions	
- [34](http://cplusplus.github.io/concepts-ts/ts-active.html#34) -- Premature substitution into associated constraints	
- [35](http://cplusplus.github.io/concepts-ts/ts-active.html#35) -- Handwaving around instantiation of constraining elements	
- [37](http://cplusplus.github.io/concepts-ts/ts-active.html#37) -- Redundant bool requirement on predicate constraints	

These issues aren't quite duplicates, but they are closely related. In general,
the process of substitution and normalization have some gaps that need to
be bridged and redundancies that need to be removed. A resolution for 35
should subsume 18 and 34. Issue 37 would be relatively easy to fix after.

## Subsumption

There was discussion in Kona that would affect the wording for these rules,
so we're waiting on a paper with new wording. That proposals (as I recall)
would make atomic constraints comparable iff they appear in the same concept
definition. Presumably that paper would address these issues as well.

- [11](http://cplusplus.github.io/concepts-ts/ts-active.html#11) -- Concerns about subsumption and equivalence rules	
- [17](http://cplusplus.github.io/concepts-ts/ts-active.html#17) -- Wording for subsumption	
- [30](http://cplusplus.github.io/concepts-ts/ts-active.html#30) -- Normalization wording guarantees worst case performance for subsumption	

It would be worth noting that that paper could also affect [expr.prim.req]
if *requires-expression*s would no longer introduce atomic constraints, which
seems reasonable since none of those constraints would be comparable anyway.

Wait until there's a new paper in EWG.

- [28](http://cplusplus.github.io/concepts-ts/ts-active.html#28) -- Ordering of constraints involving fold expressions

Update the wording to ensure it's complete. I think we could move this to
Ready in Toronto.

## Concept definitions

There were two proposals to change the concept definition section in Kona:
P0324r0 proposes to move to a single declaration syntax for concepts by
e.g., just removing `bool`. P0587r0 suggested more significant changes.
There were no straw poll votes in EWG on either paper, but I expect there
will be forthcoming changes that will affect these issues.

- [15](http://cplusplus.github.io/concepts-ts/ts-active.html#15) -- Partial specialization of non-concept variable template as a concept definition 
- [16](http://cplusplus.github.io/concepts-ts/ts-active.html#16) -- Concept and non-concept declarations of the same variable template
- [22](http://cplusplus.github.io/concepts-ts/ts-active.html#22) -- Initializers are never constraint-expressions	
- [27](http://cplusplus.github.io/concepts-ts/ts-active.html#27) -- Redundant restriction on function specifiers for concepts	

This also affects issues 6, 7, 8, and 20. However, we should wait until EWG
forwards a paper with an alternative design.

## Constrained type specifiers

- [31](http://cplusplus.github.io/concepts-ts/ts-active.html#31) -- Constrained-type-specifiers introduce non-type placeholders	

This issue requests to change the grammar name, but that might not be the right 
approach. I wonder if we shouldn't consider adding placeholders in expressions 
in order to better characterize their kind (either non-type or template). 
It's worth noting that there was some discussion about adding unconstrained 
placeholders to partial template argument lists during the deduction 
discussions. 

## Constrained declarations

- [19](http://cplusplus.github.io/concepts-ts/ts-active.html#19) -- Wording makes all constrained function definitions ill-formed	
- [25](http://cplusplus.github.io/concepts-ts/ts-active.html#25) -- Block scope template declarations	

These two are related and are relatively easy to fix.

- [24](http://cplusplus.github.io/concepts-ts/ts-active.html#24) -- Expression equivalence outside of declaration matching is novel	

I think that this issue hints at a desire to change the declaration matching
rules to be strictly syntactic (i.e., don't match by computed associated
constraints). That would need an EWG paper.

- [21](http://cplusplus.github.io/concepts-ts/ts-active.html#21) -- Disambiguation rules for requires-clauses	

This just needs wording.


## Unclassified

- [1](http://cplusplus.github.io/concepts-ts/ts-active.html#1) -- Relationship of implicit conversion constraints to is_convertible	

This issue has a note that it relates to an existing CWG issue, but which
one is not captured.

- [23](http://cplusplus.github.io/concepts-ts/ts-active.html#23) -- Associated constraints is a term defined for templates only	

This just needs wording to define associated constraints for abbreviated
function templates and explicit template specializations (see 36).

- [36](http://cplusplus.github.io/concepts-ts/ts-active.html#36) -- Constraints on complete specializations	

This should require an EWG paper.
