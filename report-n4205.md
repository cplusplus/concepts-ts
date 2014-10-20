
<head>
<style>
html { 
  font-size: 100%; 
  overflow-y: scroll; 
  -webkit-text-size-adjust: 100%; 
  -ms-text-size-adjust: 100%; 
}

body{
  color:#444;
  font-family:Georgia, Palatino, 'Palatino Linotype', Times;
  font-size:10px;
  line-height:1.5em;
  background:#fefefe;
  width: 45em;
  margin: 10px auto;
  padding: 1em;
  outline: 1300px solid #FAFAFA;
}

span.backtick {
  border:1px solid #EAEAEA;
  border-radius:3px;
  background:#F8F8F8;
  padding:0 3px 0 3px;
}

p{ margin:1em 0; }

img{ max-width:100%; }

h1,h2,h3,h4,h5,h6{
font-weight:normal;
color:#111;
line-height:1em;
}

h4,h5,h6{ font-weight: bold; }
h1{ font-size:2.5em; }
h2{ font-size:2em; border-bottom:1px solid silver; padding-bottom: 5px; }
h3{ font-size:1.5em; }
h4{ font-size:1.2em; }
h5{ font-size:1em; }
h6{ font-size:0.9em; }

blockquote{
  color:#666666;
  margin:0;
  padding-left: 3em;
  border-left: 0.5em #EEE solid;
}

hr { 
  display: block; 
  height: 2px; 
  border: 0; 
  border-top: 1px solid #aaa;
  border-bottom: 1px solid #eee; 
  margin: 1em 0; padding: 0; 
}

pre, code, kbd, samp { 
  color: #000; 
  font-family: monospace; 
  font-size: 0.88em; 
  border-radius:3px;
  background-color: #F8F8F8;
  border: 1px solid #CCC; 
}
pre { 
  white-space: pre; 
  white-space: pre-wrap; 
  word-wrap: break-word; 
  padding: 5px 12px;
}

pre code { 
  border: 0px !important; padding: 0;
}

code { padding: 0 3px 0 3px; }

b, strong { font-weight: bold; }

dfn { font-style: italic; }

