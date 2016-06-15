https://github.com/cplusplus/concepts-ts is the repository for the 
C++ Technical Specification "Extensions for Concepts". The issues
list can be found at https://github.com/cplusplus/concepts-ts/issues.

For the most recent draft of the lists generated from these files,
see http://cplusplus.github.com/concepts-ts/ts-active.html 


## Maintaining this list

To publish a new revision of this document:

1. Before starting, copy `ts-issues-toc.html` over `meta-data/ts-toc-old.html`.
2. Increment the revision and date at the top of `xml.ts-issues.xml`.
3. Modify `src/lists.cpp` to update the revision number in the history. This
   change is around line 1020.
4. Run `make lists`
5. Review your changes.
6. Commit and push.

This will not update the online publication, it only stages it. To make the
online version match these changes, update `gh-pages`.

1. Zip all the top-level `html` files into a single source: `zip issues.zip *.html`.
2. Checkout `gh-pages` and `cd` to the top-level directory in the repository.
3. Unzip your archive to overwrite the existing content.
4. Commit and push.

Note that the file `index.html` will automatically redirect to `ts-index.html`.
