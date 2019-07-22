DIRECTORY=../../../tests

for i in $DIRECTORY/*.bpl; do
    printf $i 
    printf "\n"
    ./../out/grammar.out $i $i.s
    printf "\n"
done