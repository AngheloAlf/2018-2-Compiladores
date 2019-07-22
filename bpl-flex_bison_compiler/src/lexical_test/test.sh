DIRECTORY=../../tests

for i in $DIRECTORY/*.bpl; do
    # Process $i
    ./lexical.out $i
done