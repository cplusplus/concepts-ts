
Editors Report
==============

This is not a ful

The following notes describe changes made to the specification based on
reviewer comments, personal reviews, and patches sent by outside contributors.
Sections are ordered 

Acknowledgments
---------------

Thanks to Jonathan Wakely, Fernando Pelliccioni, Casey Carter, and Dinka Ranns
for submitting patches against the Concepts proposal, and to Adam Butcher
and everybody else who brought problems to my attention.

Thanks to Dinka Ranns, Richard Smith, Gabriel Dos Reis, and Bjarne Stroustrup 
for contributing suggestions for wording to this specification. 

Thank you to the Core Working Group for their review of this proposal, and
especially Jens Mauer for his updated comments from the initial CWG review.

Thank you to the University of Akron for supporting my contributions to the 
ISO C++ Standards Committee.


Changes since N3889
-------------------

The changes to the Concepts paper were substantial following the Issaquah
meeting. I have tried to capture changes made in response to specific
technical (not typographical) issues based on my notes from the CWG review,
various discussions during the meeting, and comments/emails between the
post-Issaquah mailing and the pre-Rapperswil mailing.

Rather than address individual issues, I will try to describe the larger
changes that were made to specific parts of the paper.

### Introduction ###


### Requires expressions ###


### Declarators and declarations ###


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
  reference-qualified type parameters.