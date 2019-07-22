DIRECTORY=../tests

echo "If no ouput is produced (besided of the file name), then the grammar is ok."
echo ""

for i in $DIRECTORY/*.bpl; do
    # Process $i
    ./grammar $i
done