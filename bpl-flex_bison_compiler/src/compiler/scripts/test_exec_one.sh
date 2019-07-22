DIRECTORY=../../../tests

printf $1
printf "\n"
./../out/grammar.out $DIRECTORY/$1 $DIRECTORY/$1.s
gcc $DIRECTORY/$1.s -o $DIRECTORY/$1.out -g -L../out/ -lbplstd
./$DIRECTORY/$1.out
printf "\n"
