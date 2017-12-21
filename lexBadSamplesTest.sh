for file in ./BadSamples/*.java
do
    ./lexer "$file" | grep error
done
