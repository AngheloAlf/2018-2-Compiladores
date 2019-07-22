DIRECTORY=../../../tests

printf $1
printf "\n"
./../out/grammar.out $DIRECTORY/$1 $DIRECTORY/$1.s
printf "\n"
