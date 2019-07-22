# BPL-Flex_Bison

A [BPL](http://occs.cs.oberlin.edu/~bob/cs331/The%20BPL%20Programming%20Language.pdf) compiler using flex and bison.

The grammar has been slightly modified. The new grammar is in `grammar/BPL-UTFSM.txt.` Thanks to @vonbrand.

## Dependencies

 * Flex & Bison

 For an easy install under Debian, Ubuntu or other derivates use: `apt install flex bison`

## How to compile

 * `git clone https://gitlab.labcomp.cl/BPL/bpl-flex_bison.git`
 * `cd bpl-flex_bison/src/grammar`
 * `make` or `make release`

## How to execute

 * `./grammar <input>.bpl <output>.s`

It does not add the `.bpl` or `.s` extension.

To get an executable, use `gcc` or `clang`.
