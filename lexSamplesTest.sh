#!/usr/bin/env bash
for file in ./Samples/*.java
do
    echo "$file"
    cat "$file" | ./cmake-build-debug/ast/AST | grep error

done
