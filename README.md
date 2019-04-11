# MiniJava compiler (to intermidiate code representation) implemented on C++

1. Parsing made with the help of flex and bison. The grammar is similar to the one showed [here](http://www.cambridge.org/resources/052182060X/MCIIJ2e/grammar.htm)
2. Syntax tree could be visualised in common/drawgraph submodule
3. Typechecker bases on symbol table checking.
4. After the typecheck syntax nodes are translated into assembly-like abstract language (IR)

## requirements
* gcc-5.4,  g++-5.4
* libgraphviz-dev
* flex
* bison
