DIRECTORY=../../tests

for i in $DIRECTORY/*.bpl; do
    # Process $i
    ./lexical $i
done