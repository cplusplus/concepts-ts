
Editors Report
==============

The following notes describe changes made to the specification based on
reviewer comments, personal reviews, and patches sent by outside contributors.

Acknowledgments
---------------

Thanks to Jonathan Wakely, Fernando Pelliccioni, Casey Carter, and Dinka Ranns
for submitting patches against the Concepts proposal, and to Adam Butcher,
Faisal Vali, and everybody else who brought problems to my attention.

Thanks to Dinka Ranns, Richard Smith, Gabriel Dos Reis, and Bjarne Stroustrup,
Daveed Vandevoorde and others for contributing suggestions for wording to this 
specification. 

Thank you to the Evolution and Core Working groups for their review of this 
paper, and especially Jens Mauer for his updated comments from the initial CWG 
review.

Thank you to the University of Akron for supporting my contributions to the 
ISO C++ Standards Committee.


Changes since N3929
-------------------

The changes to the Concepts paper were substantial following the Issaquah
meeting. I have tried to capture changes made in response to specific
technical (not typographical) issues based on my notes from the CWG review,
various discussions during the meeting, and comments/emails between the
post-Issaquah mailing and the pre-Rapperswil mailing.

Rather than address individual issues, I will try to describe the larger
changes that were made to specific parts of the paper.


### Introduction ###

The introduction has been rewritten to conform to the introductions of
other technical specifications or "pre" technical specifications. There
were a number of CWG comments regarding the structure and content of this
section. I hope that they have been adequately addressed.


### Requires expressions ###

Section 4 has been extensively rewritten. A summary of major changes is
here:

- A *type-requirement* is defined as a *typename-specifier*. This was an
  issue noticed by Daveed Vandevoorde (I think?) and discussed during the 
  EWG review and some after. The change limits the declaration of type
  requirements to a smaller set of type names than would the previous
  version, which tried to allow a *type-id*. This restriction matches the
  original intent of the requirement: this type name must be valid, not
  this type must be valid.

- The *result-type-requirement* in a *compound-requirement* was completely
  redesigned. Now, *trailing-return-type* is used to as the parameter type
  of an invented function (possibly function template, possibly constraind).
  The requirement is satisfied iff the required valid expression can be
  used as an argument to that function. This unifies all of the different
  type, conversion, and nested requirements into a single framework
  (see Errata and omissions).

- The `constexpr` keyword was moved to the front of the valid expression.

- Editorially, the section is rewritten to introduce the kinds of atomic
  constraints that can be introduced before the syntax that introduces them.

Somebody in the CWG asked if there was syntax for specifying same-type and
explicit conversion requirements in compound requirement. My notes don't
capture the source. N3580 (p. 28) provided notation for this, but users found 
it clunky and hard to understand. Also, all of our use cases used the basic 
conversion requirement described in N3929. I chose not to re-add the syntax. 
If stronger requirements are needed, they can be spelled explicitly using a 
nested requirement.


### Declarators ###

The purpose of 4.1.2 is to guarantee that `auto` also signifies that a
function is a generic function. I believe this issue wording was requested
by Dinka Ranns.

I moved most of the definitions related to the use of concept names as types
into the 4.1.3, "constrained type specifiers". Section 4.1.3 describes when
a concept name can be used within a type-specifier and the meaning of that
name (see Errata and omissions).


### Declarations ###

After the CWG review, Richard Smith (and later Jens Mauer) noted that the 
syntax for specifying constraints on generic functions would only allow
a *requires-clause* if the declaration included a *trailing-return-type*.
I moved the *requires-clause* to the *init-declarator*, to allow
constrained generic functions. I also added an optional *requires-clause* to
the *function-definition* and *member-definition* productions. I believe
this also addresses an issue where a constrained member function is defined
inside its class. The syntax in N3929 did not permit that.


### Constrained parameters ###

The syntax for constrained parameters was rewritten so that it matches
the syntax for parameter declarations. The intent was to remove the semantic
ambiguity where the same constrained parameter could be declared using either
the *constrained-parameter* production or the *parameter* production having
a *constrained-type-specifier*.


