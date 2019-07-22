DIRECTORY=../../../tests

for i in $DIRECTORY/*.bpl; do
    printf $i 
    printf "\n"
    ./../out/compiler.out $i $i.s
    printf "\n"
done