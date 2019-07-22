DIRECTORY=../../../tests

for i in $DIRECTORY/*.bpl; do
    printf "Building: "
    printf $i 
    printf "\n"
    gcc $i.s -o $i.out -L../out/ -lbplstd -g
    printf "\n"
done

for i in $DIRECTORY/*.bpl; do
    # exec $i
    printf "executing: "
    printf $i 
    printf "\n"
    ./$i.out
    printf "\n"
done