ins { background: #ff9; color: #000; text-decoration: none; }

mark { background: #ff0; color: #000; font-style: italic; font-weight: bold; }

sub, sup { font-size: 75%; line-height: 0; position: relative; vertical-align: baseline; }
sup { top: -0.5em; }
sub { bottom: -0.25em; }

ul, ol { margin: 1em 0; padding: 0 0 0 2em; }
li p:last-child { margin:0 }
dd { margin: 0 0 0 2em; }

img { border: 0; -ms-interpolation-mode: bicubic; vertical-align: middle; }

table { border-collapse: collapse; border-spacing: 0; }
td { vertical-align: top; }

@media only screen and (min-width: 480px) {
  body{font-size:14px;}
}

@media only screen and (min-width: 768px) {
body{font-size:16px;}
}

@media print {
  * { background: transparent !important; color: black !important; filter:none !important; -ms-filter: none !important; }
  body{font-size:12pt; max-width:100%; outline:none;}
  a, a:visited { text-decoration: underline; }
  hr { height: 1px; border:0; border-bottom:1px solid black; }
  a[href]:after { content: " (" attr(href) ")"; }
  abbr[title]:after { content: " (" attr(title) ")"; }
  .ir a:after, a[href^="javascript:"]:after, a[href^="#"]:after { content: ""; }
  pre, blockquote { border: 1px solid #999; padding-right: 1em; page-break-inside: avoid; }
  tr, img { page-break-inside: avoid; }
  img { max-width: 100% !important; }
  @page :left { margin: 15mm 20mm 15mm 10mm; }
  @page :right { margin: 15mm 10mm 15mm 20mm; }
  p, h2, h3 { orphans: 3; widows: 3; }
  h2, h3 { page-break-after: avoid; }
}
</style>
</head>

<body>

N4205 Editor's Report
=====================

2014-10-17
Andrew Sutton
University of Akron

Acknowledgments
---------------

Special thanks to CWG for their input on these revisions, especially
those members of the committee whose participated in the two telecon
reviews in August and September.

Special thanks to those whose submitted editorial fixes and issues,
including Michael Park, Jonathan Wakely, Fernando Pelliccioni,
Casey Carter, Dinka Ranns, and Braden Obrzut.


Summary
-------

There is one new paper: N4205 replaces N4040 as the latest "Concepts" paper,
and is significantly revised based on comments from the Rapperswil
meeting, and the August and September teleconferences.


Changes
-------

The N4205 was renumbered to match layout of the current working
draft the C++ Programming languages.

- [intro.refs] Fix reference to ISO standard

- [intro.defns] Removed this subsection, preferring to define terms as needed
in text.

- [expr.prim.lambda] Introduce a new paragraph to define generic lambda
in this section instead of in [dcl.spec.auto]

- [expr.prim.lambda] Update paragraph 5 to define the member call operator
of a generic lambda in terms of an abbreviated function, as specified
in [dcl.fct].

- [expr.prim.lambda] Paragraph 4 in N4040 was moved into [dcl.fct] and
expanded with examples.

- [epxr.prim.req] Updated the identifier for this section to match that
of other primary expressions (expr.prim.req instead of expr.req).

- [expr.prim.req] Refactored the *requirement-list* grammar so that each *requirement*
is followed by `;` instead of having each kind of *requirement* have its
own `;`. It was requested that the handling of requirements match 
statements, and allow `;;` as a requirement. This is not allowed by the
current grammar since it could allow a *requires-expression* to declare
an empty set of constraints, making it logically equivalent to an 
unconstrained template but not equivalent (different *constraint-expressions*).

- [expr.prim.req] Moved grammar for specific requirements into subsections.

- [expr.prim.req] Describe the scoping of local parameters.

- [expr.prim.req] Prohibit ellipses (`requires (...)`) and default
arguments for local parameters.

- [expr.prim.req.*] Each section defines its requirements in terms of an
introduced constraint described in [temp.constr.atom], as well as other
editorial fixes (examples, spelling, grammar).

- [expr.prim.req.type] Change the grammar to accept a *type-specifier* as
a type requirement.

- [dcl.spec.auto] As per discussion in Rapperswil, expanded this section to 
accommodate the use of `auto` in the type of a parameter. These modifications
also allow multiple occurrences of `auto` in a single declaration.

- [dcl.spec.constr] Update the introduction paragraphs to link the use
of a *constrained-type-specifier* to the `auto` specifier. They can appear
in some of the same contexts.

- [dcl.spec.constr] Editorial revisions to the text describing the resolution
of a *concept-name* and the synthesis of the associated constraint
expression. In particular, the associated constraint now describes cases
where either the *constrained-type-specifier* is followed by `...`, or the 
designated concept is variadic.

- [dcl.spec.concept] Concepts shall only be defined at namespace scope.

- [dcl.spec.concept] Refactor some of the limitations for function and
variable concepts so they apply to both.

- [dcl.spec.concept] Disallow any *decl-specifier*s other than `concept`
and `bool`.

- [dcl.spec.concept] Explicitly prohibit the use of `auto` to deduce
the return type of a function concept definition because it requires the
instantiation of the function definition to deduce the type.

- [dcl.spec.concept] Drop the example in for the prohibition against
explicit instantiation, explicit specialization, and partial specialization.
It didn't provide any additional information.

- [dcl.decl] Underline new grammar in *init-declarator* syntax.

- [dcl.decl] As per discussion in Rapperswil, regular functions can be
constrained. That prohibition is dropped in N4205.

- [dcl.fct] Refactor the grammar for parameter declarations into
*basic-parameter-declaration*, which does not include default arguments,
and *parameter-declaration*, which is a *basic-parameter-declaration*
plus an optional default argument. This change supports the definition
of constrained template parameters in [temp.param].

- [dcl.fct] In paragraph 5, add associated constraints to the list of things
that all declarations for a function must agree in. On a second reading,
the word "exact" is probably too strong for constraints; they should just
be equivalent as per [temp.constr.expr].

- [dcl.fct] Define abbreviated functions by moving most of the text describing
generic lambdas to paragraph 16 and extend that text for 
*constrained-type-specifiers*. 

- [dcl.fct] Paragraph 17 describes how equivalent placeholders have the
same invented template parameter. Equivalence is now defined in terms of
the associated constraints. Added examples.

- [dcl.fct.def] Remove the restriction against constrained function definitions
being constrainable if they are function templates.

- [dcl.fct.def] Remove the restriction that a destructor definition cannot
be constrained.

- [dcl.fct.def] Paragraph 9 ensures that function parameters are visible
in the requires clause.

- [class] In the grammar for member-declarators, the requires clause now
appears before the pure-specifier-seq.

- [class.mem] In paragraph 9, update examples for normal functions.

- [class.mem] Paragraph 10 ensures that function parameters are visible
in a requires clause.

- [class.virtual] Added a new paragraph that prohibits associated constraints
on virtual functions and overrides thereof.

- [over] Add references to constraints to paragraphs 1 and 3, describing what
it means to overload with constraints.

- [over.match] Define declaration matching when the declarations have
constraints.

- [over.match.viable] Update paragraph 1 to include constraints in the 
determination of viable functions, and require the associated constraints
to be satisfied in order for a function to be a viable candidate.

- [over.match.best] Add a new ordering comparison; when two normal functions
or member functions have equivalent parameter type lists, order by their
constraints.

- [over.over] Add test describing what happens when the address of an 
overloaded function is taken, and one or more of those candidates has
associated constraints.

- [temp] Move all text related to template introductions into a new
sub-clause, 14.2.

- [temp] Add text explicitly relating declarations have equivalent
constraints, and many new examples describing these equivalences.

- [temp.param] Refactor the grammar for non-type template parameter
declarations to admit the constrained template parameters, and update
the text in paragraph 2 to reflect that change.

- [temp.param] Add paragraphs 3 and 4, which describe the declaration of 
constrained template parameters and restrictions.

- [temp.param] Collapse several paragraphs in N4040 which describe the
resolution of a concept iname into a reference to [dcl.spec.constr]. Clarify
the properties of template parameters declared as a result of that
resolution.

- [temp.intro] This section was moved out of the beginning of [temp],
and it describes how template parameters are introduced using a *concept-name*
and a list of identifiers.

- [temp.names] Make the title of this section match the standard.

- [temp.names] Add a paragraph to explicitly require the instantiation of
default template arguments when used in a context that requires them (other
than for function templates).

- [temp.names] Add a paragraph requiring associated constraints to be
satisfied in order to refer to a type or variable.

- [temp.arg.template] Describe the comparison of constraints in terms
of "most constrained" instead of subsumption. Fix the broken example.

- [temp.class] Require out-of-class member definitions to have the same
constraints as the class declaration.

- [temp.mem.func] Remove redundant text; wording for instantiation was
moved to [temp.inst]. Merge the example from N4040 (paragraph 4 of the same
section) into [temp.class].

- [temp.mem] Require that member templates defined outside of their class
to have the same constraints as their declaring class.

- [temp.friend] Rewritten. Friend functions can be declared only when
the constraints are non-dependent or they refer to a template specialization
whose template can be found based on the specialization arguments. Constrained
friend function definitions are permitted.

- [temp.class.spec] Allow class template partial specializations to be 
constrained, and with a template argument list that matches the implicit
argument list of the primary template.

- [temp.class.match] Add an example that extends the one in the
original document. Note that like the original document, the partial
specializations being found are declared in [temp.class.spec].

- [temp.class.order] Make examples core meaningful. Errors in the example
in N4205 have been fixed in a future version of the paper.

- [temp.over.link] Modify paragraph 6 to account for constraints in the
equivalence of function templates and also the functional equivalence of
those templates. Reformat those sentences into an itemized list for
improved readability.

- [temp.func.corder] Simplify the description of this ordering by rewriting
the  condition under which constraints are compared in terms of deduction 
instead template parameter lists and return types.

- [temp.alias] An intermediate version of the paper reviewed during the
teleconferences included requirements to check constraints for alias templates.
This is now handled by [temp.names].

- [temp.inst] Describe the implicit instantiation of member constraints
inside a class template specialization. In particular, note that substitution
failures in an associated constraint result in an ill-formed program.

- [temp.inst] Require the satisfaction of constraints for an explicit
instantiation naming a constrained template or a set of overloaded functions
whose candidates may be constrained.

- [temp.expl.spec] Require the satisfaction of constraints for an explicit
specialization naming a constrained template or a set of overloaded functions
whose candidates may be constrained.

- [temp.deduct] Modified paragraph 5 to explicitly define a candidates 
associated constraints to be false if substitution into those constraints 
fails.

- [temp.deduct.decl] Insert paragraph 2, which requires the filtering of
declarations by unsatisfied constraints, and update paragraph 3 to follow
from that modification.

- [temp.constr] Completely rewritten based on a suggestion from Jens
Mauer that perhaps describing constraints in terms of the expression machinery
is not the right approach. This sub-clause now contains two major parts:
the definition of constraints and the operations on constraints, and the
definition of *constraint-expression*s and their normalization into
constraints.

- [temp.constr] Constraints are described as an abstract syntax (although
no concrete grammar is given explicitly) and in a way that attempts to mirror 
[expr]. Each kind of constraint is defined in [temp.constr.op] or
[temp.constr.atom]. There are two properties derived from constraints: 
satisfaction and subsumption. These are described for each kind of constraint.

- [temp.constr] Satisfaction for any constraint is defined to fail if
substitution of non-dependent arguments into it fails.

- [temp.constr] The definition of subsumption in terms of a mapping from
atomic constraints to truth values is replaced by a more algorithmic
definition, which each constraint defining a piece of the subsumption relation.

- [temp.constr.op] Define conjunction and disjunction separately from
logical and and logical or.

- [temp.constr.atom] Define atomic constraints separately from the different
kinds of *requirements* in [expr.prim.req].

- [temp.constr.atom] Split the "result type constraint" into two distinct
atomic constraints: an implicit conversion constraint and an argument
deduction constraint.

- [temp.constr.atom] Describe expression and `constexpr` constraints
separately, removing the ambiguity as to whether or not the expression
`E` in a *compound-requirement* is an unevaluated operand. `E` is certainly
evaluated to determine the satisfaction of a `constexpr` constraint.


- [temp.constr.atom.expr] Renamed from "valid expression" constraint.

- [temp.constr.atom.type] Renamed from "valid type" constraint.

- [temp.constr.atom.conv] Define a requirement on the conversion of an
expression to a type in terms of the implicit conversions. This allows
the use of `void` in a *trailing-return-type* on a *compound-requirement*.

- [temp.constr.atom.deduct] Define a deduction constraint in terms of
successful template argument deduction against an invented function template
whose sole parameter type is derived from the *trailing-return-type* of
a *compound-requirement*.

- [temp.constr.atom.constexpr] Document the fact that `constexpr`
constraints apply on to specific arguments and not sets of arguments.

- [temp.constr.atom.constexpr] Require the expression `E` to be a prvalue
constant expression in order to be satisfied.

- [temp.constr.atom.noexcept] Define satisfaction in terms of the
`noexcept` expression.

- [temp.constr.order] Define the partial ordering by constraints in terms
of the subsumption relation. Provide references to the contexts in which
this comparison is required.

- [temp.constr.expr] Instead of defining properties of *constraint-expression*s,
define constraints in terms of normalizing a constraint expression. Different
kinds of expressions are mapped to different kinds of constraints by this
algorithm.

- [temp.constr.expr] Explicitly define when two constraints are equivalent.
Note that this duplicates a good deal of text from [temp.over.link], but
also provides additional rules for making `(E)` functionally equivalent
to `E` but not equivalent.

</body>