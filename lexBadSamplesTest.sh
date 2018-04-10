#!/usr/bin/env bash
for file in ./BadSamples/*.java
do
    cat "$file" | ./cmake-build-debug/ast/AST | grep error
done