### Concept introductions ###

The section "Concept introductions" (section 6.5 in N3889) was merged into
"Templates" (clause 7 in N4040). The *template-declaration* syntax was
factored so that a template declaration begins either with a `template`
followed by a *template-parameter-list* or a *concept* followed by a
list of *identifier*s.

### Template constraints ###

This section has also seen significant rewrites.

- Clean up requiremetns on constraint expressions
- Clean up definition of an atomic constraint
- Explicitly define the "simplification" of constraint expressions into
  atomic constraints.
- Integrated Richard Smiths suggested wording for subsumption, but omitted
  examples (See Errata).


Changes since N4040
-------------------

- 3.1.1/2. Jonathan Wakely reported an errant sentence, which was removed.

- 5/3. Removed wording that is no longer used to describe associated constraints.

- 7/4. Jens Mauer comments that "it needs to get a lot clearer what the 
  properties of the *template-parameters* so introduced are.  "They match" is 
  insufficient.  At least, it's the "kind" (type, non-type, template),
  and a correspondence using the declaration order must be prescribed." Added
  wording that more clearly identifiers the relationship between the declared
  and copied template parameter. This may need another sentence describing what 
  happens when the parameter is a template parameter pack.

- Adam Butcher reported that the use of the concept `Mergeable` was no
  longer valid in the example in 7/4.

- In 7.1/3, the word "declaration" seemed unnecessary.

- Added 7.1/4 to restrict the ability to declare cv-qualified or
  reference-qualified type parameters. Note that the example is also new
  text, but there is a formatting bug preventing it from being colored.

- In the example in 7.3.1/2, be consistent with capitalization.

- Added text to help explain why `x` should be a valid argument, but not
  `z`. I'm not sure I've been successful.

- From Jens Mauer, in 7.4.3/2  "'A constrained friend is a friend of a class 
  template with associated constraints.'' This reads as if the enclosing class 
  template needs to have associated constraints." Changed the definition of
  a constrained friend so that it is written in terms of previously defined
  constrained declarations; do not try to describe (again) how constraints are
  added to a declaration.

- Also from Jens, same section: "What is 'shorthand'?  What are 'introduction'?"
  Removed references to those terms by virtue of previous redeclaration.

- Also from Jens, same section: "'Constraints on non-template friend functions 
  are written after the result type.'" What does this mean?  Your "operator==" in 
  the example seems to violate that". Text removed.

- Faisal Vali noted that wording defining the meaning of explicit specialization
  for constrained templates (and member function templates) seemed to be
  missing. Added section 7.5.3.

Errata and omissions
--------------------

- The definition list is (woefully) incomplete. 

- In 3.1.2/6 and/or 3.1.2.4, if the *trailing-return-type* contains a
  *constrained-type-specifier*, then the requires clause also includes the
  associated constraints as if a nested requirement had been written.
  This would guarantee that overload resolution would be ordered on those
  constraints. This is currently missing.

- 4.1.3/5 will almost certainly be flagged as having an error. What is an
  "enclosing declaration?"

- 4.1.3/11-15 seem overly complex. The intent is to describe how to determine
  which concept definition is referred to, given a concept name and a 
  possibly sequence of template arguments. The general principle is that,
  for any concept name and *number of template arguments*, there shall be 
  exactly one concept definition for which a valid template-id can be formed.
  The program is ill-formed if lookup finds zero or multiple concepts.

- From Jens Mauer: "All three examples in 7.4.3/2 show definitions of friends. How 
  does declaration matching work for these constrainted things?  Does a 
  constrained friend convey friendship to an unconstrained function or type 
  outside?  Where is the specification that this doesn't work?" Need wording to
  answer these questions.

- Also from Jens: "Shouldn't we require some "subsumes" relationship for 
  constraints on the template-parameters of partial specifications vs. the 
  primary template?  Presumably, yes. There is some discussion of that here:
  https://github.com/cplusplus/concepts-ts/issues/32.

- Section 7.6 needs more and better examples. 7.6/7 is not especially helpful.
