#!/usr/bin/env bash
for file in ./BadSamples/*.java
do
    echo "$file"
    cat "$file" | ./cmake-build-debug/symboltable/SymbolTable | grep error
done
