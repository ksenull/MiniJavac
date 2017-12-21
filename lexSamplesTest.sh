for file in ./Samples/*.java
do
    ./lexer "$file" | grep error
done
